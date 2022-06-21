#pragma once
#include <Engine/Core/Symbols.h>

namespace Engine
{
	class ENGINE_API GameTime
	{
		friend class Application;
	public:
		GameTime() = delete;
		~GameTime() = delete;

		FORCEINLINE static float get_delta_time();
	private:
		FORCEINLINE static void _set_delta_time(const float deltaTime);
	private:
		static float DeltaTime;
	};


}