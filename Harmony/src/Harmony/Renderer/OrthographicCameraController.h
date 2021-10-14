#pragma once

#include "Harmony/Renderer/OrthographicCamera.h"
#include "Harmony/Core/Timestep.h"

#include "Harmony/Event/ApplicationEvent.h"
#include "Harmony/Event/MouseEvent.h"

namespace Harmony
{

	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspect_ratio, bool rotation = false);

		void on_update(Timestep ts);
		void on_event(Event& e);

		void on_resize(float width, float height);

		OrthographicCamera& get_camera() { return _camera; }
		const OrthographicCamera& get_camera() const { return _camera; }

		float get_zoom_level() const { return _zoom_level; }
		void set_zoom_level(float level) { _zoom_level = level; }
	private:
		bool on_mouse_scrolled(MouseScrolledEvent& e);
		bool on_window_resized(WindowResizeEvent& e);
	private:
		float _aspect_ratio;
		float _zoom_level = 1.0f;
		OrthographicCamera _camera;

		bool _rotation;

		glm::vec3 _camera_position = { 0.0f, 0.0f, 0.0f };
		float _camera_rotation = 0.0f;
		float _camera_translation_speed = 5.0f;
		float _camera_rotation_speed = 180.0f;
	};

}