#include <stdio.h>
#include <Engine/Window/Window.h>

int main(int argumentCount, const char** arguments)
{
	Engine::WindowCreateDesc windowCreateDesc = {};
	windowCreateDesc.PositionX = 100;
	windowCreateDesc.PositionY = 100;
	windowCreateDesc.Width = 512;
	windowCreateDesc.Height = 512;
	windowCreateDesc.Title = "Room/Project/1";

	Engine::Window* window = new Engine::Window(windowCreateDesc);
	window->show_window();

	while (!window->has_close_request())
	{
		window->update_messages();
		window->swap_buffers();
	}
}