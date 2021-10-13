#include "RendererAPI.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Harmony
{

	RendererAPI::API RendererAPI::_api = RendererAPI::API::OpenGL;

	Scope<RendererAPI> RendererAPI::create()
	{
		switch (_api)
		{
		case RendererAPI::API::None:    HM_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return create_scope<OpenGLRendererAPI>();
		}

		HM_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}