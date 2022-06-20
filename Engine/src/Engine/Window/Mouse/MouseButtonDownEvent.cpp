#include "MouseButtonDownEvent.h"

namespace Engine
{
    MouseButtonDownEvent::MouseButtonDownEvent(const unsigned int button) : WindowMouseButtonEvent(button)
    {

    }
    WindowEventType MouseButtonDownEvent::get_event_type() const
    {
        return WindowEventType::MouseButtonDown;
    }
    String MouseButtonDownEvent::get_event_message() const
    {
        return "Mouse button down: " + String::get_from_integer(get_related_button());
    }
}