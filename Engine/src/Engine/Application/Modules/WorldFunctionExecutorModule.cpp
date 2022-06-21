#include "WorldFunctionExecutorModule.h"
#include <Engine/World/World.h>
#include <Engine/World/WorldFunction.h>
#include <Engine/Application/ApplicationSession.h>
namespace Engine
{
	void WorldFunctionExecutorModule::initialize()
	{

	}
	void WorldFunctionExecutorModule::tick()
	{
		World* gameWorld = get_owner_session()->get_game_world();

		Array<WorldFunction*> functions = gameWorld->get_functions();
		for (unsigned int i = 0; i < functions.get_cursor(); i++)
		{
			functions[i]->execute();
		}
	}
	void WorldFunctionExecutorModule::finalize()
	{

	}
	void WorldFunctionExecutorModule::received_event(WindowEvent* event)
	{

	}
	void WorldFunctionExecutorModule::post_tick()
	{
	}
}