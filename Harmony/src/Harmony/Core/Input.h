#pragma once

#include "Core.h"
#include "KeyCode.h"
#include "MouseCode.h"

#include <glm/glm.hpp>

namespace Harmony
{
	class Input
	{
	public:
		static bool is_key_pressed(KeyCode key);
		static bool is_mouse_button_pressed(MouseCode button);
		static glm::vec2 get_mouse_position();
		static float get_mouse_x();
		static float get_mouse_y();
	};
}