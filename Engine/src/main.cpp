#include "Engine/Application/Application.h"
#include "Engine/Window/Window.h"
#include "Project1/StartupModule1.h"
#include "Engine/Application/Modules/WorldFunctionExecutorModule.h"
#include "Engine/Path/PathUtils.h"
#include "Engine/Application/Modules/GameInputModule.h"

int main(int argumentCount, const char** arguments)
{
	Engine::WindowCreateDesc windowCreateDesc = {};
	windowCreateDesc.PositionX = 100;
	windowCreateDesc.PositionY = 100;
	windowCreateDesc.Width = 1280;
	windowCreateDesc.Height = 720;
	windowCreateDesc.Title = "Room/Project/1";

	Engine::Application* application = new Engine::Application(windowCreateDesc);
#ifdef RUN_PROJECT_1
	application->create_module<Engine::StartupModule1>();
#else
	application->create_module<Engine::StartupModule1>();
#endif
	application->create_module<Engine::GameInputModule>();
	application->create_module<Engine::WorldFunctionExecutorModule>();
	application->run();


	return 0;
}
