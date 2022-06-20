#include "WindowMouseButtonEvent.h"

namespace Engine
{
	unsigned int WindowMouseButtonEvent::get_related_button() const
	{
		return RelatedButton;
	}
	WindowMouseButtonEvent::WindowMouseButtonEvent(const unsigned int relatedButton)
	{
		RelatedButton = relatedButton;
	}
}