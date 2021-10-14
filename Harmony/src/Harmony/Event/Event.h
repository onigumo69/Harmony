#pragma once

#include "Harmony/Core/Core.h"

#include <string>
#include <functional>
#include <ostream>

namespace Harmony
{
	// currently blocking. TODO : a better solution

	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};

#define EVENT_CLASS_TYPE(type) static EventType get_static_type() { return EventType::##type; }\
							   virtual EventType get_event_type() const override { return get_static_type(); }\
							   virtual const char* get_name() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int get_category_flags() const override { return category; }

	class Event
	{
	public:
		bool _handled = false;

		virtual EventType get_event_type() const = 0;
		virtual const char* get_name() const = 0;
		virtual int get_category_flags() const = 0;
		virtual std::string debug_to_string() const { return get_name(); }

		inline bool is_in_category(EventCategory category) { return get_category_flags() & category; }
	};

	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event)
			: _event(event)
		{}

		template<typename T>
		bool dispatch(EventFn<T> func)
		{
			if (_event.get_event_type() == T::get_static_type())
			{
				_event._handled = func(*(T*)&_event);
				return true;
			}
			return false;
		}

	private:
		Event& _event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.debug_to_string();
	}
}