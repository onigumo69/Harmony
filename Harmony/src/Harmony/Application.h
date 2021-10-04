#pragma once

#include "Core.h"
#include "Event/Event.h"
#include "Event/ApplicationEvent.h"

#include "LayerStack.h"
#include "ImGui/ImGuiLayer.h"

#include "Renderer/Shader.h"

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
		ImGuiLayer* _imgui_layer;
		bool _running = true;
		LayerStack _layer_stack;

		unsigned int _vertex_array;
		unsigned int _vertex_buffer;
		unsigned int _index_buffer;
		std::unique_ptr<Shader> _shader;
	private:
		static Application* Instance;
	};

	// to be defined in client side
	Application* create_application();
}