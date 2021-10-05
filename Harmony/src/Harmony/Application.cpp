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

		glGenVertexArrays(1, &_vertex_array);
		glBindVertexArray(_vertex_array);

		float vertices[3 * 3] =
		{
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};

		_vertex_buffer.reset(VertexBuffer::create(vertices, sizeof(vertices)));

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		uint32_t indices[3] = { 0, 1, 2 };
		_index_buffer.reset(IndexBuffer::create(indices, sizeof(indices) / sizeof(uint32_t)));

		std::string vertex_source = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);	
			}
		)";

		std::string fragment_source = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
			}
		)";

		_shader.reset(new Shader(vertex_source, fragment_source));
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

			_shader->bind();

			glBindVertexArray(_vertex_array);
			glDrawElements(GL_TRIANGLES, _index_buffer->get_count(), GL_UNSIGNED_INT, nullptr);

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