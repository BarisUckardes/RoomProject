#include "Window.h"
#include <Engine/Message/Message.h>

namespace Engine
{
	bool Window::has_close_request() const
	{
		return CloseRequest;
	}

	void Window::update_messages()
	{
		MSG msg = { 0 };
		while (PeekMessage(&msg, WindowHandle, 0, 0, PM_REMOVE) > 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	void Window::swap_buffers()
	{
		SwapBuffers(WindowDeviceContext);
	}
	void Window::show_window(const bool state)
	{
		ShowWindow(WindowHandle,state == true ? SW_SHOW : SW_HIDE);
	}

	Window::Window(const WindowCreateDesc& desc)
	{
		constexpr wchar_t WINDOW_CLASS_NAME[] = L"Win32Window";

		/*
		* Initialize
		*/
		CloseRequest = false;

		/*
		* Create win32 window class
		*/
		HINSTANCE processHandle = GetModuleHandle(0);

		WNDCLASSEX wc = { 0 };
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
		wc.lpfnWndProc = (WNDPROC)Win32WindowMessageProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = sizeof(Window);
		wc.hInstance = processHandle;
		wc.hCursor = LoadIcon(NULL, IDC_ARROW);
		wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
		wc.hbrBackground = NULL;
		wc.lpszMenuName = NULL;
		wc.lpszClassName = WINDOW_CLASS_NAME;
		wc.hIconSm = NULL;
	
		ASSERT(RegisterClassEx(&wc) != NULL, "Win32Window", "Window class registration failed!");

		/*
		* Create win32 window
		*/
		HWND windowHandle = CreateWindowEx(
			0,
			WINDOW_CLASS_NAME,
			L"Win32Window",
			WS_OVERLAPPEDWINDOW,
			desc.PositionX, desc.PositionY, desc.Width, desc.Height,
			NULL,
			NULL,
			processHandle,
			this
		);

		ASSERT(windowHandle != NULL, "Win32Window", "Window creation failed");

		WindowHandle = windowHandle;
		WindowDeviceContext = GetDC(WindowHandle);
	}
	Window::~Window()
	{

	}
	Window* get_user_window_data(HWND windowHandle)
	{
		return (Window*)GetWindowLongPtr(windowHandle, -21);
	}
	LRESULT Window::Win32WindowMessageProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (uMsg)
		{
			case WM_CREATE:
			{
				Window* userWindow = (Window*)((LPCREATESTRUCT)lParam)->lpCreateParams;
				SetWindowLongPtr(hwnd, -21, (LONG_PTR)userWindow);
				break;
			}
			case WM_CLOSE:
			{
				Window* userWindow = get_user_window_data(hwnd);
				userWindow->CloseRequest = true;
				break;
			}
			case WM_SIZE:
			{
				const unsigned int width = LOWORD(lParam);
				const unsigned int height = HIWORD(lParam);

				MESSAGE("Win32Window", "Width: %d, Height: %d", width, height);
				
				break;
			}
		}

		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}