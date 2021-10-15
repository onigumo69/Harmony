#pragma once

#include "Event.h"
#include "Harmony/Core/Input.h"

#include <sstream>

namespace Harmony
{
	class KeyEvent : public Event
	{
	public:
		inline KeyCode get_keycode() const { return _keycode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		KeyEvent(const KeyCode keycode)
			: _keycode(keycode)
		{}

		KeyCode _keycode;
	};

	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(const KeyCode keycode, const int repeat_count)
			: KeyEvent(keycode), _repeat_count(repeat_count)
		{}

		uint16_t get_repeat_count() const { return _repeat_count; }

		std::string debug_to_string() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << static_cast<int>(_keycode) << " (" << _repeat_count << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		uint16_t _repeat_count;
	};

	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(const KeyCode keycode)
			: KeyEvent(keycode)
		{}

		std::string debug_to_string() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << static_cast<int>(_keycode);
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

	class KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(const KeyCode keycode)
			: KeyEvent(keycode) {}

		std::string debug_to_string() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << static_cast<int>(_keycode);
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};
}