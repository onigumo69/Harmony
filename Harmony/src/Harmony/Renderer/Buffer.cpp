#include "Harmony/Core/Core.h"
#include "Harmony/Core/Log.h"

#include "Buffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Harmony
{

	Ref<VertexBuffer> VertexBuffer::create(uint32_t size)
	{
		switch (Renderer::get_api())
		{
		case RendererAPI::API::None:    HM_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return create_ref<OpenGLVertexBuffer>(size);
		}

		HM_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<VertexBuffer> VertexBuffer::create(float* vertices, uint32_t size)
	{
		switch (Renderer::get_api())
		{
		case RendererAPI::API::None:    HM_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return create_ref<OpenGLVertexBuffer>(vertices, size);
		}

		HM_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::get_api())
		{
		case RendererAPI::API::None:    HM_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return create_ref<OpenGLIndexBuffer>(indices, size);
		}

		HM_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}