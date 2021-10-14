#include "Renderer2D.h"

#include "RenderCommand.h"
#include "Shader.h"
#include "VertexArray.h"

#include "Harmony/Debug/Instrumentor.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Harmony
{

	struct Renderer2DStorage
	{
		Ref<VertexArray> quad_vertex_array;
		Ref<Shader> texture_shader;
		Ref<Texture2D> white_texture;
	};

	static Renderer2DStorage* Data;

	void Renderer2D::init()
	{
		HM_PROFILE_FUNCTION();

		Data = new Renderer2DStorage();
		Data->quad_vertex_array = VertexArray::create();

		float square_vertices[5 * 4] =
		{
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Ref<VertexBuffer> square_vertex_buffer = VertexBuffer::create(square_vertices, sizeof(square_vertices));
		square_vertex_buffer->set_layout(
			{
				{ ShaderDataType::Float3, "a_Position" },
				{ ShaderDataType::Float2, "a_TexCoord" }
			});
		Data->quad_vertex_array->add_vertex_buffer(square_vertex_buffer);

		uint32_t square_indices[6] = { 0, 1, 2, 2, 3, 0 };
		Ref<IndexBuffer> square_index_buffer = IndexBuffer::create(square_indices, sizeof(square_indices) / sizeof(uint32_t));
		Data->quad_vertex_array->set_index_buffer(square_index_buffer);

		Data->white_texture = Texture2D::create(1, 1);
		uint32_t white_texture_data = 0xffffffff;
		Data->white_texture->set_data(&white_texture_data, sizeof(uint32_t));

		Data->texture_shader = Shader::create("assets/shaders/Texture.glsl");
		Data->texture_shader->bind();
		Data->texture_shader->set_int("u_Texture", 0);
	}

	void Renderer2D::shutdown()
	{
		HM_PROFILE_FUNCTION();

		delete Data;
	}

	void Renderer2D::begin_scene(const OrthographicCamera& camera)
	{
		HM_PROFILE_FUNCTION();

		Data->texture_shader->bind();
		Data->texture_shader->set_mat4("u_ViewProjection", camera.get_view_projection_matrix());
	}

	void Renderer2D::end_scene()
	{
		HM_PROFILE_FUNCTION();
	}

	void Renderer2D::draw_quad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		draw_quad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::draw_quad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		HM_PROFILE_FUNCTION();

		Data->texture_shader->set_float4("u_Color", color);
		Data->white_texture->bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		Data->texture_shader->set_mat4("u_Transform", transform);

		Data->quad_vertex_array->bind();
		RenderCommand::draw_indexed(Data->quad_vertex_array);
	}

	void Renderer2D::draw_quad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture)
	{
		HM_PROFILE_FUNCTION();

		Data->texture_shader->set_float4("u_Color", glm::vec4(1.0f));
		texture->bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		Data->texture_shader->set_mat4("u_Transform", transform);

		Data->quad_vertex_array->bind();
		RenderCommand::draw_indexed(Data->quad_vertex_array);
	}

}