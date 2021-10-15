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
		float tex_index;
		float tiling_factor;
	};

	struct Renderer2DData
	{
		static const uint32_t max_quads = 20000;
		static const uint32_t max_vertices = max_quads * 4;
		static const uint32_t max_indices = max_quads * 6;
		static const uint32_t max_texture_slots = 32;

		Ref<VertexArray> quad_vertex_array;
		Ref<VertexBuffer> quad_vertex_buffer;
		Ref<Shader> texture_shader;
		Ref<Texture2D> white_texture;

		uint32_t quad_index_count = 0;
		QuadVertex* quad_vertex_buffer_base = nullptr;
		QuadVertex* quad_vertex_buffer_ptr = nullptr;

		std::array<Ref<Texture2D>, max_texture_slots> texture_slots;
		uint32_t texture_slot_index = 1;

		glm::vec4 quad_vertex_positions[4];

		Renderer2D::Statistics stats;
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
				{ ShaderDataType::Float2, "a_TexCoord" },
				{ ShaderDataType::Float, "a_TexIndex" },
				{ ShaderDataType::Float, "a_TilingFactor" }
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

		int32_t samplers[Data.max_texture_slots];
		for (uint32_t i = 0; i < Data.max_texture_slots; i++)
			samplers[i] = i;

		Data.texture_shader = Shader::create("assets/shaders/Texture.glsl");
		Data.texture_shader->bind();
		Data.texture_shader->set_int_array("u_Textures", samplers, Data.max_texture_slots);

		// set all texture slots to 0
		Data.texture_slots[0] = Data.white_texture;

		Data.quad_vertex_positions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		Data.quad_vertex_positions[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
		Data.quad_vertex_positions[2] = { 0.5f,  0.5f, 0.0f, 1.0f };
		Data.quad_vertex_positions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };
	}

	void Renderer2D::shutdown()
	{
		HM_PROFILE_FUNCTION();

		delete[] Data.quad_vertex_buffer_base;
	}

	void Renderer2D::begin_scene(const Camera& camera, const glm::mat4& transform)
	{
		HM_PROFILE_FUNCTION();

		glm::mat4 viewProj = camera.get_projection() * glm::inverse(transform);

		Data.texture_shader->bind();
		Data.texture_shader->set_mat4("u_ViewProjection", viewProj);

		Data.quad_index_count = 0;
		Data.quad_vertex_buffer_ptr = Data.quad_vertex_buffer_base;

		Data.texture_slot_index = 1;
	}

	void Renderer2D::begin_scene(const OrthographicCamera& camera)
	{
		HM_PROFILE_FUNCTION();

		Data.texture_shader->bind();
		Data.texture_shader->set_mat4("u_ViewProjection", camera.get_view_projection_matrix());

		Data.quad_index_count = 0;
		Data.quad_vertex_buffer_ptr = Data.quad_vertex_buffer_base;

		Data.texture_slot_index = 1;
	}

	void Renderer2D::end_scene()
	{
		HM_PROFILE_FUNCTION();

		uint32_t data_size = (uint32_t)((uint8_t*)Data.quad_vertex_buffer_ptr - (uint8_t*)Data.quad_vertex_buffer_base);

		Data.quad_vertex_buffer->set_data(Data.quad_vertex_buffer_base, data_size);

		flush();
	}

	void Renderer2D::flush()
	{
		if (Data.quad_index_count == 0)
			return; // nothing to draw

		// bind textures
		for (uint32_t i = 0; i < Data.texture_slot_index; i++)
			Data.texture_slots[i]->bind(i);

		RenderCommand::draw_indexed(Data.quad_vertex_array, Data.quad_index_count);
		Data.stats.draw_calls++;
	}

	void Renderer2D::flush_and_reset()
	{
		end_scene();

		Data.quad_index_count = 0;
		Data.quad_vertex_buffer_ptr = Data.quad_vertex_buffer_base;

		Data.texture_slot_index = 1;
	}

	void Renderer2D::draw_quad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		draw_quad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::draw_quad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		HM_PROFILE_FUNCTION();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		draw_quad(transform, color);
	}

	void Renderer2D::draw_quad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tiling_factor, const glm::vec4& tint_color)
	{
		draw_quad({ position.x, position.y, 0.0f }, size, texture, tiling_factor, tint_color);
	}

	void Renderer2D::draw_quad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tiling_factor, const glm::vec4& tint_color)
	{
		HM_PROFILE_FUNCTION();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		draw_quad(transform, texture, tiling_factor);
	}

	void Renderer2D::draw_quad(const glm::mat4& transform, const glm::vec4& color)
	{
		HM_PROFILE_FUNCTION();

		constexpr size_t quadVertexCount = 4;
		const float textureIndex = 0.0f; // white texture
		constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
		const float tilingFactor = 1.0f;

		if (Data.quad_index_count >= Renderer2DData::max_indices)
			flush_and_reset();

		for (size_t i = 0; i < quadVertexCount; i++)
		{
			Data.quad_vertex_buffer_ptr->position = transform * Data.quad_vertex_positions[i];
			Data.quad_vertex_buffer_ptr->color = color;
			Data.quad_vertex_buffer_ptr->tex_coord = textureCoords[i];
			Data.quad_vertex_buffer_ptr->tex_index = textureIndex;
			Data.quad_vertex_buffer_ptr->tiling_factor = tilingFactor;
			Data.quad_vertex_buffer_ptr++;
		}

		Data.quad_index_count += 6;

		Data.stats.quad_count++;
	}

	void Renderer2D::draw_quad(const glm::mat4& transform, const Ref<Texture2D>& texture, float tiling_factor, const glm::vec4& tint_color)
	{
		HM_PROFILE_FUNCTION();

		constexpr size_t quadVertexCount = 4;
		constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };

		if (Data.quad_index_count >= Renderer2DData::max_indices)
			flush_and_reset();

		float textureIndex = 0.0f;
		for (uint32_t i = 1; i < Data.texture_slot_index; i++)
		{
			if (*Data.texture_slots[i].get() == *texture.get())
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f)
		{
			if (Data.texture_slot_index >= Renderer2DData::max_texture_slots)
				flush_and_reset();

			textureIndex = (float)Data.texture_slot_index;
			Data.texture_slots[Data.texture_slot_index] = texture;
			Data.texture_slot_index++;
		}

		for (size_t i = 0; i < quadVertexCount; i++)
		{
			Data.quad_vertex_buffer_ptr->position = transform * Data.quad_vertex_positions[i];
			Data.quad_vertex_buffer_ptr->color = tint_color;
			Data.quad_vertex_buffer_ptr->tex_coord = textureCoords[i];
			Data.quad_vertex_buffer_ptr->tex_index = textureIndex;
			Data.quad_vertex_buffer_ptr->tiling_factor = tiling_factor;
			Data.quad_vertex_buffer_ptr++;
		}

		Data.quad_index_count += 6;

		Data.stats.quad_count++;
	}

	void Renderer2D::draw_rotated_quad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		draw_rotated_quad({ position.x, position.y, 0.0f }, size, rotation, color);
	}

	void Renderer2D::draw_rotated_quad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		HM_PROFILE_FUNCTION();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		draw_quad(transform, color);
	}

	void Renderer2D::draw_rotated_quad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tiling_factor, const glm::vec4& tint_color)
	{
		draw_rotated_quad({ position.x, position.y, 0.0f }, size, rotation, texture, tiling_factor, tint_color);
	}

	void Renderer2D::draw_rotated_quad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tiling_factor, const glm::vec4& tint_color)
	{
		HM_PROFILE_FUNCTION();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		draw_quad(transform, texture, tiling_factor, tint_color);
	}

	void Renderer2D::reset_stats()
	{
		memset(&Data.stats, 0, sizeof(Statistics));
	}

	Renderer2D::Statistics Renderer2D::get_stats()
	{
		return Data.stats;
	}
}