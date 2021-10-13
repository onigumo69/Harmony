#pragma once

#include "Harmony/Core/Core.h"

namespace Harmony
{

	class GraphicsContext
	{
	public:
		virtual void init() = 0;
		virtual void swap_buffers() = 0;

		static Scope<GraphicsContext> create(void* window);
	};

}