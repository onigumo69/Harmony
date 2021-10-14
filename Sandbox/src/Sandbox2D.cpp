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
	{
		HM_PROFILE_SCOPE("Renderer Prep");
		Harmony::RenderCommand::set_clear_color({ 0.1f, 0.1f, 0.1f, 1 });
		Harmony::RenderCommand::clear();
	}

	{
		HM_PROFILE_SCOPE("Renderer Draw");
		Harmony::Renderer2D::begin_scene(_camera_controller.get_camera());
		Harmony::Renderer2D::draw_rotated_quad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, glm::radians(-45.0f), { 0.8f, 0.2f, 0.3f, 1.0f });
		Harmony::Renderer2D::draw_quad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		Harmony::Renderer2D::draw_quad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, _check_board_texture, 10.0f);
		Harmony::Renderer2D::end_scene();
	}

}

void Sandbox2D::on_imgui_render()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(_square_color));
	ImGui::End();
}

void Sandbox2D::on_event(Harmony::Event& e)
{
	_camera_controller.on_event(e);
}