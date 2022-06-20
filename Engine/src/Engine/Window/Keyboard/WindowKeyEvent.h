#pragma once
#include <Engine/Window/WindowEvent.h>

namespace Engine
{
	/// <summary>
	/// Base window event class for all keyboard key related events
	/// </summary>
	class ENGINE_API WindowKeyEvent : public WindowEvent
	{
	public:
		FORCEINLINE unsigned int get_related_key() const;

	protected:
		WindowKeyEvent(const unsigned int key);
		~WindowKeyEvent() = default;
	private:
		unsigned int RelatedKey;
	};


}