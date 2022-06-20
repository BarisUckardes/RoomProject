#pragma once
#include <Engine/Window/WindowEvent.h>

namespace Engine
{
	/// <summary>
	/// Represents a base window mouse button events such as ButtonDown and ButtonUP
	/// </summary>
	class ENGINE_API WindowMouseButtonEvent : public WindowEvent
	{
	public:
		FORCEINLINE unsigned int get_related_button() const;
	protected:
		WindowMouseButtonEvent(const unsigned int relatedButton);
		~WindowMouseButtonEvent() = default;
	private:
		unsigned int RelatedButton;
	};


}