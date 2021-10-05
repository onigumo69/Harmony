#pragma once

namespace Harmony
{

	enum class RendererAPI
	{
		None = 0,
		OpenGL = 1
	};

	class Renderer
	{
	public:
		inline static RendererAPI get_api() { return API; };
	private:
		static RendererAPI API;
	};

}