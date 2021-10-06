#include "Application.h"

#include "Harmony/Log.h"

#include "Input.h"

#include <glad/glad.h>

namespace Harmony
{
	#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::Instance = nullptr;

	Application::Application()
	{
		HM_CORE_ASSERT(!Instance, "Application already exists!");
		Instance = this;

		_window = std::unique_ptr<Window>(Window::create());
		_window->set_event_callback(BIND_EVENT_FN(on_event));

		_imgui_layer = new ImGuiLayer();
		push_layer(_imgui_layer);

		_vertex_array.reset(VertexArray::create());

		float vertices[3 * 7] =
		{
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<VertexBuffer> vertex_buffer;;
		vertex_buffer.reset(VertexBuffer::create(vertices, sizeof(vertices)));
		BufferLayout layout =
		{
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" }
		};
		vertex_buffer->set_layout(layout);
		_vertex_array->add_vertex_buffer(vertex_buffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<IndexBuffer> index_buffer;
		index_buffer.reset(IndexBuffer::create(indices, sizeof(indices) / sizeof(uint32_t)));
		_vertex_array->set_index_buffer(index_buffer);

		_suaqre_vertex_array.reset(VertexArray::create());

		float squareVertices[3 * 4] =
		{
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		std::shared_ptr<VertexBuffer> square_vertex_buffer;
		square_vertex_buffer.reset(VertexBuffer::create(squareVertices, sizeof(squareVertices)));
		square_vertex_buffer->set_layout(
			{
			{ ShaderDataType::Float3, "a_Position" }
			}
		);
		_suaqre_vertex_array->add_vertex_buffer(square_vertex_buffer);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<IndexBuffer> square_index_buffer;
		square_index_buffer.reset(IndexBuffer::create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		_suaqre_vertex_array->set_index_buffer(square_index_buffer);

		std::string vertex_source = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);	
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

		_shader.reset(new Shader(vertex_source, fragment_source));

		std::string blue_shader_vertex_source = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);	
			}
		)";

		std::string blue_shader_fragment_source = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		_blue_shader.reset(new Shader(blue_shader_vertex_source, blue_shader_fragment_source));
	}

	Application::~Application()
	{
	}

	void Application::run()
	{
		while (_running)
		{
			glClearColor(0.1, 0.1, 0.1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			_blue_shader->bind();
			_suaqre_vertex_array->bind();
			glDrawElements(GL_TRIANGLES, _suaqre_vertex_array->get_index_buffer()->get_count(), GL_UNSIGNED_INT, nullptr);

			_shader->bind();

			_vertex_array->bind();
			glDrawElements(GL_TRIANGLES, _vertex_array->get_index_buffer()->get_count(), GL_UNSIGNED_INT, nullptr);


			for (Layer* layer : _layer_stack)
				layer->on_update();

			_imgui_layer->begin();
			for (Layer* layer : _layer_stack)
				layer->on_imgui_render();
			_imgui_layer->end();

			_window->on_update();
		}
	}

	void Application::on_event(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(on_window_close));

		for (auto it = _layer_stack.end(); it != _layer_stack.begin(); )
		{
			(*--it)->on_event(e);
			if (e._handled)
				break;
		}
	}

	void Application::push_layer(Layer* layer)
	{
		_layer_stack.push_layer(layer);
		layer->on_attach();
	}

	void Application::push_overlay(Layer* overlay)
	{
		_layer_stack.push_overlay(overlay);
		overlay->on_attach();
	}

	bool Application::on_window_close(WindowCloseEvent& e)
	{
		_running = false;
		return true;
	}
}