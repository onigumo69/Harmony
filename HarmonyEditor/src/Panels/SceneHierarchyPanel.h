#pragma once

#include "Harmony/Core/Core.h"
#include "Harmony/Core/Log.h"
#include "Harmony/Scene/Scene.h"
#include "Harmony/Scene/Entity.h"

namespace Harmony
{

	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene>& scene);

		void set_context(const Ref<Scene>& scene);

		void on_imgui_render();
	private:
		void draw_entity_node(Entity entity);
		void draw_components(Entity entity);
	private:
		Ref<Scene> m_Context;
		Entity m_SelectionContext;
	};

}