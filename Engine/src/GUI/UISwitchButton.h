#pragma once
#include <GUI/UIRectButton.h>

namespace Engine
{
	class ENGINE_API UISwitchButton final : public UIRectButton
	{
		GENERATE_COMPONENT(UISwitchButton)
	public:
		UISwitchButton(Component* component);
		~UISwitchButton() = default;

	
		// Inherited via UIRectButton
		virtual void on_button_click() override;
	private:
		Component* TargetComponent;

	};


}