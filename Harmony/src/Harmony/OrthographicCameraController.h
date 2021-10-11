#pragma once

#include "Renderer/OrthographicCamera.h"
#include "Core/Timestep.h"

#include "Event/ApplicationEvent.h"
#include "Event/MouseEvent.h"

namespace Harmony
{

	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspect_ratio, bool rotation = false);

		void on_update(Timestep ts);
		void on_event(Event& e);

		OrthographicCamera& get_camera() { return _camera; }
		const OrthographicCamera& get_camera() const { return _camera; }

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