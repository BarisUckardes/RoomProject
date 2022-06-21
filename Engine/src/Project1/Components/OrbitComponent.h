#pragma once
#include <IterativeLogic/LogicComponent.h>
#include <glm/vec3.hpp>

namespace Engine
{
	class ENGINE_API OrbitComponent : public LogicComponent
	{
		GENERATE_COMPONENT(OrbitComponent)
	public:
		OrbitComponent(const glm::vec3& center = {0,2,0}, const float radius = 15, const float speed = 260.0f);
		~OrbitComponent() = default;

		virtual void tick() override;
	private:
		glm::vec3 Center;
		float Radius;
		float Speed;
		float CurrentDegree;


	};


}