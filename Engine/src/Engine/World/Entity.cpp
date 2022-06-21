#include "Entity.h"
#include <Engine/World/World.h>

namespace Engine
{
	Entity::Entity(const String& name)
	{
		Name = name;
		OwnerWorld = nullptr;
	}
	Entity::~Entity()
	{

	}
	World* Entity::get_owner_world() const
	{
		return OwnerWorld;
	}
	void Entity::destroy_entity()
	{
		OwnerWorld->delete_entity(this);
	}
	void Entity::_set_owner_world(World* ownerWorld)
	{
		OwnerWorld = ownerWorld;
	}
	void Entity::_destroy()
	{
		for (unsigned int i = 0; i < Components.get_cursor(); i++)
		{
			Component* component = Components[i];

			component->finalize();

			delete component;
		}
	}
}