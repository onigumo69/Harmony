#pragma once

#include "RenderCommand.h"

namespace Harmony
{

	class Renderer
	{
	public:
		static void begin_scene();
		static void end_scene();

		static void submit(const std::shared_ptr<VertexArray>& vertexArray);

		inline static RendererAPI::API get_api() { return RendererAPI::get_api(); }
	};

}