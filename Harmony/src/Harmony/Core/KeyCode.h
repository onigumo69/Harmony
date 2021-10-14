#pragma once

namespace Harmony
{
	typedef enum class KeyCode : uint16_t
	{
		// From glfw3.h
		Space = 32,
		Apostrophe = 39, /* ' */
		Comma = 44, /* , */
		Minus = 45, /* - */
		Period = 46, /* . */
		Slash = 47, /* / */

		D0 = 48, /* 0 */
		D1 = 49, /* 1 */
		D2 = 50, /* 2 */
		D3 = 51, /* 3 */
		D4 = 52, /* 4 */
		D5 = 53, /* 5 */
		D6 = 54, /* 6 */
		D7 = 55, /* 7 */
		D8 = 56, /* 8 */
		D9 = 57, /* 9 */

		Semicolon = 59, /* ; */
		Equal = 61, /* = */

		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,

		LeftBracket = 91,  /* [ */
		Backslash = 92,  /* \ */
		RightBracket = 93,  /* ] */
		GraveAccent = 96,  /* ` */

		World1 = 161, /* non-US #1 */
		World2 = 162, /* non-US #2 */

		/* Function keys */
		Escape = 256,
		Enter = 257,
		Tab = 258,
		Backspace = 259,
		Insert = 260,
		Delete = 261,
		Right = 262,
		Left = 263,
		Down = 264,
		Up = 265,
		PageUp = 266,
		PageDown = 267,
		Home = 268,
		End = 269,
		CapsLock = 280,
		ScrollLock = 281,
		NumLock = 282,
		PrintScreen = 283,
		Pause = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,

		/* Keypad */
		KP0 = 320,
		KP1 = 321,
		KP2 = 322,
		KP3 = 323,
		KP4 = 324,
		KP5 = 325,
		KP6 = 326,
		KP7 = 327,
		KP8 = 328,
		KP9 = 329,
		KPDecimal = 330,
		KPDivide = 331,
		KPMultiply = 332,
		KPSubtract = 333,
		KPAdd = 334,
		KPEnter = 335,
		KPEqual = 336,

		LeftShift = 340,
		LeftControl = 341,
		LeftAlt = 342,
		LeftSuper = 343,
		RightShift = 344,
		RightControl = 345,
		RightAlt = 346,
		RightSuper = 347,
		Menu = 348
	} Key;

	//inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	//{
	//	os << static_cast<int32_t>(keyCode);
	//	return os;
	//}
}

// From glfw3.h
#define HM_KEY_SPACE           ::Harmony::Key::Space
#define HM_KEY_APOSTROPHE      ::Harmony::Key::Apostrophe    /* ' */
#define HM_KEY_COMMA           ::Harmony::Key::Comma         /* , */
#define HM_KEY_MINUS           ::Harmony::Key::Minus         /* - */
#define HM_KEY_PERIOD          ::Harmony::Key::Period        /* . */
#define HM_KEY_SLASH           ::Harmony::Key::Slash         /* / */
#define HM_KEY_0               ::Harmony::Key::D0
#define HM_KEY_1               ::Harmony::Key::D1
#define HM_KEY_2               ::Harmony::Key::D2
#define HM_KEY_3               ::Harmony::Key::D3
#define HM_KEY_4               ::Harmony::Key::D4
#define HM_KEY_5               ::Harmony::Key::D5
#define HM_KEY_6               ::Harmony::Key::D6
#define HM_KEY_7               ::Harmony::Key::D7
#define HM_KEY_8               ::Harmony::Key::D8
#define HM_KEY_9               ::Harmony::Key::D9
#define HM_KEY_SEMICOLON       ::Harmony::Key::Semicolon     /* ; */
#define HM_KEY_EQUAL           ::Harmony::Key::Equal         /* = */
#define HM_KEY_A               ::Harmony::Key::A
#define HM_KEY_B               ::Harmony::Key::B
#define HM_KEY_C               ::Harmony::Key::C
#define HM_KEY_D               ::Harmony::Key::D
#define HM_KEY_E               ::Harmony::Key::E
#define HM_KEY_F               ::Harmony::Key::F
#define HM_KEY_G               ::Harmony::Key::G
#define HM_KEY_H               ::Harmony::Key::H
#define HM_KEY_I               ::Harmony::Key::I
#define HM_KEY_J               ::Harmony::Key::J
#define HM_KEY_K               ::Harmony::Key::K
#define HM_KEY_L               ::Harmony::Key::L
#define HM_KEY_M               ::Harmony::Key::M
#define HM_KEY_N               ::Harmony::Key::N
#define HM_KEY_O               ::Harmony::Key::O
#define HM_KEY_P               ::Harmony::Key::P
#define HM_KEY_Q               ::Harmony::Key::Q
#define HM_KEY_R               ::Harmony::Key::R
#define HM_KEY_S               ::Harmony::Key::S
#define HM_KEY_T               ::Harmony::Key::T
#define HM_KEY_U               ::Harmony::Key::U
#define HM_KEY_V               ::Harmony::Key::V
#define HM_KEY_W               ::Harmony::Key::W
#define HM_KEY_X               ::Harmony::Key::X
#define HM_KEY_Y               ::Harmony::Key::Y
#define HM_KEY_Z               ::Harmony::Key::Z
#define HM_KEY_LEFT_BRACKET    ::Harmony::Key::LeftBracket   /* [ */
#define HM_KEY_BACKSLASH       ::Harmony::Key::Backslash     /* \ */
#define HM_KEY_RIGHT_BRACKET   ::Harmony::Key::RightBracket  /* ] */
#define HM_KEY_GRAVE_ACCENT    ::Harmony::Key::GraveAccent   /* ` */
#define HM_KEY_WORLD_1         ::Harmony::Key::World1        /* non-US #1 */
#define HM_KEY_WORLD_2         ::Harmony::Key::World2        /* non-US #2 */

