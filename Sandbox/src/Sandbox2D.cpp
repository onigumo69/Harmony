#include "Sandbox2D.h"
#include "imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), _camera_controller(1280.0f / 720.0f)
{
}

void Sandbox2D::on_attach()
{
	_square_vertex_array = Harmony::VertexArray::create();

	float square_vertices[5 * 4] =
	{
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	Harmony::Ref<Harmony::VertexBuffer> square_vertex_buffer;
	square_vertex_buffer.reset(Harmony::VertexBuffer::create(square_vertices, sizeof(square_vertices)));
	square_vertex_buffer->set_layout(
		{
			{ Harmony::ShaderDataType::Float3, "a_Position" }
		}
	);
	_square_vertex_array->add_vertex_buffer(square_vertex_buffer);

	uint32_t square_indices[6] = { 0, 1, 2, 2, 3, 0 };
	Harmony::Ref<Harmony::IndexBuffer> square_index_buffer;
	square_index_buffer.reset(Harmony::IndexBuffer::create(square_indices, sizeof(square_indices) / sizeof(uint32_t)));
	_square_vertex_array->set_index_buffer(square_index_buffer);

	_flat_color_shader = Harmony::Shader::create("assets/shaders/FlatColor.glsl");
}

void Sandbox2D::on_detach()
{
}

void Sandbox2D::on_update(Harmony::Timestep ts)
{
	// Update
	_camera_controller.on_update(ts);

	// Render
	Harmony::RenderCommand::set_clear_color({ 0.1f, 0.1f, 0.1f, 1 });
	Harmony::RenderCommand::clear();

	Harmony::Renderer::begin_scene(_camera_controller.get_camera());

	std::dynamic_pointer_cast<Harmony::OpenGLShader>(_flat_color_shader)->bind();
	std::dynamic_pointer_cast<Harmony::OpenGLShader>(_flat_color_shader)->upload_uniform_float4("u_Color", _square_color);

	Harmony::Renderer::submit(_flat_color_shader, _square_vertex_array, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	Harmony::Renderer::end_scene();
}

void Sandbox2D::on_imgui_render()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(_square_color));
	ImGui::End();
}

void Sandbox2D::on_event(Harmony::Event& e)
{
	_camera_controller.on_event(e);
}