#pragma once
#include <Engine/Graphics/Texture/TextureLoadResult.h>
#include <Engine/Containers/String.h>

namespace Engine
{
	class ENGINE_API TextureLoader
	{
	public:
		TextureLoader() = delete;
		~TextureLoader() = delete;

		FORCEINLINE static void load_from_path(const String& path, TextureLoadResult& result);
	};
}