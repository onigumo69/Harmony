#include "Sandbox2D.h"

#include "Harmony/Debug/Instrumentor.h"

#include <imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), _camera_controller(1280.0f / 720.0f)
{
}

void Sandbox2D::on_attach()
{
	HM_PROFILE_FUNCTION();

	_check_board_texture = Harmony::Texture2D::create("assets/textures/Checkerboard.png");
}

void Sandbox2D::on_detach()
{
	HM_PROFILE_FUNCTION();
}

void Sandbox2D::on_update(Harmony::Timestep ts)
{
	// Update
	_camera_controller.on_update(ts);

	// Render
	Harmony::Renderer2D::reset_stats();
	{
		HM_PROFILE_SCOPE("Renderer Prep");
		Harmony::RenderCommand::set_clear_color({ 0.1f, 0.1f, 0.1f, 1 });
		Harmony::RenderCommand::clear();
	}

	{
		static float rotation = 0.0f;
		rotation += ts * 50.0f;

		HM_PROFILE_SCOPE("Renderer Draw");
		Harmony::Renderer2D::begin_scene(_camera_controller.get_camera());
		Harmony::Renderer2D::draw_rotated_quad({ 1.0f, 0.0f }, { 0.8f, 0.8f }, -45.0f, { 0.8f, 0.2f, 0.3f, 1.0f });
		Harmony::Renderer2D::draw_quad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Harmony::Renderer2D::draw_quad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		Harmony::Renderer2D::draw_quad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, _check_board_texture, 10.0f);
		Harmony::Renderer2D::draw_rotated_quad({ -2.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, rotation, _check_board_texture, 20.0f);
		Harmony::Renderer2D::end_scene();

		Harmony::Renderer2D::begin_scene(_camera_controller.get_camera());
		for (float y = -5.0f; y < 5.0f; y += 0.5f)
		{
			for (float x = -5.0f; x < 5.0f; x += 0.5f)
			{
				glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f };
				Harmony::Renderer2D::draw_quad({ x, y }, { 0.45f, 0.45f }, color);
			}
		}
		Harmony::Renderer2D::end_scene();
	}

}

void Sandbox2D::on_imgui_render()
{
	ImGui::Begin("Settings");

	auto stats = Harmony::Renderer2D::get_stats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.draw_calls);
	ImGui::Text("Quads: %d", stats.quad_count);
	ImGui::Text("Vertices: %d", stats.get_total_vertex_count());
	ImGui::Text("Indices: %d", stats.get_total_index_count());

	ImGui::ColorEdit4("Square Color", glm::value_ptr(_square_color));
	ImGui::End();
}

void Sandbox2D::on_event(Harmony::Event& e)
{
	_camera_controller.on_event(e);
}