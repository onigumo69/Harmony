#include "Harmony/Core.h"
#include "Harmony/Log.h"

#include <glad/glad.h>
#include <gl/GL.h>

#include "OpenGLContext.h"

namespace Harmony
{

	OpenGLContext::OpenGLContext(GLFWwindow* window_handle)
		: _window_handle(window_handle)
	{
		HM_CORE_ASSERT(window_handle, "Window handle is null!")
	}

	void OpenGLContext::init()
	{
		glfwMakeContextCurrent(_window_handle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HM_CORE_ASSERT(status, "Failed to initialize Glad!");
	}


	void OpenGLContext::swap_buffers()
	{
		glfwSwapBuffers(_window_handle);
	}

}