#pragma once
#include <Engine/Core/Symbols.h>

namespace Engine
{
	/// <summary>
	/// Supported window event types
	/// </summary>
	enum class ENGINE_API WindowEventType
	{
		WindowClosed,
		WindowResized,
		WindowMoved,
		KeyDown,
		KeyUp,
		MouseButtonDown,
		MouseButtonUp,
		MouseMoved,
	};
}