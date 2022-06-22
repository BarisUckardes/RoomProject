#include "RGBLightControl.h"
#include <ForwardRenderer/ForwardPointLight.h>
#include <Engine/Input/InputCore.h>

namespace Engine
{
	RGBLightControl::RGBLightControl(ForwardPointLight* light)
	{
		Light = light;
	}
	void RGBLightControl::tick()
	{
		if (GameInput::is_key_down((unsigned int)'R'))
		{
			Light->set_color({ 1.0f,0.2f,0.1f });
		}		
		else if (GameInput::is_key_down((unsigned int)'G'))
		{				
			Light->set_color({ 2.0f,1.2f,0.1f });
		}
		else if (GameInput::is_key_down((unsigned int)'B'))
		{
			Light->set_color({ 0.1f,0.2f,1.0f });
		}
	}
}