#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Containers/String.h>

namespace Engine
{
	class Window;
	class World;
	class ENGINE_API ApplicationSession
	{
	public:
		ApplicationSession(Window* window);
		~ApplicationSession();

		FORCEINLINE Window* get_app_window() const;
		FORCEINLINE World* get_game_world() const;

		World* create_world(const String& name);
	private:
		Window* AppWindow;
		World* GameWorld;
	};


}