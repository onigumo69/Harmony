#include "SceneHierarchyPanel.h"

#include "Harmony/Scene/Component.h"

#include <imgui.h>

namespace Harmony
{

	SceneHierarchyPanel::SceneHierarchyPanel(const Ref<Scene>& context)
	{
		set_context(context);
	}

	void SceneHierarchyPanel::set_context(const Ref<Scene>& context)
	{
		m_Context = context;
	}

	void SceneHierarchyPanel::on_imgui_render()
	{
		ImGui::Begin("Scene Hierarchy");

		m_Context->_registry.each([&](auto entityID)
			{
				Entity entity{ entityID , m_Context.get() };
				draw_entity_node(entity);
			});

		ImGui::End();
	}

	void SceneHierarchyPanel::draw_entity_node(Entity entity)
	{
		auto& tag = entity.get_component<TagComponent>().Tag;

		ImGuiTreeNodeFlags flags = ((m_SelectionContext == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
		bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tag.c_str());
		if (ImGui::IsItemClicked())
		{
			m_SelectionContext = entity;
		}

		if (opened)
		{
			ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;
			bool opened = ImGui::TreeNodeEx((void*)9817239, flags, tag.c_str());
			if (opened)
				ImGui::TreePop();
			ImGui::TreePop();
		}

	}

}