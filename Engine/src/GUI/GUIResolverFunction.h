#pragma once
#include <Engine/World/WorldFunction.h>
#include <Engine/Containers/Array.h>

namespace Engine
{
	class UIRectButton;
	class ENGINE_API GUIResolverFunction : public WorldFunction
	{
		GENERATE_WORLD_FUNCTION(GUIResolverFunction)
	public:
		GUIResolverFunction() = default;
		~GUIResolverFunction() = default;

		FORCEINLINE void register_button(UIRectButton* rect);
		FORCEINLINE void remove_button(UIRectButton* rect);

		virtual void initialize() override;
		virtual void execute() override;
		virtual void finalize() override;
	private:
		Array<UIRectButton*> Buttons;
	};
}