#pragma once

#include "Harmony.h"

namespace Harmony
{

	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void on_attach() override;
		virtual void on_detach() override;

		void on_update(Timestep ts) override;
		virtual void on_imgui_render() override;
		void on_event(Event& e) override;
	private:
		Harmony::OrthographicCameraController _camera_controller;

		Ref<VertexArray> _square_vertex_array;
		Ref<Shader> _flat_color_shader;
		Ref<Framebuffer> _framebuffer;

		Ref<Scene> _active_scene;
		entt::entity _square_entity;

		Ref<Texture2D> _checkboard_texture;

		bool _viewport_focused = false;
		bool _viewport_hovered = false;

		glm::vec2 _viewport_size = { 0.0f, 0.0f };

		glm::vec4 _square_color = { 0.2f, 0.3f, 0.8f, 1.0f };
	};

}