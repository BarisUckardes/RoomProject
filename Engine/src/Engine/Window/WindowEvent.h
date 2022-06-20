#pragma once
#include <Engine/Containers/String.h>
#include <Engine/Window/WindowEventType.h>

namespace Engine
{
	/// <summary>
	/// Base window event class for window event authoring
	/// </summary>
	class ENGINE_API WindowEvent
	{
	public:
		WindowEvent() : Handled(false) {}
		~WindowEvent() = default;

		FORCEINLINE bool is_handled() const;

		/// <summary>
		/// Marks this event as handled, helps whether the event is distinguished as marked or not.So we can ignore it.(Should help with UI)
		/// </summary>
		void mark_handled();

		FORCEINLINE virtual WindowEventType get_event_type() const = 0;
		FORCEINLINE virtual String get_event_message() const = 0;
	private:
		bool Handled;
	};
}