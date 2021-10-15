#include "Scene.h"
#include "Component.h"

#include "Entity.h"

#include "Harmony/Renderer/Renderer2D.h"

#include <glm/glm.hpp>

namespace Harmony
{

	static void DoMath(const glm::mat4& transform)
	{

	}

	static void OnTransformConstruct(entt::registry& registry, entt::entity entity)
	{

	}

	Scene::Scene()
	{
#if ENTT_EXAMPLE_CODE
		entt::entity entity = _registry.create();
		_registry.emplace<TransformComponent>(entity, glm::mat4(1.0f));

		_registry.on_construct<TransformComponent>().connect<&OnTransformConstruct>();


		if (_registry.has<TransformComponent>(entity))
			TransformComponent& transform = _registry.get<TransformComponent>(entity);


		auto view = _registry.view<TransformComponent>();
		for (auto entity : view)
		{
			TransformComponent& transform = view.get<TransformComponent>(entity);
		}

		auto group = _registry.group<TransformComponent>(entt::get<MeshComponent>);
		for (auto entity : group)
		{
			auto& [transform, mesh] = group.get<TransformComponent, MeshComponent>(entity);
		}
#endif
	}

	Scene::~Scene()
	{
	}

	Entity Scene::create_entity(const std::string& name)
	{
		Entity entity = { _registry.create(), this };
		entity.add_component<TransformComponent>();
		auto& tag = entity.add_component<TagComponent>();
		tag.Tag = name.empty() ? "Entity" : name;
		return entity;
	}

	void Scene::on_update(Timestep ts)
	{
		// Render 2D
		Camera* main_camera = nullptr;
		glm::mat4* camera_transform = nullptr;

		{
			auto view = _registry.view<TransformComponent, CameraComponent>();
			for (auto entity : view)
			{
				auto [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);

				if (camera.primary)
				{
					main_camera = &camera.camera;
					camera_transform = &transform.Transform;
					break;
				}
			}
		}

		if (main_camera)
		{
			Renderer2D::begin_scene(main_camera->get_projection(), *camera_transform);

			auto group = _registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
			for (auto entity : group)
			{
				auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

				Renderer2D::draw_quad(transform, sprite.Color);
			}

			Renderer2D::end_scene();
		}

	}

	void Scene::on_viewport_resize(uint32_t width, uint32_t height)
	{
		_viewport_width = width;
		_viewport_height = height;

		// Resize our non-FixedAspectRatio cameras
		auto view = _registry.view<CameraComponent>();
		for (auto entity : view)
		{
			auto& camera_component = view.get<CameraComponent>(entity);
			if (!camera_component.FixedAspectRatio)
				camera_component.camera.set_viewport_size(width, height);
		}

	}

}