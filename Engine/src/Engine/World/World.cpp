#include "World.h"
#include <Engine/World/Entity.h>

namespace Engine
{
    Entity* World::create_entity(const String& name)
    {
        Entity* entity = new Entity(name);

        entity->_set_owner_world(this);

        Entities.add(entity);

        return entity;
    }
    void World::delete_entity(Entity* entity)
    {
        Entities.remove(entity);

        entity->_destroy();

        delete entity;
    }
    World::World(ApplicationSession* ownerSession, const String& name)
    {
        OwnerSession = ownerSession;
        Name = name;
    }
    World::~World()
    {

    }
    const Array<Entity*>& World::get_entities() const
    {
        return Entities;
    }
    const Array<WorldFunction*> World::get_functions() const
    {
        return Functions;
    }
    ApplicationSession* World::get_owner_session() const
    {
        return OwnerSession;
    }
    String World::get_name() const
    {
        return Name;
    }
}