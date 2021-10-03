#pragma once

#include "Core.h"
#include "Event/Event.h"
#include "Event/ApplicationEvent.h"

#include "LayerStack.h"

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

		void push_layer(Layer* layer);
		void push_overlay(Layer* overlay);

		inline Window& get_window() { return *_window; }

		inline static Application& get() { return *Instance; }
	private:
		bool on_window_close(WindowCloseEvent& e);

		std::unique_ptr<Window> _window;
		bool _running = true;
		LayerStack _layer_stack;
	private:
		static Application* Instance;
	};

	// to be defined in client side
	Application* create_application();
}