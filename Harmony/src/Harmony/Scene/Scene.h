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
		void on_viewport_resize(uint32_t width, uint32_t height);

	private:
		entt::registry _registry;
		uint32_t _viewport_width{};
		uint32_t _viewport_height{};

		friend class Entity;
		friend class SceneHierarchyPanel;
	};

}