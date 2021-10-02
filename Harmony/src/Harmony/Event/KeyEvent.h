#pragma once

#include "Event.h"

#include <sstream>

namespace Harmony
{
	class HARMONY_API KeyEvent : public Event
	{
	public:
		inline int get_keycode() const { return _keycode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		KeyEvent(int keycode)
			: _keycode(keycode)
		{}

		int _keycode;
	};

	class HARMONY_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode, int repeat_count)
			: KeyEvent(keycode), _repeat_count(repeat_count)
		{}

		inline int get_repeat_count() const { return _repeat_count; }

		std::string debug_to_string() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << _keycode << " (" << _repeat_count << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int _repeat_count;
	};

	class HARMONY_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode)
			: KeyEvent(keycode)
		{}

		std::string debug_to_string() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << _keycode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};
}