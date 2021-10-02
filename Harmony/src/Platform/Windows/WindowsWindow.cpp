#include "WindowsWindow.h"

#include "Harmony/Log.h"

namespace Harmony
{

	static bool s_GLFWInitialized = false;

	Window* Window::create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		shutdown();
	}

	void WindowsWindow::init(const WindowProps& props)
	{
		_data._title = props._title;
		_data._width = props._width;
		_data._height = props._height;

		HM_CORE_INFO("Creating window {0} ({1}, {2})", props._title, props._width, props._height);

		if (!s_GLFWInitialized)
		{
			// TODO: glfwTerminate on system shutdown
			int success = glfwInit();
			HM_CORE_ASSERT(success, "Could not intialize GLFW!");

			s_GLFWInitialized = true;
		}

		_window = glfwCreateWindow((int)props._width, (int)props._height, _data._title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(_window);
		glfwSetWindowUserPointer(_window, &_data);
		set_vsync(true);
	}

	void WindowsWindow::shutdown()
	{
		glfwDestroyWindow(_window);
	}

	void WindowsWindow::on_update()
	{
		glfwPollEvents();
		glfwSwapBuffers(_window);
	}

	void WindowsWindow::set_vsync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		_data._vsync = enabled;
	}

	bool WindowsWindow::is_vsync() const
	{
		return _data._vsync;
	}

}