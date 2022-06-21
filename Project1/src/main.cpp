#include <stdio.h>
#include <Engine/Window/Window.h>
#include <Engine/Application/Application.h>
#include "../Modules/StartupModule.h"

int main(int argumentCount, const char** arguments)
{
	Engine::WindowCreateDesc windowCreateDesc = {};
	windowCreateDesc.PositionX = 100;
	windowCreateDesc.PositionY = 100;
	windowCreateDesc.Width = 512;
	windowCreateDesc.Height = 512;
	windowCreateDesc.Title = "Room/Project/1";

	Engine::Application application = Engine::Application(windowCreateDesc);
	application.create_module<StartupModule>();

	application.run();
}