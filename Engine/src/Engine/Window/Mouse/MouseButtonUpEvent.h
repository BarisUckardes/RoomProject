#pragma once
#include <Engine/Window/Mouse/WindowMouseButtonEvent.h>

namespace Engine
{
	/// <summary>
	/// Represents a mouse butotn up event
	/// </summary>
	class ENGINE_API MouseButtonUpEvent final : public WindowMouseButtonEvent
	{
	public:
		MouseButtonUpEvent(const unsigned int button);
		~MouseButtonUpEvent() = default;

		// Inherited via WindowMouseButtonEvent
		virtual WindowEventType get_event_type() const override;
		virtual String get_event_message() const override;
	};


}