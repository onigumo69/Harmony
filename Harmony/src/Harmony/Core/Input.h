#pragma once

#include "Core.h"

#include <utility>

namespace Harmony
{
	class Input
	{
	public:
		inline static bool is_key_pressed(int keycode) { return Instance->is_key_pressed_impl(keycode); }

		inline static bool is_mouse_button_pressed(int button) { return Instance->is_mouse_button_pressed_impl(button); }

		inline static float get_mouse_x() { return Instance->get_mouse_x_impl(); }
		inline static float get_mouse_y() { return Instance->get_mouse_y_impl(); }
		
	protected:
		virtual bool is_key_pressed_impl(int keycode) = 0;

		virtual bool is_mouse_button_pressed_impl(int button) = 0;

		virtual std::pair<float, float> get_mouse_position_impl() = 0;
		virtual float get_mouse_x_impl() = 0;
		virtual float get_mouse_y_impl() = 0;

	private:
		static Input* Instance;
	};
}