#pragma once

namespace Harmony
{

	class Timestep
	{
	public:
		Timestep(float time = 0.0f)
			: _time(time)
		{}

		operator float() const { return _time; }

		float get_seconds() const { return _time; }
		float get_milliseconds() const { return _time; }
		
	private:
		float _time;
	};

}