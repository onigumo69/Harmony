#include <Harmony.h>

#include "imgui.h"

class ExampleLayer : public Harmony::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), _camera(-1.6f, 1.6f, -0.9f, 0.9f), _camera_position(0.0f)
	{
		_vertex_array.reset(Harmony::VertexArray::create());

		float vertices[3 * 7] =
		{
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<Harmony::VertexBuffer> vertex_buffer;
		vertex_buffer.reset(Harmony::VertexBuffer::create(vertices, sizeof(vertices)));
		Harmony::BufferLayout layout =
		{
			{ Harmony::ShaderDataType::Float3, "a_Position" },
			{ Harmony::ShaderDataType::Float4, "a_Color" }
		};
		vertex_buffer->set_layout(layout);
		_vertex_array->add_vertex_buffer(vertex_buffer);


		uint32_t indices[3] = { 0,1,2 };
		std::shared_ptr<Harmony::IndexBuffer> index_buffer;
		index_buffer.reset(Harmony::IndexBuffer::create(indices, sizeof(indices) / sizeof(uint32_t)));
		_vertex_array->set_index_buffer(index_buffer);

		_square_vertex_array.reset(Harmony::VertexArray::create());

		float square_vertices[3 * 4] =
		{
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		std::shared_ptr<Harmony::VertexBuffer> square_vertex_buffer;
		square_vertex_buffer.reset(Harmony::VertexBuffer::create(square_vertices, sizeof(square_vertices)));
		square_vertex_buffer->set_layout(
			{
				{ Harmony::ShaderDataType::Float3, "a_Position" }
			});
		_square_vertex_array->add_vertex_buffer(square_vertex_buffer);


		uint32_t square_indices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Harmony::IndexBuffer> square_index_buffer;
		square_index_buffer.reset(Harmony::IndexBuffer::create(square_indices, sizeof(square_indices) / sizeof(uint32_t)));
		_square_vertex_array->set_index_buffer(square_index_buffer);

		std::string vertex_source = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
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

		_shader.reset(new Harmony::Shader(vertex_source, fragment_source));


		std::string blue_vertex_source = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
			}
		)";

		std::string blue_fragment_source = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		_blue_shader.reset(new Harmony::Shader(blue_vertex_source, blue_fragment_source));
	}

	void on_update(Harmony::Timestep ts) override
	{
		if (Harmony::Input::is_key_pressed(HM_KEY_LEFT))
			_camera_position.x -= _camera_move_speed * ts;
		else if (Harmony::Input::is_key_pressed(HM_KEY_RIGHT))
			_camera_position.x += _camera_move_speed * ts;

		if(Harmony::Input::is_key_pressed(HM_KEY_UP))
			_camera_position.y += _camera_move_speed * ts;
		else if (Harmony::Input::is_key_pressed(HM_KEY_DOWN))
			_camera_position.y -= _camera_move_speed * ts;

		if (Harmony::Input::is_key_pressed(HM_KEY_A))
			_camera_rotation += _camera_move_speed * ts;
		else if (Harmony::Input::is_key_pressed(HM_KEY_D))
			_camera_rotation -= _camera_move_speed * ts;

		Harmony::RenderCommand::set_clear_color({ 0.1f, 0.1f, 0.1f, 1.0f });
		Harmony::RenderCommand::clear();

		_camera.set_position(_camera_position);
		_camera.set_rotation(_camera_rotation);

		Harmony::Renderer::begin_scene(_camera);

		Harmony::Renderer::submit(_blue_shader, _square_vertex_array);
		Harmony::Renderer::submit(_shader, _vertex_array);

		Harmony::Renderer::end_scene();
	}

	virtual void on_imgui_render() override
	{

	}

	void on_event(Harmony::Event& event) override
	{

	}
private:
	std::shared_ptr<Harmony::Shader> _shader;
	std::shared_ptr<Harmony::VertexArray> _vertex_array;

	std::shared_ptr<Harmony::Shader> _blue_shader;
	std::shared_ptr<Harmony::VertexArray> _square_vertex_array;

	Harmony::OrthographicCamera _camera;
	glm::vec3 _camera_position;
	float _camera_move_speed = 5.0f;
	float _camera_rotation = 0.0f;
	float _camera_rotation_speed = 180.0f;
};

class Sandbox : public Harmony::Application
{
public:
	Sandbox()
	{
		push_layer(new ExampleLayer());
	}

	~Sandbox()
	{

	}

};

Harmony::Application* Harmony::create_application()
{
	return new Sandbox();
}