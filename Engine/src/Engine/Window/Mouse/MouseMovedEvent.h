#pragma once
#include <Engine/Window/WindowEvent.h>

namespace Engine
{
	/// <summary>
	/// Represents a mouse moved event, contains the new mouse location properties such as new x-y positions
	/// </summary>
	class ENGINE_API MouseMovedEvent final : public WindowEvent
	{
	public:
		MouseMovedEvent(const unsigned int x, const unsigned int y);
		~MouseMovedEvent() = default;

		FORCEINLINE unsigned int get_x() const;
		FORCEINLINE unsigned int get_y() const;

		// Inherited via WindowEvent
		virtual WindowEventType get_event_type() const override;
		virtual String get_event_message() const override;
	private:
		unsigned int X;
		unsigned int Y;

	};


}