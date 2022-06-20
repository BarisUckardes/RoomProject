#pragma once
#include <Engine/Window/WindowEvent.h>

namespace Engine
{
	/// <summary>
	/// Represents a window resized event, contains the new window size properties such as width and height
	/// </summary>
	class ENGINE_API WindowResizedEvent final : public WindowEvent
	{
	public:
		WindowResizedEvent(const unsigned int width, const unsigned height);
		~WindowResizedEvent() = default;

		FORCEINLINE unsigned int get_width() const;
		FORCEINLINE unsigned int get_height() const;

		// Inherited via WindowEvent
		virtual WindowEventType get_event_type() const override;
		virtual String get_event_message() const override;
	private:
		unsigned int Width;
		unsigned int Height;

	};


}