#include "Component.h"

namespace Engine
{
    Entity* Component::get_owner_entity() const
    {
        return OwnerEntity;
    }
    String Component::get_name() const
    {
        return Name;
    }
    void Component::set_name(const String& name)
    {
        Name = name;
    }
    void Component::_set_owner_entity(Entity* ownerEntity)
    {
        OwnerEntity = ownerEntity;
    }
}