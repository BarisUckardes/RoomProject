#pragma once
#include <Engine/Core/Symbols.h>
#include <Windows.h>

namespace Engine
{
	class WindowEvent;
	class Application;
	/// <summary>
	/// Required fields sto create a window
	/// </summary>
	struct ENGINE_API WindowCreateDesc
	{
		const char* Title;
		unsigned int PositionX;
		unsigned int PositionY;
		unsigned int Width;
		unsigned int Height;
	};

	/// <summary>
	/// Authoring class for window
	/// </summary>
	class ENGINE_API Window
	{
	public:
		Window(const WindowCreateDesc& desc,Application* listenerApplication);
		~Window();

		FORCEINLINE bool has_close_request() const;

		void update_messages();
		void swap_buffers();
		void show_window(const bool state = true);
	private:
		static LRESULT CALLBACK Win32WindowMessageProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

		FORCEINLINE void _broadcast_event(WindowEvent* event);
	private:
		Application* ListenerApplication;
		HWND WindowHandle;
		HDC WindowDeviceContext;
		HGLRC WindowGLContext;
		unsigned int PositionX;
		unsigned int PositionY;
		unsigned int Width;
		unsigned int Height;
		bool CloseRequest;
	};
}