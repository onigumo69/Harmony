#pragma once

#include <glm/glm.hpp>

#include "VertexArray.h"

namespace Harmony
{

	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0, OpenGL = 1
		};
	public:
		virtual void init() = 0;
		virtual void set_viewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;

		virtual void set_clear_color(const glm::vec4& color) = 0;
		virtual void clear() = 0;

		virtual void draw_indexed(const Ref<VertexArray>& vertex_array, uint32_t index_count = 0) = 0;

		inline static API get_api() { return _api; }
		
		static Scope<RendererAPI> create();
	private:
		static API _api;
	};

}