#include "Shader.h"

#include "Harmony/Core.h"
#include "Harmony/Log.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

#include <vector>

namespace Harmony
{

	Shader* Shader::create(const std::string& vertex_source, const std::string& fragment_source)
	{
		switch (Renderer::get_api())
		{
		case RendererAPI::API::None:    HM_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return new OpenGLShader(vertex_source, fragment_source);
		}

		HM_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}