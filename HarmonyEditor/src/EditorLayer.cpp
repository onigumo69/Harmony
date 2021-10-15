#include "EditorLayer.h"
#include <imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Harmony
{

	EditorLayer::EditorLayer()
		: Layer("EditorLayer"), _camera_controller(1280.0f / 720.0f), _square_color({ 0.2f, 0.3f, 0.8f, 1.0f })
	{
	}

	void EditorLayer::on_attach()
	{
		HM_PROFILE_FUNCTION();

		_checkboard_texture = Texture2D::create("assets/textures/Checkerboard.png");

		FramebufferSpecification fb_spec;
		fb_spec.width = 1280;
		fb_spec.height = 720;
		_framebuffer = Framebuffer::create(fb_spec);

		_active_scene = create_ref<Scene>();

		// Entity
		auto square = _active_scene->create_entity("Green Square");
		square.add_component<SpriteRendererComponent>(glm::vec4{ 0.0f, 1.0f, 0.0f, 1.0f });

		_square_entity = square;

		_camera_entity = _active_scene->create_entity("Camera Entity");
		_camera_entity.add_component<CameraComponent>();

		_second_camera_entity = _active_scene->create_entity("Clip Space Entity");
		auto& cc = _second_camera_entity.add_component<CameraComponent>();
		cc.primary = false;

		class CameraController : public ScriptableEntity
		{
		public:
			void OnCreate()
			{
				auto& transform = get_component<TransformComponent>().Transform;
				transform[3][0] = rand() % 10 - 5.0f;
			}

			void OnDestroy()
			{
			}

			void OnUpdate(Timestep ts)
			{
				auto& transform = get_component<TransformComponent>().Transform;

				float speed = 5.0f;

				if (Input::is_key_pressed(Key::A))
					transform[3][0] -= speed * ts;
				if (Input::is_key_pressed(Key::D))
					transform[3][0] += speed * ts;
				if (Input::is_key_pressed(Key::W))
					transform[3][1] += speed * ts;
				if (Input::is_key_pressed(Key::S))
					transform[3][1] -= speed * ts;
			}
		};

		_camera_entity.add_component<NativeScriptComponent>().Bind<CameraController>();
		_second_camera_entity.add_component<NativeScriptComponent>().Bind<CameraController>();

		_scene_hierarchy_panel.set_context(_active_scene);
	}

	void EditorLayer::on_detach()
	{
		HM_PROFILE_FUNCTION();
	}

	void EditorLayer::on_update(Timestep ts)
	{
		HM_PROFILE_FUNCTION();

		// Resize
		if (Harmony::FramebufferSpecification spec = _framebuffer->get_specification();
			_viewport_size.x > 0.0f && _viewport_size.y > 0.0f && // zero sized framebuffer is invalid
			(spec.width != _viewport_size.x || spec.height != _viewport_size.y))
		{
			_framebuffer->resize((uint32_t)_viewport_size.x, (uint32_t)_viewport_size.y);
			_camera_controller.on_resize(_viewport_size.x, _viewport_size.y);

			_active_scene->on_viewport_resize((uint32_t)_viewport_size.x, (uint32_t)_viewport_size.y);
		}

		// Update
		if (_viewport_focused)
			_camera_controller.on_update(ts);

		// Render
		Renderer2D::reset_stats();
		_framebuffer->bind();
		RenderCommand::set_clear_color({ 0.1f, 0.1f, 0.1f, 1 });
		RenderCommand::clear();

		// Update scene
		_active_scene->on_update(ts);

		_framebuffer->unbind();
	}

	void EditorLayer::on_imgui_render()
	{
		HM_PROFILE_FUNCTION();

		// Note: Switch this to true to enable dockspace
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

				if (ImGui::MenuItem("Exit")) Application::get().close();
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		_scene_hierarchy_panel.on_imgui_render();

		ImGui::Begin("Settings");

		auto stats = Renderer2D::get_stats();
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Draw Calls: %d", stats.draw_calls);
		ImGui::Text("Quads: %d", stats.quad_count);
		ImGui::Text("Vertices: %d", stats.get_total_vertex_count());
		ImGui::Text("Indices: %d", stats.get_total_index_count());

		if (_square_entity)
		{
			ImGui::Separator();
			auto& tag = _square_entity.get_component<TagComponent>().Tag;
			ImGui::Text("%s", tag.c_str());

			auto& squareColor = _square_entity.get_component<SpriteRendererComponent>().Color;
			ImGui::ColorEdit4("Square Color", glm::value_ptr(squareColor));
			ImGui::Separator();
		}

		ImGui::DragFloat3("Camera Transform",
			glm::value_ptr(_camera_entity.get_component<TransformComponent>().Transform[3]));

		if (ImGui::Checkbox("Camera A", &_primary_camera))
		{
			_camera_entity.get_component<CameraComponent>().primary = _primary_camera;
			_second_camera_entity.get_component<CameraComponent>().primary = !_primary_camera;
		}

		{
			auto& camera = _second_camera_entity.get_component<CameraComponent>().camera;
			float ortho_size = camera.get_orthographic_size();
			if (ImGui::DragFloat("Second Camera Ortho Size", &ortho_size))
				camera.set_orthographic_size(ortho_size);
		}

		ImGui::End();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
		ImGui::Begin("Viewport");

		_viewport_focused = ImGui::IsWindowFocused();
		_viewport_hovered = ImGui::IsWindowHovered();
		Application::get().get_imgui_layer()->block_events(!_viewport_focused || !_viewport_hovered);

		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();

		_viewport_size = { viewportPanelSize.x, viewportPanelSize.y };

		uint64_t textureID = _framebuffer->get_color_attachment_renderer_id();
		ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{ _viewport_size.x, _viewport_size.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
		ImGui::End();
		ImGui::PopStyleVar();

		ImGui::End();
	}

	void EditorLayer::on_event(Event& e)
	{
		_camera_controller.on_event(e);
	}

}