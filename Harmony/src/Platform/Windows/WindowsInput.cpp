#include "Harmony/Core/Input.h"

#include "Harmony/Core/Application.h"
#include <GLFW/glfw3.h>

#include <utility>

namespace Harmony
{

	bool Input::is_key_pressed(KeyCode keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::get().get_window().get_native_window());
		auto state = glfwGetKey(window, static_cast<int32_t>(keycode));
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Input::is_mouse_button_pressed(MouseCode button)
	{
		auto window = static_cast<GLFWwindow*>(Application::get().get_window().get_native_window());
		auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));
		return state == GLFW_PRESS;
	}

	std::pair<float, float> Input::get_mouse_position()
	{
		auto window = static_cast<GLFWwindow*>(Application::get().get_window().get_native_window());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}

	float Input::get_mouse_x()
	{
		std::pair<float, float> pos = get_mouse_position();
		return pos.first;
	}

	float Input::get_mouse_y()
	{
		std::pair<float, float> pos = get_mouse_position();
		return pos.second;
	}
}