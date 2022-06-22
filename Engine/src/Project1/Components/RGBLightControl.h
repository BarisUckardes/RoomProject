#pragma once
#include <IterativeLogic/LogicComponent.h>

namespace Engine
{
	class ForwardPointLight;
	class ENGINE_API RGBLightControl : public LogicComponent
	{
		GENERATE_COMPONENT(RGBLightControl)
	public:
		RGBLightControl(ForwardPointLight* light);
		~RGBLightControl() = default;


		// Inherited via LogicComponent
		virtual void tick() override;
	private:
		ForwardPointLight* Light;
	};


}