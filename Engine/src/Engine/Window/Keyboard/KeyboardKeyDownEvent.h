#pragma once
#include <Engine/Window/Keyboard/WindowKeyEvent.h>

namespace Engine
{
	/// <summary>
	/// Represents a keyboard down event
	/// </summary>
	class ENGINE_API KeyboardKeyDownEvent final : public WindowKeyEvent
	{
	public:
		KeyboardKeyDownEvent(const unsigned int key);
		~KeyboardKeyDownEvent() = default;

		// Inherited via WindowKeyEvent
		virtual WindowEventType get_event_type() const override;
		virtual String get_event_message() const override;
	};


}