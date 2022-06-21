#pragma once
#include <Engine/Core/Symbols.h>

namespace Engine
{
#define KEY_COUNT 256
#define BUTTON_COUNT 2

	struct ENGINE_API GameInputBlob
	{
		GameInputBlob()
		{
			for (unsigned int i = 0; i < KEY_COUNT; i++)
			{
				Keys[i] = 0; // default state;
			}
			for (unsigned int i = 0; i < BUTTON_COUNT; i++)
			{
				Buttons[i] = 0;
			}
			MouseDeltaX = 0;
			MouseDeltaY = 0;
			MousePositionX = 0;
			MousePositionY = 0;
		}
		~GameInputBlob() = default;

		unsigned int Keys[KEY_COUNT];
		unsigned int Buttons[BUTTON_COUNT];
		float MouseDeltaX;
		float MouseDeltaY;
		unsigned int MousePositionX;
		unsigned int MousePositionY;
	};
}