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
	HM_PROFILE_FUNCTION();

	// Note: Switch this to true to enable dockspace
	static bool dockingEnabled = false;
	if (dockingEnabled)
	{
		static bool dockspaceOpen = true;
		static bool opt_fullscreen_persistant = true;
		bool opt_fullscreen = opt_fullscreen_persistant;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive, 
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise 
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				// Disabling fullscreen would allow the window to be moved to the front of other windows, 
				// which we can't undo at the moment without finer window depth/z control.
				//ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);

				if (ImGui::MenuItem("Exit")) Harmony::Application::get().close();
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		ImGui::Begin("Settings");

		auto stats = Harmony::Renderer2D::get_stats();
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Draw Calls: %d", stats.draw_calls);
		ImGui::Text("Quads: %d", stats.quad_count);
		ImGui::Text("Vertices: %d", stats.get_total_vertex_count());
		ImGui::Text("Indices: %d", stats.get_total_index_count());

		ImGui::ColorEdit4("Square Color", glm::value_ptr(_square_color));

		uint32_t texture_id = _check_board_texture->get_renderer_id();
		ImGui::Image((void*)texture_id, ImVec2{ 256.0f, 256.0f });
		ImGui::End();

		ImGui::End();
	}
	else
	{
		ImGui::Begin("Settings");

		auto stats = Harmony::Renderer2D::get_stats();
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Draw Calls: %d", stats.draw_calls);
		ImGui::Text("Quads: %d", stats.quad_count);
		ImGui::Text("Vertices: %d", stats.get_total_vertex_count());
		ImGui::Text("Indices: %d", stats.get_total_index_count());

		ImGui::ColorEdit4("Square Color", glm::value_ptr(_square_color));

		uint32_t texture_id = _check_board_texture->get_renderer_id();
		ImGui::Image((void*)texture_id, ImVec2{ 256.0f, 256.0f });
		ImGui::End();
	}
}

void Sandbox2D::on_event(Harmony::Event& e)
{
	_camera_controller.on_event(e);
}