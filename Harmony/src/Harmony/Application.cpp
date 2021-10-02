#include "Application.h"

#include "Harmony/Log.h"
#include "Harmony/Event/ApplicationEvent.h"

#include <GLFW/glfw3.h>

namespace Harmony
{

	Application::Application()
	{
		_window = std::unique_ptr<Window>(Window::create());
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

}