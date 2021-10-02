#include "Application.h"

#include "Harmony/Log.h"

#include <GLFW/glfw3.h>

namespace Harmony
{
	#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application()
	{
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
			_window->on_update();
		}
	}

	void Application::on_event(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(on_window_close));

		HM_CORE_TRACE("{0}", e);
	}

	bool Application::on_window_close(WindowCloseEvent& e)
	{
		_running = false;
		return true;
	}
}