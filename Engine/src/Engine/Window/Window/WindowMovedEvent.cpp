#include "WindowMovedEvent.h"

namespace Engine
{
	WindowMovedEvent::WindowMovedEvent(const unsigned int positionX, const unsigned int positionY)
	{
		PositionX = positionX;
		PositionY = positionY;
	}
	unsigned int WindowMovedEvent::get_position_x() const
	{
		return PositionX;
	}
	unsigned int WindowMovedEvent::get_position_y() const
	{
		return PositionY;
	}
	WindowEventType WindowMovedEvent::get_event_type() const
	{
		return WindowEventType::WindowMoved;
	}
	String WindowMovedEvent::get_event_message() const
	{
		return "New window position X:" + String::get_from_integer(PositionX) + " Y:" + String::get_from_integer(PositionY);
	}
}