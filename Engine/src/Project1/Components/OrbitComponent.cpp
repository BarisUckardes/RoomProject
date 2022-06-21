#include "OrbitComponent.h"
#include <ForwardRenderer/SpatialComponent.h>
#include <Engine/World/Entity.h>
#include <Engine/Time/GameTime.h>
#include <glm/gtc/matrix_transform.hpp>
namespace Engine
{
    OrbitComponent::OrbitComponent(const glm::vec3& center, const float radius, const float speed)
    {
        Center = center;
        Radius = radius;
        Speed = speed;
    }
    void OrbitComponent::tick()
    {
        SpatialComponent* spatial = get_owner_entity()->get_component<SpatialComponent>();
        
        const float x = cos(glm::radians(CurrentDegree));
        const float y = sin(glm::radians(CurrentDegree));

        glm::vec3 dir = { x,0,y };
        glm::vec3 pos = Center + dir * Radius;

        spatial->set_position(pos);

        CurrentDegree += Speed * GameTime::get_delta_time();

    }
}