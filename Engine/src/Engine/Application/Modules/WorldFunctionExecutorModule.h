#pragma once
#include <Engine/Application/ApplicationModule.h>

namespace Engine
{
	class ENGINE_API WorldFunctionExecutorModule : public ApplicationModule
	{
	public:


		// Inherited via ApplicationModule
		virtual void initialize() override;
		virtual void tick() override;
		virtual void post_tick() override;
		virtual void finalize() override;
		virtual void received_event(WindowEvent* event) override;




	};
}