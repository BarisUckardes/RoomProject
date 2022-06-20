#pragma once
#include <Engine/Window/Keyboard/WindowKeyEvent.h>

namespace Engine
{
	/// <summary>
	/// Represents a keyboard key up event
	/// </summary>
	class ENGINE_API KeyboardKeyUpEvent final : public WindowKeyEvent
	{
	public:
		KeyboardKeyUpEvent(const unsigned int key);
		~KeyboardKeyUpEvent() = default;

		// Inherited via WindowKeyEvent
		virtual WindowEventType get_event_type() const override;
		virtual String get_event_message() const override;
	};


}