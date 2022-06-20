#pragma once
#include <Engine/Core/Symbols.h>
#include <GLAD/glad.h>
#include <Engine/Containers/String.h>

namespace Engine
{
	
	/// <summary>
	/// Represents a 2d texture which created via loading from a path or created as a transient texture
	/// </summary>
	class ENGINE_API Texture2D
	{
	public:
		Texture2D(const unsigned int width, const unsigned int height, const unsigned int format,const unsigned int internalFormat);
		Texture2D(const String& path);
		~Texture2D();

		FORCEINLINE unsigned int get_width() const;
		FORCEINLINE unsigned int get_height() const;
		FORCEINLINE unsigned int get_texture_handle() const;

		void update_texture(const void* data,const unsigned long size);
	private:
		unsigned int Width;
		unsigned int Height;
		unsigned int TextureHandle;
		unsigned int Format;
	};


}