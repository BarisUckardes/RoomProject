#include "WindowResizedEvent.h"

namespace Engine
{
	WindowResizedEvent::WindowResizedEvent(const unsigned int width, const unsigned height)
	{
		Width = width;
		Height = height;
	}
	unsigned int WindowResizedEvent::get_width() const
	{
		return Width;
	}
	unsigned int WindowResizedEvent::get_height() const
	{
		return Height;
	}
	WindowEventType WindowResizedEvent::get_event_type() const
	{
		return WindowEventType::WindowResized;
	}
	String WindowResizedEvent::get_event_message() const
	{
		return "New window size X:" + String::get_from_integer(Width) + " Y:" + String::get_from_float(Height);
	}
}