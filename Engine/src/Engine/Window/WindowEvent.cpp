#include "WindowEvent.h"

namespace Engine
{
    bool WindowEvent::is_handled() const
    {
        return Handled;
    }

    void WindowEvent::mark_handled()
    {
        Handled = true;
    }
}