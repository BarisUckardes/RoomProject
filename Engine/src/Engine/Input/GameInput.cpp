#include "GameInput.h"
#include <Engine/Input/GameInputBlob.h>
#include <Engine/Message/Message.h>

namespace Engine
{
	const GameInputBlob* GameInput::InputBlob = nullptr;

	unsigned int GameInput::get_mouse_pos_x()
	{
		return InputBlob->MousePositionX;
	}

	unsigned int GameInput::get_mouse_pos_y()
	{
		return InputBlob->MousePositionY;
	}

	float GameInput::get_mouse_delta_x()
	{
		return InputBlob->MouseDeltaX;
	}
	float GameInput::get_mouse_delta_y()
	{
		return InputBlob->MouseDeltaY;
	}
	bool GameInput::is_key_down(const unsigned int key)
	{
		return InputBlob->Keys[key] >= 1; // 1 and 2 is the down state
	}

	bool GameInput::is_key_pressed(const unsigned int key)
	{
		return InputBlob->Keys[key] == 1;
	}
	
	bool GameInput::is_key_up(const unsigned int key)
	{
		return InputBlob->Keys[key] == 0;
	}
	bool GameInput::is_button_pressed(const unsigned int key)
	{
		return InputBlob->Buttons[key] == 1;
	}
	bool GameInput::is_button_down(const unsigned int button)
	{
		return InputBlob->Buttons[button] >= 1;
	}
	void GameInput::_set_input_blob(const GameInputBlob* blob)
	{
		InputBlob = blob;
	}
}