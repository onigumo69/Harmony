#include "Application.h"

#include "Log.h"
#include "Input.h"

#include "Harmony/Debug/Instrumentor.h"
#include "Harmony/Renderer/Renderer.h"

#include <GLFW/glfw3.h>

namespace Harmony
{
	Application* Application::Instance = nullptr;

	Application::Application()
	{
		HM_PROFILE_FUNCTION();

		HM_CORE_ASSERT(!Instance, "Application already exists!");
		Instance = this;

		_window = Window::create();
		_window->set_event_callback(HM_BIND_EVENT_FN(Application::on_event));

		Renderer::init();

		_imgui_layer = new ImGuiLayer();
		push_overlay(_imgui_layer);
	}

	Application::~Application()
	{
		HM_PROFILE_FUNCTION();

		Renderer::shutdown();
	}

	void Application::run()
	{
		HM_PROFILE_FUNCTION();

		while (_running)
		{
			HM_PROFILE_SCOPE("RunLoop");

			float time = (float)glfwGetTime();
			Timestep timestep = time - _last_frame_time;
			_last_frame_time = time;


			if (!_minimized)
			{
				{
					HM_PROFILE_SCOPE("LayerStack on_update");

					for (Layer* layer : _layer_stack)
						layer->on_update(timestep);
				}

				_imgui_layer->begin();
				{
					HM_PROFILE_SCOPE("LayerStack on_imgui_render");

					for (Layer* layer : _layer_stack)
						layer->on_imgui_render();
				}
				_imgui_layer->end();
			}

			_window->on_update();
		}
	}

	void Application::on_event(Event& e)
	{
		HM_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowCloseEvent>(HM_BIND_EVENT_FN(Application::on_window_close));
		dispatcher.dispatch<WindowResizeEvent>(HM_BIND_EVENT_FN(Application::on_window_resize));

		for (auto it = _layer_stack.rbegin(); it != _layer_stack.rend(); ++it)
		{
			(*it)->on_event(e);
			if (e._handled)
				break;
		}
	}

	void Application::push_layer(Layer* layer)
	{
		HM_PROFILE_FUNCTION();

		_layer_stack.push_layer(layer);
		layer->on_attach();
	}

	void Application::push_overlay(Layer* overlay)
	{
		HM_PROFILE_FUNCTION();

		_layer_stack.push_overlay(overlay);
		overlay->on_attach();
	}

	bool Application::on_window_close(WindowCloseEvent& e)
	{
		_running = false;
		return true;
	}

	bool Application::on_window_resize(WindowResizeEvent& e)
	{
		HM_PROFILE_FUNCTION();

		if (e.get_width() == 0 || e.get_height() == 0)
		{
			_minimized = true;
			return false;
		}

		_minimized = false;
		Renderer::on_window_resize(e.get_width(), e.get_height());

		return false;
	}

}