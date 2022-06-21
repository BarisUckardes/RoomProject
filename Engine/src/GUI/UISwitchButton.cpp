#include "UISwitchButton.h"

namespace Engine
{
	UISwitchButton::UISwitchButton(Component* component)
	{
		TargetComponent = component;
	}
	void UISwitchButton::on_button_click()
	{
		TargetComponent->set_active(!TargetComponent->is_active());
	}
}