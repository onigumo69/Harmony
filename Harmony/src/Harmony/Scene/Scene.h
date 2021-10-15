#pragma once

#include "Harmony/Core/Timestep.h"

#include <entt.hpp>

namespace Harmony
{

	class Scene
	{
	public:
		Scene();
		~Scene();

		entt::entity create_entity();

		entt::registry& reg() { return _registry; }

		void on_update(Timestep ts);

	private:
		entt::registry _registry;
	};

}