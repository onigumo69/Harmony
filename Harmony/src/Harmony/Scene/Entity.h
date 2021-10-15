#pragma once

#include "Scene.h"

#include "Harmony/Core/Core.h"
#include "Harmony/Core/Log.h"

#include <entt.hpp>

namespace Harmony
{

	class Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene);
		Entity(const Entity& other) = default;

		template<typename T, typename... Args>
		T& add_component(Args&&... args)
		{
			HM_CORE_ASSERT(!has_component<T>(), "Entity already has component!");
			return _scene->_registry.emplace<T>(_entity_handle, std::forward<Args>(args)...);
		}

		template<typename T>
		T& get_component()
		{
			HM_CORE_ASSERT(has_component<T>(), "Entity does not have component!");
			return _scene->_registry.get<T>(_entity_handle);
		}

		template<typename T>
		bool has_component()
		{
			return _scene->_registry.has<T>(_entity_handle);
		}

		template<typename T>
		void remove_component()
		{
			HM_CORE_ASSERT(has_component<T>(), "Entity does not have component!");
			_scene->_registry.remove<T>(_entity_handle);
		}

		operator bool() const { return _entity_handle != entt::null; }

	private:
		entt::entity _entity_handle{ entt::null };
		Scene* _scene = nullptr;
	};

}