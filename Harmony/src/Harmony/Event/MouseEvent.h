#pragma once

#include "Event.h"

#include <sstream>

namespace Harmony
{
	class HARMONY_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y)
			: _mouseX(x), _mouseY(y)
		{}

		inline float get_x() const { return _mouseX; }
		inline float get_y() const { return _mouseY; }

		std::string debug_to_string() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << _mouseX << ", " << _mouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float _mouseX, _mouseY;
	};

	class HARMONY_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float x_offset, float y_offset)
			: _x_offset(x_offset), _y_offset(y_offset)
		{}

		inline float get_x_offset() const { return _x_offset; }
		inline float get_y_offset() const { return _y_offset; }

		std::string debug_to_string() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << get_x_offset() << ", " << get_y_offset();
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float _x_offset, _y_offset;
	};

	class HARMONY_API MouseButtonEvent : public Event
	{
	public:
		inline int get_mouse_button() const { return _button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	protected:
		MouseButtonEvent(int button)
			: _button(button)
		{}

		int _button;
	};

	class HARMONY_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button)
			: MouseButtonEvent(button)
		{}

		std::string debug_to_string() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << _button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class HARMONY_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button)
			: MouseButtonEvent(button) {}

		std::string debug_to_string() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << _button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}