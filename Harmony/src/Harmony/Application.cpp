#include "Application.h"

#include "Harmony/Log.h"

#include "Input.h"

#include "Harmony/Renderer/Renderer.h"

#include <GLFW/glfw3.h>

namespace Harmony
{
	#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::Instance = nullptr;

	Application::Application()
	{
		HM_CORE_ASSERT(!Instance, "Application already exists!");
		Instance = this;

		_window = std::unique_ptr<Window>(Window::create());
		_window->set_event_callback(BIND_EVENT_FN(on_event));

		_imgui_layer = new ImGuiLayer();
		push_overlay(_imgui_layer);
	}

	Application::~Application()
	{
	}

	void Application::run()
	{
		while (_running)
		{
			float time = (float)glfwGetTime();
			Timestep timestep = time - _last_frame_time;
			_last_frame_time = time;


			for (Layer* layer : _layer_stack)
				layer->on_update(timestep);

			_imgui_layer->begin();
			for (Layer* layer : _layer_stack)
				layer->on_imgui_render();
			_imgui_layer->end();

			_window->on_update();
		}
	}

	void Application::on_event(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(on_window_close));

		for (auto it = _layer_stack.end(); it != _layer_stack.begin(); )
		{
			(*--it)->on_event(e);
			if (e._handled)
				break;
		}
	}

	void Application::push_layer(Layer* layer)
	{
		_layer_stack.push_layer(layer);
		layer->on_attach();
	}

	void Application::push_overlay(Layer* overlay)
	{
		_layer_stack.push_overlay(overlay);
		overlay->on_attach();
	}

	bool Application::on_window_close(WindowCloseEvent& e)
	{
		_running = false;
		return true;
	}
}