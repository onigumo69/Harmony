#pragma once

#include "Harmony.h"

class Sandbox2D : public Harmony::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void on_attach() override;
	virtual void on_detach() override;

	void on_update(Harmony::Timestep ts) override;
	virtual void on_imgui_render() override;
	void on_event(Harmony::Event& e) override;
private:
	Harmony::OrthographicCameraController _camera_controller;

	Harmony::Ref<Harmony::VertexArray> _square_vertex_array;
	Harmony::Ref<Harmony::Shader> _flat_color_shader;
	Harmony::Ref<Harmony::Texture2D> _check_board_texture;

	glm::vec4 _square_color = { 0.2f, 0.3f, 0.8f, 1.0f };
};