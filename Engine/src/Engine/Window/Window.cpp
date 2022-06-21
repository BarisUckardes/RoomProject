#include "Window.h"
#include <Engine/Message/Message.h>
#include <Engine/Window/WindowEvents.h>
#include <Engine/Input/InputCore.h>
#include <Engine/Application/Application.h>
#include <GLAD/glad.h>
#include <gl/GL.h>

typedef HGLRC(WINAPI* PFNWGLCREATECONTEXTATTRIBSARBPROC) (HDC hDC, HGLRC hShareContext, const int* attribList);
typedef const char* (WINAPI* PFNWGLGETEXTENSIONSSTRINGEXTPROC)(void);
typedef BOOL(WINAPI* PFNWGLSWAPINTERVALEXTPROC)(int);
typedef int (WINAPI* PFNWGLGETSWAPINTERVALEXTPROC) (void);
#define WGL_CONTEXT_MAJOR_VERSION_ARB 0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB 0X2092
#define WGL_CONTEXT_FLAGS_ARB 0X2094
#define WGL_CONTEXT_COREPROFILE_BIT_ARB 0x00000001
#define WGL_CONTEXT_PROFILE_MASK_ARB 0x9126

namespace Engine
{
	float Window::s_Width = 0;
	float Window::s_Height = 0;

	bool Window::has_close_request() const
	{
		return CloseRequest;
	}

	unsigned int Window::get_width() const
	{
		return Width;
	}

