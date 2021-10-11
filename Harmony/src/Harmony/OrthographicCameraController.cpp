#include "OrthographicCameraController.h"

#include "Input.h"
#include "KeyCode.h"

namespace Harmony
{

	OrthographicCameraController::OrthographicCameraController(float aspect_ratio, bool rotation)
		: _aspect_ratio(aspect_ratio), _camera(-_aspect_ratio * _zoom_level, _aspect_ratio* _zoom_level, -_zoom_level, _zoom_level), _rotation(rotation)
	{
	}

	void OrthographicCameraController::on_update(Timestep ts)
	{
		if (Input::is_key_pressed(HM_KEY_A))
			_camera_position.x -= _camera_translation_speed * ts;
		else if (Input::is_key_pressed(HM_KEY_D))
			_camera_position.x += _camera_translation_speed * ts;

		if (Input::is_key_pressed(HM_KEY_W))
			_camera_position.y += _camera_translation_speed * ts;
		else if (Input::is_key_pressed(HM_KEY_S))
			_camera_position.y -= _camera_translation_speed * ts;

		if (_rotation)
		{
			if (Input::is_key_pressed(HM_KEY_Q))
				_camera_rotation += _camera_rotation_speed * ts;
			if (Input::is_key_pressed(HM_KEY_E))
				_camera_rotation -= _camera_rotation_speed * ts;

			_camera.set_rotation(_camera_rotation);
		}

		_camera.set_position(_camera_position);

		_camera_translation_speed = _zoom_level;
	}

	void OrthographicCameraController::on_event(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<MouseScrolledEvent>(HM_BIND_EVENT_FN(OrthographicCameraController::on_mouse_scrolled));
		dispatcher.dispatch<WindowResizeEvent>(HM_BIND_EVENT_FN(OrthographicCameraController::on_window_resized));
	}

	bool OrthographicCameraController::on_mouse_scrolled(MouseScrolledEvent& e)
	{
		_zoom_level -= e.get_y_offset() * 0.25f;
		_zoom_level = std::max(_zoom_level, 0.25f);
		_camera.set_projection(-_aspect_ratio * _zoom_level, _aspect_ratio * _zoom_level, -_zoom_level, _zoom_level);
		return false;
	}

	bool OrthographicCameraController::on_window_resized(WindowResizeEvent& e)
	{
		_aspect_ratio = (float)e.get_width() / (float)e.get_height();
		_camera.set_projection(-_aspect_ratio * _zoom_level, _aspect_ratio * _zoom_level, -_zoom_level, _zoom_level);
		return false;
	}

}