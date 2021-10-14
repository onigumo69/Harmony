#include "Framebuffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace Harmony
{

	Ref<Framebuffer> Framebuffer::create(const FramebufferSpecification& spec)
	{
		switch (Renderer::get_api())
		{
		case RendererAPI::API::None:    HM_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return create_ref<OpenGLFramebuffer>(spec);
		}

		HM_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}