#include "TextureLoader.h"
#include <STBI/stb_image.h>
#include <Engine/Message/Message.h>
#include <GLAD/glad.h>

namespace Engine
{
	void TextureLoader::load_from_path(const String& path, TextureLoadResult& result)
	{
        int widthOut = 0;
        int heightOut = 0;
        int channelsOut = 0;

        unsigned char* data = stbi_load(*path, &widthOut, &heightOut, &channelsOut, 0);

        if (data == nullptr)
        {
            ASSERT("TextureLoader", "Image loading failed with logs ->  %s", stbi_failure_reason());
            result.DataPtr = nullptr;
            return;
        }

        result.Width = widthOut;
        result.Height = heightOut;
        result.Format = channelsOut == 4 ? GL_RGBA : GL_RGB;
        result.InternalFormat = channelsOut == 4 ? GL_RGBA8 : GL_RGB8;
        result.DataPtr = data;

	}
}