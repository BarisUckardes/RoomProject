#include "IterativeLogicFunction.h"
#include <IterativeLogic/LogicComponent.h>
namespace Engine
{
	void IterativeLogicFunction::register_component(LogicComponent* component)
	{
		Components.add(component);
	}
	void IterativeLogicFunction::remove_component(LogicComponent* component)
	{
		Components.remove(component);
	}
	void IterativeLogicFunction::initialize()
	{

	}
	void IterativeLogicFunction::execute()
	{
		for (unsigned int i = 0; i < Components.get_cursor(); i++)
		{
			Components[i]->tick();
		}
	}
	void IterativeLogicFunction::finalize()
	{

	}
}