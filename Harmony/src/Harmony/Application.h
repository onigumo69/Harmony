#pragma once

#include "Core.h"
#include "Event/Event.h"

namespace Harmony
{
	class HARMONY_API Application
	{
	public:
		Application();
		virtual ~Application();

		void run();
	};

	// to be defined in client side
	Application* create_application();
}