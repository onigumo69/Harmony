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

		glGenBuffers(1, &_vertex_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer);

		float vertices[3 * 3] =
		{
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		glGenBuffers(1, &_index_buffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _index_buffer);

		unsigned int indices[3] = { 0, 1, 2 };
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
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

			glBindVertexArray(_vertex_array);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

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