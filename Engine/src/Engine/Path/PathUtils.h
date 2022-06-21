#pragma once
#include <Engine/Containers/String.h>

namespace Engine
{
	class ENGINE_API PathUtils
	{
	public:
		PathUtils() = delete;
		~PathUtils() = delete;

		FORCEINLINE static String get_relative_path(const String& path);
	};
}