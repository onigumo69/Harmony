#include "Window.h"
#include "Platform/Windows/WindowsWindow.h"

namespace Harmony
{

	Scope<Window> Window::create(const WindowProps& props)
	{
		return create_scope<WindowsWindow>(props);
	}

}