	unsigned int Window::get_height() const
	{
		return Height;
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

	float Window::get_window_width()
	{
		return s_Width;
	}

	float Window::get_window_height()
	{
		return s_Height;
	}

	Window::Window(const WindowCreateDesc& desc,Application* listenerApplication)
	{
		constexpr wchar_t WINDOW_CLASS_NAME[] = L"Win32Window";

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

		/*
		* Get pixel desc for opengl context
		*/
		HDC windowDeviceContext = GetDC(windowHandle);
		PIXELFORMATDESCRIPTOR pfd = { sizeof(pfd),1 };
		pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pfd.dwFlags = PFD_DRAW_TO_WINDOW | LPD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.nVersion = 1;
		pfd.cColorBits = 32;
		pfd.cAlphaBits = 8;
		pfd.cDepthBits = 24;
		pfd.cStencilBits = 8;
		pfd.iLayerType = PFD_MAIN_PLANE;

		const int pixelFormatIndex = ChoosePixelFormat(windowDeviceContext, &pfd);
		ASSERT(pixelFormatIndex != 0, "Win32Window", "Invalid pixel format");

		SetPixelFormat(windowDeviceContext,pixelFormatIndex, &pfd);

		/*
		* Create dummy opengl context 3.1
		*/
		HGLRC tempContext = wglCreateContext(windowDeviceContext);
		ASSERT(tempContext != NULL, "Win32Window", "Dummy opengl context creation failed!");

		wglMakeCurrent(windowDeviceContext, tempContext);

		/*
		* Create glad opengl context
		*/
		PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = NULL;
		wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
		ASSERT(wglCreateContextAttribsARB != NULL, "Win32Window", "Wgl create context attrib method couldnt found!");

		constexpr int attribList[] = {
			WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
			WGL_CONTEXT_MINOR_VERSION_ARB, 5,
			WGL_CONTEXT_FLAGS_ARB, 0,
			WGL_CONTEXT_PROFILE_MASK_ARB,
			WGL_CONTEXT_COREPROFILE_BIT_ARB, 0,
		};

		HGLRC gladContext = wglCreateContextAttribsARB(windowDeviceContext, NULL, attribList);
		
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(tempContext);

		wglMakeCurrent(windowDeviceContext, gladContext);

		ASSERT(gladLoadGL() != 0, "Win32Window", "Glad intilization failed!");
		MESSAGE("Win32Window", "Glad version: %s", (const char*)glGetString(GL_VERSION));

		/*
		* Setup debug context if this is a debug build
		*/
#ifdef _DEBUG
		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(
			[](GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
			{
				MESSAGE("OpenGL", "%s", message);
			}
		, nullptr);
#endif

		/*
		* Initialize
		*/
		CloseRequest = false;
		ListenerApplication = listenerApplication;
		WindowHandle = windowHandle;
		WindowDeviceContext = windowDeviceContext;
		WindowGLContext = gladContext;
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
				userWindow->_broadcast_event(new WindowClosedEvent());
				break;
			}
			case WM_MOVE:
			{
				Window* userWindow = get_user_window_data(hwnd);
				userWindow->_broadcast_event(new WindowMovedEvent(LOWORD(lParam), HIWORD(lParam)));
				break;
			}
			case WM_SIZE:
			{
				Window* userWindow = get_user_window_data(hwnd);
				userWindow->_broadcast_event(new WindowResizedEvent(LOWORD(lParam), HIWORD(lParam)));
				break;
			}
			case WM_KEYDOWN:
			{
				Window* userWindow = get_user_window_data(hwnd);
				userWindow->_broadcast_event(new KeyboardKeyDownEvent(wParam));
				break;
			}
			case WM_KEYUP:
			{
				Window* userWindow = get_user_window_data(hwnd);
				userWindow->_broadcast_event(new KeyboardKeyUpEvent(wParam));
				break;
			}
			case WM_RBUTTONDOWN:
			{
				Window* userWindow = get_user_window_data(hwnd);
				userWindow->_broadcast_event(new MouseButtonDownEvent(MOUSE_BUTTON_1));
				break;
			}
			case WM_RBUTTONUP:
			{
				Window* userWindow = get_user_window_data(hwnd);
				userWindow->_broadcast_event(new MouseButtonUpEvent(MOUSE_BUTTON_1));
				break;
			}
			case WM_LBUTTONDOWN:
			{
				Window* userWindow = get_user_window_data(hwnd);
				userWindow->_broadcast_event(new MouseButtonDownEvent(MOUSE_BUTTON_2));
				break;
			}
			case WM_LBUTTONUP:
			{
				Window* userWindow = get_user_window_data(hwnd);
				userWindow->_broadcast_event(new MouseButtonUpEvent(MOUSE_BUTTON_2));
				break;
			}
			case WM_MOUSEMOVE:
			{
				Window* userWindow = get_user_window_data(hwnd);
				userWindow->_broadcast_event(new MouseMovedEvent(LOWORD(lParam), HIWORD(lParam)));
				break;
			}
		}

		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	void Window::_broadcast_event(WindowEvent* event)
	{
		 const WindowEventType type = event->get_event_type();
		 switch (type)
		 {
			 case Engine::WindowEventType::WindowClosed:
			 {
				 CloseRequest = true;
				 break;
			 }
			 case Engine::WindowEventType::WindowResized:
			 {
				 const WindowResizedEvent* eventData = (const WindowResizedEvent*)event;

				 Width = eventData->get_width();
				 Height = eventData->get_height();
				 s_Width = Width;
				 s_Height = Height;
				 break;
			 }
			 case Engine::WindowEventType::WindowMoved:
			 {
				 const WindowMovedEvent* eventData = (const WindowMovedEvent*)event;

				 PositionX = eventData->get_position_x();
				 PositionY = eventData->get_position_y();
				 break;
			 }
			 case Engine::WindowEventType::KeyDown:
				 break;
			 case Engine::WindowEventType::KeyUp:
				 break;
			 case Engine::WindowEventType::MouseButtonDown:
				 break;
			 case Engine::WindowEventType::MouseButtonUp:
				 break;
			 case Engine::WindowEventType::MouseMoved:
				 break;
			 default:
				 break;
		 }

		 /*
		 * Dispatch the event to the listener application
		 */
		 ListenerApplication->dispatch_event(event);
	}
}