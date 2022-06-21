#include "ApplicationSession.h"
#include <Engine/World/World.h>
#include <Engine/Message/Message.h>

namespace Engine
{
	ApplicationSession::ApplicationSession(Window* window)
	{
		AppWindow = window;
		GameWorld = nullptr;
	}
	ApplicationSession::~ApplicationSession()
	{
	}
	Window* ApplicationSession::get_app_window() const
	{
		return AppWindow;
	}
	World* ApplicationSession::get_game_world() const
	{
		return GameWorld;
	}
	World* ApplicationSession::create_world(const String& name)
	{
		ASSERT(GameWorld == nullptr, "ApplicationSession", "This engine supports only one world!");

		World* world = new World(this,name);

		GameWorld = world;

		return world;
	}
}