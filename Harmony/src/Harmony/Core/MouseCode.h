#pragma once

#include <ostream>

namespace Harmony
{
	typedef enum class MouseCode : uint16_t
	{
		// From glfw3.h
		Button0 = 0,
		Button1 = 1,
		Button2 = 2,
		Button3 = 3,
		Button4 = 4,
		Button5 = 5,
		Button6 = 6,
		Button7 = 7,

		ButtonLast = Button7,
		ButtonLeft = Button0,
		ButtonRight = Button1,
		ButtonMiddle = Button2
	} Mouse;

	inline std::ostream& operator<<(std::ostream& os, MouseCode mouseCode)
	{
		os << static_cast<int32_t>(mouseCode);
		return os;
	}
}

#define HM_MOUSE_BUTTON_0      ::Harmony::Mouse::Button0
#define HM_MOUSE_BUTTON_1      ::Harmony::Mouse::Button1
#define HM_MOUSE_BUTTON_2      ::Harmony::Mouse::Button2
#define HM_MOUSE_BUTTON_3      ::Harmony::Mouse::Button3
#define HM_MOUSE_BUTTON_4      ::Harmony::Mouse::Button4
#define HM_MOUSE_BUTTON_5      ::Harmony::Mouse::Button5
#define HM_MOUSE_BUTTON_6      ::Harmony::Mouse::Button6
#define HM_MOUSE_BUTTON_7      ::Harmony::Mouse::Button7
#define HM_MOUSE_BUTTON_LAST   ::Harmony::Mouse::ButtonLast
#define HM_MOUSE_BUTTON_LEFT   ::Harmony::Mouse::ButtonLeft
#define HM_MOUSE_BUTTON_RIGHT  ::Harmony::Mouse::ButtonRight
#define HM_MOUSE_BUTTON_MIDDLE ::Harmony::Mouse::ButtonMiddle