#pragma once

#include "Core.h"
#include "Event/Event.h"
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
	private:
		std::unique_ptr<Window> _window;
		bool _running = true;
	};

	// to be defined in client side
	Application* create_application();
}