#include "GameInputModule.h"
#include <Engine/Window/WindowEvents.h>
#include <Engine/Input/GameInput.h>
#include <Engine/Message/Message.h>
#include <cmath>

#define MOUSE_DELTA_THRESHOLD 250
namespace Engine
{
    void GameInputModule::initialize()
    {
        Blob = new GameInputBlob();
       
        GameInput::_set_input_blob(Blob);
    }
    void GameInputModule::tick()
    {

    }
    void GameInputModule::finalize()
    {

    }
    void GameInputModule::received_event(WindowEvent* event)
    {
        WindowEventType type = event->get_event_type();

        switch (type)
        {
            case Engine::WindowEventType::KeyDown:
            {
                WindowKeyEvent* eventData = (WindowKeyEvent*)event;
                const unsigned int key = eventData->get_related_key();

                Blob->Keys[key] = 1;
                break;
            }
            case Engine::WindowEventType::KeyUp:
            {
                WindowKeyEvent* eventData = (WindowKeyEvent*)event;
                const unsigned int key = eventData->get_related_key();

                Blob->Keys[key] = 0;
                break;
            }
            case Engine::WindowEventType::MouseButtonDown:
            {
                WindowMouseButtonEvent* eventData = (WindowMouseButtonEvent*)event;
                const unsigned int button = eventData->get_related_button();

                Blob->Buttons[button] = 1;
                break;
            }
            case Engine::WindowEventType::MouseButtonUp:
            {
                WindowMouseButtonEvent* eventData = (WindowMouseButtonEvent*)event;
                const unsigned int button = eventData->get_related_button();

                Blob->Buttons[button] = 0;
                break;
            }
            case Engine::WindowEventType::MouseMoved:
            {
                MouseMovedEvent* eventData = (MouseMovedEvent*)event;
                const unsigned int x = eventData->get_x();
                const unsigned int y = eventData->get_y();

                const float deltaX = (float)Blob->MousePositionX - (float)x;
                const float deltaY = (float)Blob->MousePositionY - (float)y;

                Blob->MousePositionX = x;
                Blob->MousePositionY = y;

                Blob->MouseDeltaX = abs(deltaX) > MOUSE_DELTA_THRESHOLD ? 0 : deltaX;
                Blob->MouseDeltaY = abs(deltaY) > MOUSE_DELTA_THRESHOLD ? 0 : deltaY;

                break;
            }
            default:
                break;
        }

        event->mark_handled();
    }
    void GameInputModule::post_tick()
    {
        Blob->MouseDeltaX = 0;
        Blob->MouseDeltaY = 0;
    }
}