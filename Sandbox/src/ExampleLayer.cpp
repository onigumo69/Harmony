#include "ExampleLayer.h"

#include <imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

ExampleLayer::ExampleLayer()
	: Layer("ExampleLayer"), _camera_controller(1280.0f / 720.0f)
{
	_vertex_array = Harmony::VertexArray::create();

	float vertices[3 * 7] =
	{
		-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
		 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
		 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
	};

	Harmony::Ref<Harmony::VertexBuffer> vertex_buffer = Harmony::VertexBuffer::create(vertices, sizeof(vertices));
	Harmony::BufferLayout layout = {
		{ Harmony::ShaderDataType::Float3, "a_Position" },
		{ Harmony::ShaderDataType::Float4, "a_Color" }
	};
	vertex_buffer->set_layout(layout);
	_vertex_array->add_vertex_buffer(vertex_buffer);

	uint32_t indices[3] = { 0, 1, 2 };
	Harmony::Ref<Harmony::IndexBuffer> index_buffer = Harmony::IndexBuffer::create(indices, sizeof(indices) / sizeof(uint32_t));
	_vertex_array->set_index_buffer(index_buffer);

	_square_vertex_array = Harmony::VertexArray::create();

	float square_vertices[5 * 4] =
	{
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
	};

	Harmony::Ref<Harmony::VertexBuffer> square_vertex_buffer = Harmony::VertexBuffer::create(square_vertices, sizeof(square_vertices));
	square_vertex_buffer->set_layout({
		{ Harmony::ShaderDataType::Float3, "a_Position" },
		{ Harmony::ShaderDataType::Float2, "a_TexCoord" }
		});
	_square_vertex_array->add_vertex_buffer(square_vertex_buffer);

	uint32_t square_indices[6] = { 0, 1, 2, 2, 3, 0 };
	Harmony::Ref<Harmony::IndexBuffer> square_index_buffer = Harmony::IndexBuffer::create(square_indices, sizeof(square_indices) / sizeof(uint32_t));
	_square_vertex_array->set_index_buffer(square_index_buffer);

	std::string vertex_source = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

	std::string fragment_source = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

	_shader = Harmony::Shader::create("VertexPosColor", vertex_source, fragment_source);

	std::string flat_color_vertex_source = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

	std::string flat_color_fragment_source = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			
			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

	_flat_color_shader = Harmony::Shader::create("FlatColor", flat_color_vertex_source, flat_color_fragment_source);

	auto texture_shader = _shader_library.load("assets/shaders/Texture.glsl");

	_texture = Harmony::Texture2D::create("assets/textures/Checkerboard.png");
	_grass_texture = Harmony::Texture2D::create("assets/textures/Grass.png");

	texture_shader->bind();
	texture_shader->set_int("u_Texture", 0);
}

void ExampleLayer::on_attach()
{
}

void ExampleLayer::on_detach()
{
}

void ExampleLayer::on_update(Harmony::Timestep ts)
{
	// Update
	_camera_controller.on_update(ts);

	// Render
	Harmony::RenderCommand::set_clear_color({ 0.1f, 0.1f, 0.1f, 1 });
	Harmony::RenderCommand::clear();

	Harmony::Renderer::begin_scene(_camera_controller.get_camera());

	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

	_flat_color_shader->bind();
	_flat_color_shader->set_float3("u_Color", _square_color);

	for (int y = 0; y < 20; y++)
	{
		for (int x = 0; x < 20; x++)
		{
			glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
			Harmony::Renderer::submit(_flat_color_shader, _square_vertex_array, transform);
		}
	}

	auto texture_shader = _shader_library.get("Texture");

	_texture->bind();
	Harmony::Renderer::submit(texture_shader, _square_vertex_array, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
	_grass_texture->bind();
	Harmony::Renderer::submit(texture_shader, _square_vertex_array, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	Harmony::Renderer::end_scene();
}

void ExampleLayer::on_imgui_render()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Square Color", glm::value_ptr(_square_color));
	ImGui::End();
}

void ExampleLayer::on_event(Harmony::Event& e)
{
	_camera_controller.on_event(e);
}