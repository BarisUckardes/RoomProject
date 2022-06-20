#include "ApplicationSession.h"


namespace Engine
{
	ApplicationSession::ApplicationSession(Window* window)
	{
		AppWindow = window;
	}
	ApplicationSession::~ApplicationSession()
	{
	}
	Window* ApplicationSession::get_app_window() const
	{
		return AppWindow;
	}
}