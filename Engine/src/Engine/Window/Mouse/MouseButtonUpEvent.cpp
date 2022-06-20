#include "MouseButtonUpEvent.h"

namespace Engine
{
	MouseButtonUpEvent::MouseButtonUpEvent(const unsigned int button) : WindowMouseButtonEvent(button)
	{

	}
	WindowEventType MouseButtonUpEvent::get_event_type() const
	{
		return WindowEventType::MouseButtonUp;
	}
	String MouseButtonUpEvent::get_event_message() const
	{
		return "Mouse button up: " + String::get_from_integer(get_related_button());
	}
}