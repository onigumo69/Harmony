#pragma once

#include "Harmony.h"

class ExampleLayer : public Harmony::Layer
{
public:
	ExampleLayer();
	virtual ~ExampleLayer() = default;

	virtual void on_attach() override;
	virtual void on_detach() override;

	void on_update(Harmony::Timestep ts) override;
	virtual void on_imgui_render() override;
	void on_event(Harmony::Event& e) override;
private:
	Harmony::ShaderLibrary _shader_library;;
	Harmony::Ref<Harmony::Shader> _shader;
	Harmony::Ref<Harmony::VertexArray> _vertex_array;

	Harmony::Ref<Harmony::Shader> _flat_color_shader;
	Harmony::Ref<Harmony::VertexArray> _square_vertex_array;

	Harmony::Ref<Harmony::Texture2D> _texture, _grass_texture;

	Harmony::OrthographicCameraController _camera_controller;
	glm::vec3 _square_color = { 0.2f, 0.3f, 0.8f };
};