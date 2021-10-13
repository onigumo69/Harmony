#pragma once

#include "OrthographicCamera.h"
#include "Texture.h"

namespace Harmony
{

	class Renderer2D
	{
	public:
		static void init();
		static void shutdown();

		static void begin_scene(const OrthographicCamera& camera);
		static void end_scene();

		static void draw_quad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void draw_quad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		static void draw_quad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture);
		static void draw_quad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture);
	};

}