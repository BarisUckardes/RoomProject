#include "Application.h"
#include <Engine/Application/ApplicationSession.h>
#include <Engine/Application/ApplicationModule.h>
#include <Engine/Window/Window.h>
#include <Engine/Window/WindowEvent.h>
#include <Engine/Containers/String.h>
#include <Engine/Message/Message.h>

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
		ApplicationSession* appSession = new ApplicationSession(AppWindow);

		String exitReason = "Undefined reason!";
		bool internalRunningState = true;

		AppWindow->show_window();

		Running = true;
		for (unsigned int i = 0; i < Modules.get_cursor(); i++)
		{
			ApplicationModule* module = Modules[i];
			module->_set_owner_session(appSession);
			module->initialize();
		}
		while (internalRunningState)
		{
			AppWindow->update_messages();

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

			for (unsigned int i = 0; i < Modules.get_cursor(); i++)
				Modules[i]->tick();

			AppWindow->swap_buffers();

			if (AppWindow->has_close_request())
			{
				internalRunningState = false;
				exitReason = "Window close request";
			}
		}

		MESSAGE("Application", "Exit reason: %s", *exitReason);
	}
	void Application::dispatch_event(WindowEvent* event)
	{
		PerFrameEventBuffer[PerFrameEventBufferCursor++] = event;
		ASSERT(PerFrameEventBufferCursor < PER_FRAME_MAX_EVENT_COUNT, "Application", "PerFrameEventBuffer overflown");
	}
}
	
