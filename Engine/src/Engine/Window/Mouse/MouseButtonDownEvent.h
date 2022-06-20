#pragma once
#include <Engine/Window/Mouse/WindowMouseButtonEvent.h>

namespace Engine
{
	/// <summary>
	/// Represents a mouse button down event
	/// </summary>
	class ENGINE_API MouseButtonDownEvent final : public WindowMouseButtonEvent
	{
	public:
		MouseButtonDownEvent(const unsigned int button);
		~MouseButtonDownEvent() = default;

		// Inherited via WindowMouseButtonEvent
		virtual WindowEventType get_event_type() const override;
		virtual String get_event_message() const override;

	};


}