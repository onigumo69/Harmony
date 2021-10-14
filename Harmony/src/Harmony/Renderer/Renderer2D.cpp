#include "Renderer2D.h"

#include "RenderCommand.h"
#include "Shader.h"
#include "VertexArray.h"

#include "Harmony/Debug/Instrumentor.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Harmony
{

	struct QuadVertex
	{
		glm::vec3 position;
		glm::vec4 color;
		glm::vec2 tex_coord;
	};

	struct Renderer2DData
	{
		const uint32_t max_quads = 10000;
		const uint32_t max_vertices = max_quads * 4;
		const uint32_t max_indices = max_quads * 6;

		Ref<VertexArray> quad_vertex_array;
		Ref<VertexBuffer> quad_vertex_buffer;
		Ref<Shader> texture_shader;
		Ref<Texture2D> white_texture;

		uint32_t quad_index_count = 0;
		QuadVertex* quad_vertex_buffer_base = nullptr;
		QuadVertex* quad_vertex_buffer_ptr = nullptr;
	};

	static Renderer2DData Data;

	void Renderer2D::init()
	{
		HM_PROFILE_FUNCTION();

		Data.quad_vertex_array = VertexArray::create();
		Data.quad_vertex_buffer = VertexBuffer::create(Data.max_vertices * sizeof(QuadVertex));
		Data.quad_vertex_buffer->set_layout({
				{ ShaderDataType::Float3, "a_Position" },
				{ ShaderDataType::Float4, "a_Color" },
				{ ShaderDataType::Float2, "a_TexCoord" }
			});

		Data.quad_vertex_array->add_vertex_buffer(Data.quad_vertex_buffer);
		Data.quad_vertex_buffer_base = new QuadVertex[Data.max_vertices];

		uint32_t* quad_indices = new uint32_t[Data.max_indices];

		uint32_t offset = 0;
		for (uint32_t i = 0; i < Data.max_indices; i += 6)
		{
			quad_indices[i + 0] = offset + 0;
			quad_indices[i + 1] = offset + 1;
			quad_indices[i + 2] = offset + 2;
			
			quad_indices[i + 3] = offset + 2;
			quad_indices[i + 4] = offset + 3;
			quad_indices[i + 5] = offset + 0;

			offset += 4;
		}

		Ref<IndexBuffer> quad_index_buffer = IndexBuffer::create(quad_indices, Data.max_indices);
		Data.quad_vertex_array->set_index_buffer(quad_index_buffer);
		delete[] quad_indices;

		Data.white_texture = Texture2D::create(1, 1);
		uint32_t white_texture_data = 0xffffffff;
		Data.white_texture->set_data(&white_texture_data, sizeof(uint32_t));

		Data.texture_shader = Shader::create("assets/shaders/Texture.glsl");
		Data.texture_shader->bind();
		Data.texture_shader->set_int("u_Texture", 0);
	}

	void Renderer2D::shutdown()
	{
		HM_PROFILE_FUNCTION();

	}

	void Renderer2D::begin_scene(const OrthographicCamera& camera)
	{
		HM_PROFILE_FUNCTION();

		Data.texture_shader->bind();
		Data.texture_shader->set_mat4("u_ViewProjection", camera.get_view_projection_matrix());

		Data.quad_index_count = 0;
		Data.quad_vertex_buffer_ptr = Data.quad_vertex_buffer_base;
	}

	void Renderer2D::end_scene()
	{
		HM_PROFILE_FUNCTION();

		uint32_t data_size = (uint8_t*)Data.quad_vertex_buffer_ptr - (uint8_t*)Data.quad_vertex_buffer_base;
		Data.quad_vertex_buffer->set_data(Data.quad_vertex_buffer_base, data_size);

		flush();
	}

	void Renderer2D::flush()
	{
		RenderCommand::draw_indexed(Data.quad_vertex_array, Data.quad_index_count);
	}

	void Renderer2D::draw_quad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		draw_quad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::draw_quad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		HM_PROFILE_FUNCTION();

		Data.quad_vertex_buffer_ptr->position = position;
		Data.quad_vertex_buffer_ptr->color = color;
		Data.quad_vertex_buffer_ptr->tex_coord = { 0.0f, 0.0f };
		Data.quad_vertex_buffer_ptr++;

		Data.quad_vertex_buffer_ptr->position = { position.x + size.x, position.y, 0.0f };
		Data.quad_vertex_buffer_ptr->color = color;
		Data.quad_vertex_buffer_ptr->tex_coord = { 1.0f, 0.0f };
		Data.quad_vertex_buffer_ptr++;

		Data.quad_vertex_buffer_ptr->position = { position.x + size.x, position.y + size.y, 0.0f };
		Data.quad_vertex_buffer_ptr->color = color;
		Data.quad_vertex_buffer_ptr->tex_coord = { 1.0f, 1.0f };
		Data.quad_vertex_buffer_ptr++;

		Data.quad_vertex_buffer_ptr->position = { position.x, position.y + size.y, 0.0f };
		Data.quad_vertex_buffer_ptr->color = color;
		Data.quad_vertex_buffer_ptr->tex_coord = { 0.0f, 1.0f };
		Data.quad_vertex_buffer_ptr++;

		Data.quad_index_count += 6;

		/*
		Data.texture_shader->set_float("u_TilingFactor", 1.0f);
		Data.white_texture->bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) 
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		Data.texture_shader->set_mat4("u_Transform", transform);
		Data.quad_vertex_array->bind();
		RenderCommand::draw_indexed(Data.quad_vertex_array);
		*/
	}

	void Renderer2D::draw_quad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tiling_factor, const glm::vec4& tint_color)
	{
		draw_quad({ position.x, position.y, 0.0f }, size, texture, tiling_factor, tint_color);
	}

	void Renderer2D::draw_quad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tiling_factor, const glm::vec4& tint_color)
	{
		HM_PROFILE_FUNCTION();

		Data.texture_shader->set_float4("u_Color", tint_color);
		Data.texture_shader->set_float("u_TilingFactor", tiling_factor);
		texture->bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) 
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		Data.texture_shader->set_mat4("u_Transform", transform);

		Data.quad_vertex_array->bind();
		RenderCommand::draw_indexed(Data.quad_vertex_array);
	}
	
	void Renderer2D::draw_rotated_quad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		draw_rotated_quad({ position.x, position.y, 0.0f }, size, rotation, color);
	}

	void Renderer2D::draw_rotated_quad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		HM_PROFILE_FUNCTION();

		Data.texture_shader->set_float4("u_Color", color);
		Data.texture_shader->set_float("u_TilingFactor", 1.0f);
		Data.white_texture->bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		Data.texture_shader->set_mat4("u_Transform", transform);
		Data.quad_vertex_array->bind();
		RenderCommand::draw_indexed(Data.quad_vertex_array);
	}

	void Renderer2D::draw_rotated_quad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tiling_factor, const glm::vec4& tint_color)
	{
		draw_rotated_quad({ position.x, position.y, 0.0f }, size, rotation, texture, tiling_factor, tint_color);
	}

	void Renderer2D::draw_rotated_quad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tiling_factor, const glm::vec4& tint_color)
	{
		HM_PROFILE_FUNCTION();

		Data.texture_shader->set_float4("u_Color", tint_color);
		Data.texture_shader->set_float("u_TilingFactor", tiling_factor);
		texture->bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		Data.texture_shader->set_mat4("u_Transform", transform);

		Data.quad_vertex_array->bind();
		RenderCommand::draw_indexed(Data.quad_vertex_array);
	}

}