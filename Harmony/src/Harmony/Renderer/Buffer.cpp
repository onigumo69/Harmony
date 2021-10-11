#include "Harmony/Core/Core.h"
#include "Harmony/Core/Log.h"

#include "Buffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Harmony
{

	VertexBuffer* VertexBuffer::create(float* vertices, uint32_t size)
	{
		switch (Renderer::get_api())
		{
		case RendererAPI::API::None:    HM_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return new OpenGLVertexBuffer(vertices, size);
		}

		HM_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::get_api())
		{
		case RendererAPI::API::None:    HM_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return new OpenGLIndexBuffer(indices, size);
		}

		HM_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}