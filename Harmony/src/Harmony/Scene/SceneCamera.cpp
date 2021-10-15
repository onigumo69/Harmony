#include "SceneCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Harmony
{

	SceneCamera::SceneCamera()
	{
		recalculate_projection();
	}

	void SceneCamera::set_orthographic_size(float size, float near, float far)
	{
		_orthographic_size = size;
		_orthographic_near = near;
		_orthographic_far = far;
		recalculate_projection();
	}

	void SceneCamera::set_viewport_size(uint32_t width, uint32_t height)
	{
		_aspect_ratio = (float)width / (float)height;
		recalculate_projection();
	}

	void SceneCamera::recalculate_projection()
	{
		float ortho_left = -_orthographic_size * _aspect_ratio * 0.5f;
		float ortho_right = _orthographic_size * _aspect_ratio * 0.5f;
		float ortho_bottom = -_orthographic_size * 0.5f;
		float ortho_top = _orthographic_size * 0.5f;

		_projection = glm::ortho(ortho_left, ortho_right,
			ortho_bottom, ortho_top, _orthographic_near, _orthographic_far);
	}

}