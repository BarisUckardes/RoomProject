#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Input/GameInputBlob.h>

namespace Engine
{
	class ENGINE_API GameInput
	{
		friend class GameInputModule;
	public:
		GameInput() = default;
		~GameInput() = default;

		FORCEINLINE static unsigned int get_mouse_pos_x();
		FORCEINLINE static unsigned int get_mouse_pos_y();
		FORCEINLINE static float get_mouse_delta_x();
		FORCEINLINE static float get_mouse_delta_y();
		FORCEINLINE static bool is_key_down(const unsigned int key);
		FORCEINLINE static bool is_key_pressed(const unsigned int key);
		FORCEINLINE static bool is_button_pressed(const unsigned int key);
		FORCEINLINE static bool is_key_up(const unsigned int key);
		FORCEINLINE static bool is_button_down(const unsigned int button);
	private:
		static void _set_input_blob(const GameInputBlob* blob);
	private:
		static const GameInputBlob* InputBlob;
	};


}