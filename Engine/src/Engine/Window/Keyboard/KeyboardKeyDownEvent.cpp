#include "KeyboardKeyDownEvent.h"

namespace Engine
{
	KeyboardKeyDownEvent::KeyboardKeyDownEvent(const unsigned int key) : WindowKeyEvent(key)
	{

	}
	WindowEventType KeyboardKeyDownEvent::get_event_type() const
	{
		return WindowEventType::KeyDown;
	}
	String KeyboardKeyDownEvent::get_event_message() const
	{
		return "Key pressed: " + String::get_from_integer(get_related_key());
	}
}