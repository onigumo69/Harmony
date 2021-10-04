#pragma once

#include "Harmony/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>

namespace Harmony
{

	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* window_handle);

		virtual void init() override;
		virtual void swap_buffers() override;
	private:
		GLFWwindow* _window_handle;
	};

}