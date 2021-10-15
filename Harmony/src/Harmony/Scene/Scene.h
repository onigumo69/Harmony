#pragma once

#include "Harmony/Core/Timestep.h"

#include <entt.hpp>

namespace Harmony
{

	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();

		Entity create_entity(const std::string& name = std::string());

		void on_update(Timestep ts);

	private:
		entt::registry _registry;

		friend class Entity;
	};

}