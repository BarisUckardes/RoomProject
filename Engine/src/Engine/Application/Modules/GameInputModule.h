#pragma once
#include <Engine/Input/GameInputBlob.h>
#include <Engine/Application/ApplicationModule.h>s

namespace Engine
{
	class ENGINE_API GameInputModule : public ApplicationModule
	{
	public:
		GameInputModule(): Blob(nullptr) {}
		~GameInputModule() = default;

		virtual void initialize() override;
		virtual void tick() override;
		virtual void post_tick() override;
		virtual void finalize() override;
		virtual void received_event(WindowEvent* event) override;
	private:
		GameInputBlob* Blob;


	};


}