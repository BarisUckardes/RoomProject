#include "LogicComponent.h"
#include <IterativeLogic/IterativeLogicFunction.h>
#include <Engine/World/World.h>
#include <Engine/World/Entity.h>

namespace Engine
{
	void LogicComponent::initialize()
	{
		get_owner_entity()->get_owner_world()->get_function<IterativeLogicFunction>()->register_component(this);
	}
	void LogicComponent::finalize()
	{
		get_owner_entity()->get_owner_world()->get_function<IterativeLogicFunction>()->remove_component(this);
	}
}