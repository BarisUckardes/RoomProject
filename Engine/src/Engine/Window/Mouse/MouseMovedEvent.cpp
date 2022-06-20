#include "MouseMovedEvent.h"


namespace Engine
{
	MouseMovedEvent::MouseMovedEvent(const unsigned int x, const unsigned int y)
	{
		X = x;
		Y = y;
	}
	unsigned int MouseMovedEvent::get_x() const
	{
		return X;
	}
	unsigned int MouseMovedEvent::get_y() const
	{
		return Y;
	}
	WindowEventType MouseMovedEvent::get_event_type() const
	{
		return WindowEventType::MouseMoved;
	}
	String MouseMovedEvent::get_event_message() const
	{
		return "New mouse location X:" + String::get_from_integer(X) + " Y:" + String::get_from_integer(Y);
	}
}