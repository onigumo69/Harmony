#include "WindowsWindow.h"

#include "Harmony/Core/Log.h"
#include "Harmony/Core/Input.h"
#include "Harmony/Debug/Instrumentor.h"
#include "Harmony/Event/ApplicationEvent.h"
#include "Harmony/Event/MouseEvent.h"
#include "Harmony/Event/KeyEvent.h"
#include "Harmony/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLContext.h"

namespace Harmony
{

	static uint8_t s_GLFWWindowCount = 0;

	static void GLFWErrorCallback(int error, const char* description)
	{
		HM_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		HM_PROFILE_FUNCTION();

		init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		HM_PROFILE_FUNCTION();

		shutdown();
	}

	void WindowsWindow::init(const WindowProps& props)
	{
		HM_PROFILE_FUNCTION();

		_data._title = props._title;
		_data._width = props._width;
		_data._height = props._height;

		HM_CORE_INFO("Creating window {0} ({1}, {2})", props._title, props._width, props._height);

		if (s_GLFWWindowCount == 0)
		{
			HM_PROFILE_SCOPE("glfwInit");

			// TODO: glfwTerminate on system shutdown
			int success = glfwInit();
			HM_CORE_ASSERT(success, "Could not initialize GLFW!");

			glfwSetErrorCallback(GLFWErrorCallback);
		}

		{
			HM_PROFILE_SCOPE("glfwCreateWindow");

#if defined(HM_DEBUG)
			if (Renderer::get_api() == RendererAPI::API::OpenGL)
				glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif

			_window = glfwCreateWindow((int)props._width, (int)props._height, _data._title.c_str(), nullptr, nullptr);
			++s_GLFWWindowCount;
		}

		_context = GraphicsContext::create(_window);
		_context->init();

		glfwSetWindowUserPointer(_window, &_data);
		set_vsync(true);

		// Set GLFW callbacks
		glfwSetWindowSizeCallback(_window, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data._width = width;
				data._height = height;

				WindowResizeEvent event(width, height);
				data._event_callback(event);
			});

		glfwSetWindowCloseCallback(_window, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				data._event_callback(event);
			});

		glfwSetKeyCallback(_window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(static_cast<KeyCode>(key), 0);
					data._event_callback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(static_cast<KeyCode>(key));
					data._event_callback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(static_cast<KeyCode>(key), 1);
					data._event_callback(event);
					break;
				}
				}
			});

		glfwSetCharCallback(_window, [](GLFWwindow* window, unsigned int keycode)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				KeyTypedEvent event(static_cast<KeyCode>(keycode));
				data._event_callback(event);
			});

		glfwSetMouseButtonCallback(_window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(static_cast<MouseCode>(button));
					data._event_callback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(static_cast<MouseCode>(button));
					data._event_callback(event);
					break;
				}
				}
			});

		glfwSetScrollCallback(_window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				data._event_callback(event);
			});

		glfwSetCursorPosCallback(_window, [](GLFWwindow* window, double xPos, double yPos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseMovedEvent event((float)xPos, (float)yPos);
				data._event_callback(event);
			});
	}

	void WindowsWindow::shutdown()
	{
		HM_PROFILE_FUNCTION();

		glfwDestroyWindow(_window);
		--s_GLFWWindowCount;

		if (s_GLFWWindowCount == 0)
		{
			glfwTerminate();
		}
	}

	void WindowsWindow::on_update()
	{
		HM_PROFILE_FUNCTION();

		glfwPollEvents();
		_context->swap_buffers();
	}

	void WindowsWindow::set_vsync(bool enabled)
	{
		HM_PROFILE_FUNCTION();

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