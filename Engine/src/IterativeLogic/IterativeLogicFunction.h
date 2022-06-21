#pragma once
#include <Engine/World/WorldFunction.h>
#include <Engine/Containers/Array.h>

namespace Engine
{
	class LogicComponent;
	class ENGINE_API IterativeLogicFunction : public WorldFunction
	{
		GENERATE_WORLD_FUNCTION(IterativeLogicFunction)
	public:
		IterativeLogicFunction() = default;
		~IterativeLogicFunction() = default;

		FORCEINLINE void register_component(LogicComponent* component);
		FORCEINLINE void remove_component(LogicComponent* component);

		virtual void initialize() override;
		virtual void execute() override;
		virtual void finalize() override;

	private:
		Array<LogicComponent*> Components;
	};
}