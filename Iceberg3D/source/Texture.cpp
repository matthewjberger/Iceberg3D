#include "GlobalIncludes.h"
#include "Texture.h"
#include "Game.h"

using namespace iceberg;

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture::Texture(aiTextureType type, GLenum bindTarget)
{
    // Initialize variables
    width_ = 0;
    height_ = 0;
    channels_ = 0;

    textureID_ = 0;
    bindTarget_ = bindTarget;

    type_ = type;

    glGenTextures(1, &textureID_);

}

Texture::~Texture()
{
    // Free the texture
    free();
}

void Texture::free() const
{
    // Delete the texture
    glDeleteTextures(1, &textureID_);
}

void Texture::bind(int textureUnit) const
{
    // Bind as current texture for rendering
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(bindTarget_, textureID_);
}

void Texture::unbind(int textureUnit) const
{
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(bindTarget_, 0);
}

void Texture::create_from_data(int width, int height, const unsigned char* data, GLenum pixelFormat, GLenum target)
{
    width_ = width;
    height_ = height;

    bind();
    glTexImage2D(target, 0, pixelFormat, width_, height_, 0, pixelFormat, GL_UNSIGNED_BYTE, data);
    glTexParameteri(bindTarget_, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(bindTarget_, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(bindTarget_, GL_TEXTURE_WRAP_R, GL_REPEAT);
    glTexParameteri(bindTarget_, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(bindTarget_, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);
    unbind();
}

bool Texture::load(const std::string& path, GLenum target)
{
    if(bindTarget_ == GL_TEXTURE_CUBE_MAP)
    {
        stbi_set_flip_vertically_on_load(false);
    }
    else
    {
        stbi_set_flip_vertically_on_load(true);
    }

    path_ = path;

    int width, height;
    unsigned char* image = stbi_load(path.c_str(), &width, &height, &channels_, 0);
    if (!image)
    {
        std::string errorMessage = "Couldn't load image " + path;
        Game::handle_error(errorMessage);
        return false;
    }

    GLenum pixelFormat = GL_RGB;
    switch (channels_)
    {
        case 1: pixelFormat = GL_ALPHA;     break;
        case 2: pixelFormat = GL_LUMINANCE; break;
        case 3: pixelFormat = GL_RGB;       break;
        case 4: pixelFormat = GL_RGBA;      break;
    }

    create_from_data(width, height, image, pixelFormat, target);

    stbi_image_free(image);
    stbi_set_flip_vertically_on_load(false);

    return true;
}

std::string Texture::path() const
{
    return path_;
}

aiTextureType Texture::type() const
{
    return type_;
}

void Texture::set_wrap() const
{
    bind();
    glTexParameteri(bindTarget_, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(bindTarget_, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(bindTarget_, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    unbind();
}

GLuint Texture::id() const
{
    return textureID_;
}