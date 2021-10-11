#include "WindowsInput.h"

#include "Harmony/Core/Application.h"
#include <GLFW/glfw3.h>

#include <utility>

namespace Harmony
{

	Input* Input::Instance = new WindowsInput();

	bool WindowsInput::is_key_pressed_impl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::get().get_window().get_native_window());
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::is_mouse_button_pressed_impl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::get().get_window().get_native_window());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> WindowsInput::get_mouse_position_impl()
	{
		auto window = static_cast<GLFWwindow*>(Application::get().get_window().get_native_window());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}

	float WindowsInput::get_mouse_x_impl()
	{
		std::pair<float, float> pos = get_mouse_position_impl();
		return pos.first;
	}

	float WindowsInput::get_mouse_y_impl()
	{
		std::pair<float, float> pos = get_mouse_position_impl();
		return pos.second;
	}
}