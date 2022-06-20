#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Containers/Array.h>

#define PER_FRAME_MAX_EVENT_COUNT 2048
namespace Engine
{
	class ApplicationModule;
	class WindowEvent;
	class Window;
	struct WindowCreateDesc;
	class ENGINE_API Application
	{
	public:
		Application(const WindowCreateDesc& desc);
		~Application() = default;

		void run();
		void dispatch_event(WindowEvent* event);
	private:
		Window* AppWindow;
		bool Running;
		Array<ApplicationModule*> Modules;
		WindowEvent* PerFrameEventBuffer[PER_FRAME_MAX_EVENT_COUNT];
		unsigned int PerFrameEventBufferCursor;
	};
}