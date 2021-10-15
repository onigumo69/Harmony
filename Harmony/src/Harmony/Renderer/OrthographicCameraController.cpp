#include "OrthographicCameraController.h"

#include "Harmony/Core/Input.h"
#include "Harmony/Core/KeyCode.h"
#include "Harmony/Debug/Instrumentor.h"

namespace Harmony
{

	OrthographicCameraController::OrthographicCameraController(float aspect_ratio, bool rotation)
		: _aspect_ratio(aspect_ratio), _camera(-_aspect_ratio * _zoom_level, _aspect_ratio* _zoom_level, -_zoom_level, _zoom_level), _rotation(rotation)
	{
	}

	void OrthographicCameraController::on_update(Timestep ts)
	{
		HM_PROFILE_FUNCTION();

		if (Input::is_key_pressed(Key::A))
		{
			_camera_position.x -= cos(glm::radians(_camera_rotation)) * _camera_translation_speed * ts;
			_camera_position.y -= sin(glm::radians(_camera_rotation)) * _camera_translation_speed * ts;
		}
		else if (Input::is_key_pressed(Key::D))
		{
			_camera_position.x += cos(glm::radians(_camera_rotation)) * _camera_translation_speed * ts;
			_camera_position.y += sin(glm::radians(_camera_rotation)) * _camera_translation_speed * ts;
		}

		if (Input::is_key_pressed(Key::W))
		{
			_camera_position.x += -sin(glm::radians(_camera_rotation)) * _camera_translation_speed * ts;
			_camera_position.y += cos(glm::radians(_camera_rotation)) * _camera_translation_speed * ts;
		}
		else if (Input::is_key_pressed(Key::S))
		{
			_camera_position.x -= -sin(glm::radians(_camera_rotation)) * _camera_translation_speed * ts;
			_camera_position.y -= cos(glm::radians(_camera_rotation)) * _camera_translation_speed * ts;
		}

		if (_rotation)
		{
			if (Input::is_key_pressed(Key::Q))
				_camera_rotation += _camera_rotation_speed * ts;
			if (Input::is_key_pressed(Key::E))
				_camera_rotation -= _camera_rotation_speed * ts;

			if (_camera_rotation > 180.0f)
				_camera_rotation -= 360.0f;
			else if (_camera_rotation <= -180.0f)
				_camera_rotation += 360.0f;

			_camera.set_rotation(_camera_rotation);
		}

		_camera.set_position(_camera_position);

		_camera_translation_speed = _zoom_level;
	}

	void OrthographicCameraController::on_event(Event& e)
	{
		HM_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.dispatch<MouseScrolledEvent>(HM_BIND_EVENT_FN(OrthographicCameraController::on_mouse_scrolled));
		dispatcher.dispatch<WindowResizeEvent>(HM_BIND_EVENT_FN(OrthographicCameraController::on_window_resized));
	}

	void OrthographicCameraController::on_resize(float width, float height)
	{
		_aspect_ratio = width / height;
		_camera.set_projection(-_aspect_ratio * _zoom_level, _aspect_ratio * _zoom_level, -_zoom_level, _zoom_level);
	}

	bool OrthographicCameraController::on_mouse_scrolled(MouseScrolledEvent& e)
	{
		HM_PROFILE_FUNCTION();

		_zoom_level -= e.get_y_offset() * 0.25f;
		_zoom_level = std::max(_zoom_level, 0.25f);
		_camera.set_projection(-_aspect_ratio * _zoom_level, _aspect_ratio * _zoom_level, -_zoom_level, _zoom_level);
		return false;
	}

	bool OrthographicCameraController::on_window_resized(WindowResizeEvent& e)
	{
		HM_PROFILE_FUNCTION();

		on_resize((float)e.get_width(), (float)e.get_height());

		return false;
	}

}