#include "OrthographicCamera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Harmony
{

	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		: _projection_matrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), _view_matrix(1.0f)
	{
		_view_projection_matrix = _projection_matrix * _view_matrix;
	}

	void OrthographicCamera::set_projection(float left, float right, float bottom, float top)
	{
		_projection_matrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		_view_projection_matrix = _projection_matrix * _view_matrix;
	}

	void OrthographicCamera::recalculate_view_matrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), _position) *
			glm::rotate(glm::mat4(1.0f), glm::radians(_rotation), glm::vec3(0, 0, 1));

		_view_matrix = glm::inverse(transform);
		_view_projection_matrix = _projection_matrix * _view_matrix;
	}
}