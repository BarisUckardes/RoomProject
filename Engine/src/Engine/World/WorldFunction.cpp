#include "WorldFunction.h"

namespace Engine
{
	World* WorldFunction::get_owner_world() const
	{
		return OwnerWorld;
	}
	void WorldFunction::_set_owner_world(World* world)
	{
		OwnerWorld = world;
	}
}