#include "Application.h"
#include <Engine/Application/ApplicationSession.h>
#include <Engine/Application/ApplicationModule.h>
#include <Engine/Window/Window.h>
#include <Engine/Window/WindowEvent.h>
#include <Engine/Containers/String.h>
#include <Engine/Message/Message.h>
#include <Engine/Time/GameTime.h>
#include <iostream>
#include <chrono>
namespace Engine
{

	Application::Application(const WindowCreateDesc& desc)
	{
		PerFrameEventBufferCursor = false;
		Running = false;
		AppWindow = new Window(desc, this);
	}
	
	void Application::run()
	{
		/*
		* Create session
		*/
		ApplicationSession* appSession = new ApplicationSession(AppWindow);

		String exitReason = "Undefined reason!";
		bool internalRunningState = true;

		AppWindow->show_window();

		/*
		* Initialize app modules
		*/
		Running = true;
		for (unsigned int i = 0; i < Modules.get_cursor(); i++)
		{
			ApplicationModule* module = Modules[i];
			module->_set_owner_session(appSession);
			module->initialize();
		}

		/*
		* Run app loop
		*/
		while (internalRunningState)
		{
			auto start = std::chrono::steady_clock::now();
			
			/*
			* Update window messages
			*/
			AppWindow->update_messages();

			/*
			* Forward window messages
			*/
			for (unsigned int i = 0; i < PerFrameEventBufferCursor; i++)
			{
				WindowEvent* event = PerFrameEventBuffer[i];
				for (int p = Modules.get_cursor() - 1; p >= 0; p--)
				{
					ApplicationModule* module = Modules[p];

					module->received_event(event);
					if (event->is_handled())
						break;
				}
			}
			for (unsigned int i = 0; i < PerFrameEventBufferCursor; i++)
			{
				delete PerFrameEventBuffer[i];
			}
			PerFrameEventBufferCursor = 0;

			/*
			* Update all app modules
			*/
			for (unsigned int i = 0; i < Modules.get_cursor(); i++)
				Modules[i]->tick();

			/*
			* Post update all app modules
			*/
			for (unsigned int i = 0; i < Modules.get_cursor(); i++)
				Modules[i]->post_tick();
			/*
			* Swap app window swapchain buffers
			*/
			AppWindow->swap_buffers();

			/*
			* Validate app close request
			*/
			if (AppWindow->has_close_request())
			{
				internalRunningState = false;
				exitReason = "Window close request";
			}

			/*
			* Calculate frame delta time
			*/
			auto end = std::chrono::steady_clock::now();
			long long ms = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
			const float deltaTime = ms / 1000.0f;

			GameTime::_set_delta_time(deltaTime);
		}

		for (unsigned int i = 0; i < Modules.get_cursor(); i++)
		{
			ApplicationModule* module = Modules[i];
			module->finalize();
			module->_set_owner_session(nullptr);
			delete module;
		}

		MESSAGE("Application", "Exit reason: %s", *exitReason);
	}
	void Application::dispatch_event(WindowEvent* event)
	{
		PerFrameEventBuffer[PerFrameEventBufferCursor++] = event;
		ASSERT(PerFrameEventBufferCursor < PER_FRAME_MAX_EVENT_COUNT, "Application", "PerFrameEventBuffer overflown");
	}
}
	
