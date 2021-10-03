#include "Application.h"

#include "Harmony/Log.h"

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
	}


	Application::~Application()
	{
	}

	void Application::run()
	{
		while (_running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : _layer_stack)
				layer->on_update();

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