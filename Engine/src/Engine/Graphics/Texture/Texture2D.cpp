#include "Texture2D.h"
#include <Engine/Graphics/Texture/TextureLoader.h>

namespace Engine
{
    Texture2D::Texture2D(const unsigned int width, const unsigned int height, const unsigned int format,const unsigned int internalFormat)
    {
        /*
        * Generate a gl texture
        */
        glGenTextures(1, &TextureHandle);

        /*
        * Allocate texture data on gpu
        */
        glBindTexture(GL_TEXTURE_2D, TextureHandle);
        glTexImage2D(GL_TEXTURE_2D, 1, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, nullptr);
        glBindTexture(GL_TEXTURE_2D, 0);

        /*
        * Initialize this object
        */
        Width = width;
        Height = height;
        Format = format;
    }
    Texture2D::Texture2D(const String& path)
    {
        /*
        * Load the texture
        */
        TextureLoadResult loadResult = {};

        TextureLoader::load_from_path(path, loadResult);

        /*
        * Generate texture
        */
        glGenTextures(1, &TextureHandle);

        /*
        * Allocate texture data on gpu
        */
        glBindTexture(GL_TEXTURE_2D, TextureHandle);
        glTexImage2D(GL_TEXTURE_2D, 1, loadResult.InternalFormat, loadResult.Width, loadResult.Height, 0, loadResult.Format, GL_UNSIGNED_BYTE, nullptr);
        glBindTexture(GL_TEXTURE_2D, 0);

        /*
        * Initialize this object
        */
        Width = loadResult.Width;
        Height = loadResult.Height;
        Format = loadResult.Format;
    }
    Texture2D::~Texture2D()
    {
        if (TextureHandle != 0)
            glDeleteTextures(1,&TextureHandle);
        TextureHandle = 0;
    }
    unsigned int Texture2D::get_width() const
    {
        return Width;
    }
    unsigned int Texture2D::get_height() const
    {
        return Height;
    }
    unsigned int Texture2D::get_texture_handle() const
    {
        return TextureHandle;
    }
    void Texture2D::update_texture(const void* data, const unsigned long size)
    {
        glBindTexture(GL_TEXTURE_2D, TextureHandle);
        glTextureSubImage2D(GL_TEXTURE_2D, 1, 0, 0, Width, Height, Format, GL_UNSIGNED_BYTE, data);
        glBindTexture(GL_TEXTURE_2D, TextureHandle);
    }
}