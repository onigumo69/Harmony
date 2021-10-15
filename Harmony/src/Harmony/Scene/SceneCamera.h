#pragma once

#include "Harmony/Renderer/Camera.h"

namespace Harmony
{

	class SceneCamera : public Camera
	{
	public:
		SceneCamera();
		virtual ~SceneCamera() = default;

		void set_orthographic_size(float size, float near, float far);

		void set_viewport_size(uint32_t width, uint32_t height);

		float get_orthographic_size() const { return _orthographic_size; }
		void set_orthographic_size(float size)
		{
			_orthographic_size = size;
			recalculate_projection();
		}
	private:
		void recalculate_projection();
	private:
		float _orthographic_size = 10.0f;
		float _orthographic_near = -1.0f;
		float _orthographic_far = 1.0f;

		float _aspect_ratio = 0.0f;
	};

}