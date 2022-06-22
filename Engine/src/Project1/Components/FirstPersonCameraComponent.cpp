#include "FirstPersonCameraComponent.h"
#include <Engine/Input/InputCore.h>
#include <ForwardRenderer/SpatialComponent.h>
#include <Engine/World/Entity.h>
#include <Engine/Time/GameTime.h>
#include <Engine/Message/Message.h>

#define PLAYER_HEIGHT 5.0f
namespace Engine
{
    FirstPersonCameraComponent::FirstPersonCameraComponent(const float movementSpeed, const float angularSpeed)
    {
        MovementSpeed = movementSpeed;
        AngularSpeed = angularSpeed;
    }

    void FirstPersonCameraComponent::tick()
    {
        SpatialComponent* spatial = get_owner_entity()->get_component<SpatialComponent>();

        /*
        * Calculate movement
        */
        if (GameInput::is_key_down((unsigned int)'W'))
        {
            spatial->set_position(spatial->get_position() + GameTime::get_delta_time() * MovementSpeed * spatial->get_forward_vector());
        }
        else if (GameInput::is_key_down((unsigned int)'S'))
        {
            spatial->set_position(spatial->get_position() + GameTime::get_delta_time() * -MovementSpeed * spatial->get_forward_vector());
        }
        if (GameInput::is_key_down((unsigned int)'A'))
        {
            spatial->set_position(spatial->get_position() + GameTime::get_delta_time() * MovementSpeed * spatial->get_right_vector());
        }
        else if (GameInput::is_key_down((unsigned int)'D'))
        {
            spatial->set_position(spatial->get_position() + GameTime::get_delta_time() * -MovementSpeed * spatial->get_right_vector());
        }

        glm::vec3 pos = spatial->get_position();
        pos.y = PLAYER_HEIGHT;
       // spatial->set_position(pos);

        /*
        * Validate if user wants to rotate
        */
        if (GameInput::is_button_down(0))
        {
            /*
            * Calculate angular movement
            */
            const float mouseDeltaX = GameInput::get_mouse_delta_x();
            const float mouseDeltaY = GameInput::get_mouse_delta_y();
            spatial->set_rotation(spatial->get_rotation() + glm::vec3(mouseDeltaY, -mouseDeltaX, 0) * GameTime::get_delta_time() * AngularSpeed);
        }
        
    }

}