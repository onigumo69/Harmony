#pragma once

#include "Camera.h"
#include "OrthographicCamera.h"
#include "Texture.h"

namespace Harmony
{

	class Renderer2D
	{
	public:
		static void init();
		static void shutdown();

		static void begin_scene(const Camera& camera, const glm::mat4& transform);
		static void begin_scene(const OrthographicCamera& camera);
		static void end_scene();
		static void flush();

		static void draw_quad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void draw_quad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		static void draw_quad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tiling_factor = 1.0f, const glm::vec4& tint_color = glm::vec4(1.0f));
		static void draw_quad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tiling_factor = 1.0f, const glm::vec4& tint_color = glm::vec4(1.0f));
		static void draw_quad(const glm::mat4& transform, const glm::vec4& color);
		static void draw_quad(const glm::mat4& transform, const Ref<Texture2D>& texture, float tiling_factor = 1.0f, const glm::vec4& tint_color = glm::vec4(1.0f));

		static void draw_rotated_quad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color);
		static void draw_rotated_quad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tiling_factor = 1.0f, const glm::vec4& tint_color = glm::vec4(1.0f));
		static void draw_rotated_quad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tiling_factor = 1.0f, const glm::vec4& tint_color = glm::vec4(1.0f));
		static void draw_rotated_quad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color);


		struct Statistics
		{
			uint32_t draw_calls = 0;
			uint32_t quad_count = 0;

			uint32_t get_total_vertex_count() { return quad_count * 4; }
			uint32_t get_total_index_count() { return quad_count * 6; }
		};
		static void reset_stats();
		static Statistics get_stats();
	private:
		static void flush_and_reset();
	};

}