/* Function keys */
#define HM_KEY_ESCAPE          ::Harmony::Key::Escape
#define HM_KEY_ENTER           ::Harmony::Key::Enter
#define HM_KEY_TAB             ::Harmony::Key::Tab
#define HM_KEY_BACKSPACE       ::Harmony::Key::Backspace
#define HM_KEY_INSERT          ::Harmony::Key::Insert
#define HM_KEY_DELETE          ::Harmony::Key::Delete
#define HM_KEY_RIGHT           ::Harmony::Key::Right
#define HM_KEY_LEFT            ::Harmony::Key::Left
#define HM_KEY_DOWN            ::Harmony::Key::Down
#define HM_KEY_UP              ::Harmony::Key::Up
#define HM_KEY_PAGE_UP         ::Harmony::Key::PageUp
#define HM_KEY_PAGE_DOWN       ::Harmony::Key::PageDown
#define HM_KEY_HOME            ::Harmony::Key::Home
#define HM_KEY_END             ::Harmony::Key::End
#define HM_KEY_CAPS_LOCK       ::Harmony::Key::CapsLock
#define HM_KEY_SCROLL_LOCK     ::Harmony::Key::ScrollLock
#define HM_KEY_NUM_LOCK        ::Harmony::Key::NumLock
#define HM_KEY_PRINT_SCREEN    ::Harmony::Key::PrintScreen
#define HM_KEY_PAUSE           ::Harmony::Key::Pause
#define HM_KEY_F1              ::Harmony::Key::F1
#define HM_KEY_F2              ::Harmony::Key::F2
#define HM_KEY_F3              ::Harmony::Key::F3
#define HM_KEY_F4              ::Harmony::Key::F4
#define HM_KEY_F5              ::Harmony::Key::F5
#define HM_KEY_F6              ::Harmony::Key::F6
#define HM_KEY_F7              ::Harmony::Key::F7
#define HM_KEY_F8              ::Harmony::Key::F8
#define HM_KEY_F9              ::Harmony::Key::F9
#define HM_KEY_F10             ::Harmony::Key::F10
#define HM_KEY_F11             ::Harmony::Key::F11
#define HM_KEY_F12             ::Harmony::Key::F12
#define HM_KEY_F13             ::Harmony::Key::F13
#define HM_KEY_F14             ::Harmony::Key::F14
#define HM_KEY_F15             ::Harmony::Key::F15
#define HM_KEY_F16             ::Harmony::Key::F16
#define HM_KEY_F17             ::Harmony::Key::F17
#define HM_KEY_F18             ::Harmony::Key::F18
#define HM_KEY_F19             ::Harmony::Key::F19
#define HM_KEY_F20             ::Harmony::Key::F20
#define HM_KEY_F21             ::Harmony::Key::F21
#define HM_KEY_F22             ::Harmony::Key::F22
#define HM_KEY_F23             ::Harmony::Key::F23
#define HM_KEY_F24             ::Harmony::Key::F24
#define HM_KEY_F25             ::Harmony::Key::F25

/* Keypad */
#define HM_KEY_KP_0            ::Harmony::Key::KP0
#define HM_KEY_KP_1            ::Harmony::Key::KP1
#define HM_KEY_KP_2            ::Harmony::Key::KP2
#define HM_KEY_KP_3            ::Harmony::Key::KP3
#define HM_KEY_KP_4            ::Harmony::Key::KP4
#define HM_KEY_KP_5            ::Harmony::Key::KP5
#define HM_KEY_KP_6            ::Harmony::Key::KP6
#define HM_KEY_KP_7            ::Harmony::Key::KP7
#define HM_KEY_KP_8            ::Harmony::Key::KP8
#define HM_KEY_KP_9            ::Harmony::Key::KP9
#define HM_KEY_KP_DECIMAL      ::Harmony::Key::KPDecimal
#define HM_KEY_KP_DIVIDE       ::Harmony::Key::KPDivide
#define HM_KEY_KP_MULTIPLY     ::Harmony::Key::KPMultiply
#define HM_KEY_KP_SUBTRACT     ::Harmony::Key::KPSubtract
#define HM_KEY_KP_ADD          ::Harmony::Key::KPAdd
#define HM_KEY_KP_ENTER        ::Harmony::Key::KPEnter
#define HM_KEY_KP_EQUAL        ::Harmony::Key::KPEqual

#define HM_KEY_LEFT_SHIFT      ::Harmony::Key::LeftShift
#define HM_KEY_LEFT_CONTROL    ::Harmony::Key::LeftControl
#define HM_KEY_LEFT_ALT        ::Harmony::Key::LeftAlt
#define HM_KEY_LEFT_SUPER      ::Harmony::Key::LeftSuper
#define HM_KEY_RIGHT_SHIFT     ::Harmony::Key::RightShift
#define HM_KEY_RIGHT_CONTROL   ::Harmony::Key::RightControl
#define HM_KEY_RIGHT_ALT       ::Harmony::Key::RightAlt
#define HM_KEY_RIGHT_SUPER     ::Harmony::Key::RightSuper
#define HM_KEY_MENU            ::Harmony::Key::Menu