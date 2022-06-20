#include "WindowClosedEvent.h"

namespace Engine
{
	WindowEventType WindowClosedEvent::get_event_type() const
	{
		return WindowEventType::WindowClosed;
	}
	String WindowClosedEvent::get_event_message() const
	{
		return "Window closed!";
	}
}