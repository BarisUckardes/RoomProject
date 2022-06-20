#include "WindowKeyEvent.h"

namespace Engine
{
	unsigned int WindowKeyEvent::get_related_key() const
	{
		return RelatedKey;
	}
	WindowKeyEvent::WindowKeyEvent(const unsigned int key)
	{
		RelatedKey = key;
	}
}