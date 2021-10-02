#include "Application.h"

#include "Harmony/Log.h"
#include "Harmony/Event/ApplicationEvent.h"

namespace Harmony
{

	Application::Application()
	{
	}


	Application::~Application()
	{
	}

	void Application::run()
	{
		WindowResizeEvent e(1280, 720);
		if (e.is_in_category(EventCategoryApplication))
		{
			HM_TRACE(e);
		}
		if (e.is_in_category(EventCategoryInput))
		{
			HM_TRACE(e);
		}
	}

}