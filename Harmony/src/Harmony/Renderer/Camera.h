#pragma once

#include <glm/glm.hpp>

namespace Harmony
{

	class Camera
	{
	public:
		Camera(const glm::mat4& projection)
			: _projection(projection)
		{}

		const glm::mat4& get_projection() const { return _projection; }
	private:
		glm::mat4 _projection;
	};

}