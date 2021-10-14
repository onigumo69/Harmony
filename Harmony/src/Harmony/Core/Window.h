#pragma once

#include "Harmony/Core/Core.h"
#include "Harmony/Event/Event.h"

namespace Harmony
{
	struct WindowProps
	{
		std::string _title;
		uint32_t _width;
		uint32_t _height;

		WindowProps(const std::string& title = "Harmony Engine",
					uint32_t width = 1280,
					uint32_t height = 720)
			: _title(title), _width(width), _height(height)
		{}
	};

	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void on_update() = 0;

		virtual uint32_t get_width() const = 0;
		virtual uint32_t get_height() const = 0;

		virtual void set_event_callback(const EventCallbackFn& callback) = 0;
		virtual void set_vsync(bool enabled) = 0;
		virtual bool is_vsync() const = 0;

		virtual void* get_native_window() const = 0;

		static Scope<Window> create(const WindowProps& props = WindowProps());
	};
}