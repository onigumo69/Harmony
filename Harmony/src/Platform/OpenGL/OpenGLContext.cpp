#include "Harmony/Core/Core.h"
#include "Harmony/Core/Log.h"

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

		HM_CORE_INFO("OpenGL Info:");
		HM_CORE_INFO("Vendor: {0}", glGetString(GL_VENDOR));
		HM_CORE_INFO("Renderer: {0}", glGetString(GL_RENDERER));
		HM_CORE_INFO("Version: {0}", glGetString(GL_VERSION));
	}


	void OpenGLContext::swap_buffers()
	{
		glfwSwapBuffers(_window_handle);
	}

}