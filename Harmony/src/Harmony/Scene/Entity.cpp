#include "Entity.h"

namespace Harmony
{

	Entity::Entity(entt::entity handle, Scene* scene)
		: _entity_handle(handle), _scene(scene)
	{
	}

}