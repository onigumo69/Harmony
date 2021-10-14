#pragma once

#include "Core.h"
#include "Harmony/Event/Event.h"
#include "Harmony/Event/ApplicationEvent.h"

#include "Timestep.h"

#include "LayerStack.h"
#include "Harmony/ImGui/ImGuiLayer.h"

#include "Harmony/Renderer/OrthographicCamera.h"

#include "Window.h"

#include <memory>

int main(int argc, char** argv);

namespace Harmony
{
	class Application
	{
	public:
		Application(const std::string& name = "Harmony Core");
		virtual ~Application();

		void on_event(Event& e);

		void push_layer(Layer* layer);
		void push_overlay(Layer* overlay);

		inline Window& get_window() { return *_window; }

		void close();

		ImGuiLayer* get_imgui_layer() { return _imgui_layer; }

		inline static Application& get() { return *Instance; }
	private:
		void run();
		bool on_window_close(WindowCloseEvent& e);
		bool on_window_resize(WindowResizeEvent& e);

		std::unique_ptr<Window> _window;
		ImGuiLayer* _imgui_layer;
		bool _running = true;
		bool _minimized = false;
		LayerStack _layer_stack;

		float _last_frame_time = 0.0f;
	private:
		static Application* Instance;
		friend int ::main(int argc, char** argv);
	};

	// to be defined in client side
	Application* create_application();
}