#pragma once
#include <Engine/Window/WindowEvent.h>

namespace Engine
{
	/// <summary>
	/// Represents a window moved event, contains the new window position properties such as the current position of the window X-Y
	/// </summary>
	class ENGINE_API WindowMovedEvent final : public WindowEvent
	{
	public:
		WindowMovedEvent(const unsigned int positionX, const unsigned int positionY);
		~WindowMovedEvent() = default;

		FORCEINLINE unsigned int get_position_x() const;
		FORCEINLINE unsigned int get_position_y() const;

		// Inherited via WindowEvent
		virtual WindowEventType get_event_type() const override;
		virtual String get_event_message() const override;
	private:
		unsigned int PositionX;
		unsigned int PositionY;
	};


}