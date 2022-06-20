#pragma once
#include <Engine/Core/Symbols.h>

namespace Engine
{
	class Window;
	class ENGINE_API ApplicationSession
	{
	public:
		ApplicationSession(Window* window);
		~ApplicationSession();

		FORCEINLINE Window* get_app_window() const;
	private:
		Window* AppWindow;
	};


}