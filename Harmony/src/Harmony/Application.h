#pragma once

#include "Core.h"
#include "Event/Event.h"
#include "Event/ApplicationEvent.h"

#include "Window.h"

#include <memory>

namespace Harmony
{
	class HARMONY_API Application
	{
	public:
		Application();
		virtual ~Application();

		void run();

		void on_event(Event& e);
	private:
		bool on_window_close(WindowCloseEvent& e);

		std::unique_ptr<Window> _window;
		bool _running = true;
	};

	// to be defined in client side
	Application* create_application();
}