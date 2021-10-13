#include "Renderer2D.h"

#include "RenderCommand.h"
#include "Shader.h"
#include "VertexArray.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Harmony
{

	struct Renderer2DStorage
	{
		Ref<VertexArray> quad_vertex_array;
		Ref<Shader> flat_color_shader;
		Ref<Shader> texture_shader;
	};

	static Renderer2DStorage* Data;

	void Renderer2D::init()
	{
		Data = new Renderer2DStorage();
		Data->quad_vertex_array = VertexArray::create();

		float square_vertices[5 * 4] =
		{
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Ref<VertexBuffer> square_vertex_buffer;
		square_vertex_buffer.reset(VertexBuffer::create(square_vertices, sizeof(square_vertices)));
		square_vertex_buffer->set_layout(
			{
				{ ShaderDataType::Float3, "a_Position" },
				{ ShaderDataType::Float2, "a_TexCoord" }
			});
		Data->quad_vertex_array->add_vertex_buffer(square_vertex_buffer);

		uint32_t square_indices[6] = { 0, 1, 2, 2, 3, 0 };
		Ref<IndexBuffer> square_index_buffer;
		square_index_buffer.reset(IndexBuffer::create(square_indices, sizeof(square_indices) / sizeof(uint32_t)));
		Data->quad_vertex_array->set_index_buffer(square_index_buffer);

		Data->flat_color_shader = Shader::create("assets/shaders/FlatColor.glsl");
		Data->texture_shader = Shader::create("assets/shaders/Texture.glsl");
		Data->texture_shader->bind();
		Data->texture_shader->set_int("u_Texture", 0);
	}

	void Renderer2D::shutdown()
	{
		delete Data;
	}

	void Renderer2D::begin_scene(const OrthographicCamera& camera)
	{
		Data->flat_color_shader->bind();
		Data->flat_color_shader->set_mat4("u_ViewProjection", camera.get_view_projection_matrix());

		Data->texture_shader->bind();
		Data->texture_shader->set_mat4("u_ViewProjection", camera.get_view_projection_matrix());
	}

	void Renderer2D::end_scene()
	{

	}

	void Renderer2D::draw_quad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		draw_quad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::draw_quad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		Data->flat_color_shader->bind();
		Data->flat_color_shader->set_float4("u_Color", color);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		Data->flat_color_shader->set_mat4("u_Transform", transform);

		Data->quad_vertex_array->bind();
		RenderCommand::draw_indexed(Data->quad_vertex_array);
	}

	void Renderer2D::draw_quad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture)
	{
		Data->texture_shader->bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		Data->texture_shader->set_mat4("u_Transform", transform);

		texture->bind();

		Data->quad_vertex_array->bind();
		RenderCommand::draw_indexed(Data->quad_vertex_array);
	}

}