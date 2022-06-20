#include "KeyboardKeyUpEvent.h"

namespace Engine
{
    KeyboardKeyUpEvent::KeyboardKeyUpEvent(const unsigned int key) : WindowKeyEvent(key)
    {

    }
    WindowEventType KeyboardKeyUpEvent::get_event_type() const
    {
        return WindowEventType::KeyUp;
    }
    String KeyboardKeyUpEvent::get_event_message() const
    {
        return "Key up: " + String::get_from_integer(get_related_key());
    }
}