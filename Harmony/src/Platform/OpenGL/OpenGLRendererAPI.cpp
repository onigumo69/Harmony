#include "OpenGLRendererAPI.h"
#include "Harmony/Debug/Instrumentor.h"
#include "Harmony/Renderer/VertexArray.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <memory>

namespace Harmony
{

	void opengl_message_callback(
		unsigned source,
		unsigned type,
		unsigned id,
		unsigned severity,
		int length,
		const char* message,
		const void* userParam)
	{
		switch (severity)
		{
		case GL_DEBUG_SEVERITY_HIGH:         HM_CORE_FATAL(message); return;
		case GL_DEBUG_SEVERITY_MEDIUM:       HM_CORE_ERROR(message); return;
		case GL_DEBUG_SEVERITY_LOW:          HM_CORE_WARN(message); return;
		case GL_DEBUG_SEVERITY_NOTIFICATION: HM_CORE_TRACE(message); return;
		}

		HM_CORE_ASSERT(false, "Unknown severity level!");
	}

	void OpenGLRendererAPI::init()
	{
		HM_PROFILE_FUNCTION();

#ifdef HM_DEBUG
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(opengl_message_callback, nullptr);

		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
#endif

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
	}

	void OpenGLRendererAPI::set_viewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}

	void OpenGLRendererAPI::set_clear_color(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::draw_indexed(const Ref<VertexArray>& vertex_array, uint32_t index_count)
	{
		uint32_t count = index_count ? index_count : vertex_array->get_index_buffer()->get_count();
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
		
		glBindTexture(GL_TEXTURE_2D, 0);
	}

}