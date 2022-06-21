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
    bool Component::is_active() const
    {
        return Active;
    }
    void Component::set_active(const bool state)
    {
        Active = state;
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