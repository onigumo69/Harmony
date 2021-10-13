#pragma once

#include "Harmony/Core/Window.h"
#include "Harmony/Renderer/GraphicsContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Harmony
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void on_update() override;

		inline unsigned int get_width() const override { return _data._width; }
		inline unsigned int get_height() const override { return _data._height; }

		// Window attributes
		inline void set_event_callback(const EventCallbackFn& callback) override { _data._event_callback = callback; }
		void set_vsync(bool enabled) override;
		bool is_vsync() const override;

		inline virtual void* get_native_window() const { return _window; }
	private:
		virtual void init(const WindowProps& props);
		virtual void shutdown();
	private:
		GLFWwindow* _window;
		Scope<GraphicsContext> _context;

		struct WindowData
		{
			std::string _title;
			unsigned int _width, _height;
			bool _vsync;

			EventCallbackFn _event_callback;
		};

		WindowData _data;
	};
}