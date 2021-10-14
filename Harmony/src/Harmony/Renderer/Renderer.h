#pragma once

#include "RenderCommand.h"

#include "OrthographicCamera.h"
#include "Shader.h"

namespace Harmony
{

	class Renderer
	{
	public:
		static void init();
		static void shutdown();
		static void on_window_resize(uint32_t width, uint32_t height);

		static void begin_scene(OrthographicCamera& camera);
		static void end_scene();

		static void submit(const Ref<Shader>& shader,
			const Ref<VertexArray>& vertex_array,
			const glm::mat4& transform = glm::mat4(1.0f));

		inline static RendererAPI::API get_api() { return RendererAPI::get_api(); }
	private:
		struct SceneData
		{
			glm::mat4 _view_projection_matrix;
		};

		static Scope<SceneData> _scene_data;
	};

}