#pragma once
#include <Engine/Core/Symbols.h>

namespace Engine
{
	/// <summary>
	/// Returned result data after loading a texture
	/// </summary>
	struct ENGINE_API TextureLoadResult
	{
		unsigned int Width;
		unsigned int Height;
		unsigned int Format;
		unsigned int InternalFormat;
		const void* DataPtr;
	};
}