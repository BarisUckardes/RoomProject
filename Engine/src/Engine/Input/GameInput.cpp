#include "GameInput.h"
#include <Engine/Input/GameInputBlob.h>
#include <Engine/Message/Message.h>

namespace Engine
{
	const GameInputBlob* GameInput::InputBlob = nullptr;

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
		return InputBlob->Keys[key] == 1 || InputBlob->Keys[key] == 2; // 1 and 2 is the down state
	}
	bool GameInput::is_key_up(const unsigned int key)
	{
		return InputBlob->Keys[key] == 3;
	}
	bool GameInput::is_button_down(const unsigned int button)
	{
		return InputBlob->Buttons[button] == 1;
	}
	void GameInput::_set_input_blob(const GameInputBlob* blob)
	{
		InputBlob = blob;
	}
}