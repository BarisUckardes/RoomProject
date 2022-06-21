#include "GameTime.h"

namespace Engine
{
	float GameTime::DeltaTime = 0;

	float GameTime::get_delta_time()
	{
		return DeltaTime;
	}
	void GameTime::_set_delta_time(const float deltaTime)
	{
		DeltaTime = deltaTime;
	}
}