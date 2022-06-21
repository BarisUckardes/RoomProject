#pragma once
#include <IterativeLogic/LogicComponent.h>

namespace Engine
{
	class FirstPersonCameraComponent : public LogicComponent
	{
		GENERATE_COMPONENT(FirstPersonCameraComponent)
	public:
		FirstPersonCameraComponent(const float movementSpeed = 10.0f, const float angularSpeed = 25.0f);
		~FirstPersonCameraComponent() = default;
		virtual void tick() override;

	private:
		float MovementSpeed;
		float AngularSpeed;

	};


}