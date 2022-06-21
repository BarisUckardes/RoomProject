#pragma once
#include <Engine/World/Component.h>

namespace Engine
{
	class ENGINE_API LogicComponent : public Component
	{
		GENERATE_COMPONENT(LogicComponent)
	public:
		LogicComponent() = default;
		~LogicComponent() = default;

		virtual void initialize() override;
		FORCEINLINE virtual void tick() = 0;
		virtual void finalize() override;
	};


}