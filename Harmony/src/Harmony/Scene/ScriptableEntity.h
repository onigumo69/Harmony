#pragma once

#include "Entity.h"

namespace Harmony
{

	class ScriptableEntity
	{
	public:
		virtual ~ScriptableEntity()
		{}

		template<typename T>
		T& get_component()
		{
			return m_Entity.get_component<T>();
		}
	protected:
		virtual void OnCreate() {}
		virtual void OnDestroy() {}
		virtual void OnUpdate(Timestep ts) {}
	private:
		Entity m_Entity;
		friend class Scene;
	};

}