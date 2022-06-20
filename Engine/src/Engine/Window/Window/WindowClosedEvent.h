#pragma once
#include <Engine/Window/WindowEvent.h>

namespace Engine
{
	/// <summary>
	/// Represents a window closed event
	/// </summary>
	class ENGINE_API WindowClosedEvent final : public WindowEvent
	{
	public:
		WindowClosedEvent() = default;
		~WindowClosedEvent() = default;

		virtual WindowEventType get_event_type() const override;
		virtual String get_event_message() const override;
	};
}