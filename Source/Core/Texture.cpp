#include "GlobalIncludes.h"
#include "Texture.h"
using namespace std;

Texture::Texture()
{
    // Initialize variables
    width_ = 0;
    height_ = 0;
    bpp_ = 0;

    textureID_ = 0;
    sampler_ = 0;

    mipMapsGenerated_ = false;

    minification_ = 0;
    magnification_ = 0;
}

Texture::~Texture()
{
    // Free the texture
    free();
}

void Texture::free() const
{
    // Delete the sampler
    glDeleteSamplers(1, &sampler_);

    // Delete the texture
    glDeleteTextures(1, &textureID_);
}

void Texture::set_filtering(int magnification, int minification)
{
    // Set magnification filter
    glSamplerParameteri(sampler_, GL_TEXTURE_MAG_FILTER, magnification);

    // Set minification filter
    glSamplerParameteri(sampler_, GL_TEXTURE_MIN_FILTER, minification);

    // Set magnification member variable
    magnification_ = magnification;

    // Set minification member variable
    minification_ = minification;
}

void Texture::bind(int textureUnit) const
{
    // Bind as current texture for rendering
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(GL_TEXTURE_2D, textureID_);
    glBindSampler(textureUnit, sampler_);
}

bool Texture::create_from_surface(SDL_Surface* surface, bool genMipMaps)
{
    // TODO: Add failure conditions for this

    // Generate the texture and bind it
    glGenTextures(1, &textureID_);
    glBindTexture(GL_TEXTURE_2D, textureID_);

    // Set pixel mode
    int pixelMode = GL_RGB;

    // Check for alpha component and set pixel mode appropriately
    if (surface->format->BytesPerPixel == 4)
    {
        pixelMode = GL_RGBA;
    }

    // Send data to gpu
    glTexImage2D(GL_TEXTURE_2D, 0, pixelMode, surface->w, surface->h, 0, pixelMode, GL_UNSIGNED_BYTE, surface->pixels);

    // Generate mipmaps if requested
    if (genMipMaps)
    {
        glGenerateMipmap(GL_TEXTURE_2D);

        // Set mipmap generation flag
        mipMapsGenerated_ = true;
    }

    // Generate samplers
    glGenSamplers(1, &sampler_);

    // Set filtering
    set_filtering(GL_LINEAR, GL_LINEAR);

    // Parameters
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    return true;
}

bool Texture::load(const string& path, bool genMipMaps)
{
    // Set path
    path_ = path;

    // The texture id
    textureID_ = 0;

    // Load the image
    SDL_Surface* textureSurface = IMG_Load(path.c_str());

    // Check for errors
    if (textureSurface == nullptr)
    {
        printf("Couldn't load image %s./nIMG_Error: %s", path.c_str(), IMG_GetError());
        return false;
    }

    // Create the texture from an SDL Surface
    if (!create_from_surface(textureSurface, genMipMaps))
    {
        return false;
    }

    // Get rid of the temporary surface
    SDL_FreeSurface(textureSurface);

    return true;
}

string Texture::path() const
{
    return path_;
}

int Texture::minification() const
{
    return minification_;
}

int Texture::magnification() const
{
    return magnification_;
}

void Texture::set_sampler_parameter(GLenum parameter, GLenum value) const
{
    glSamplerParameteri(sampler_, parameter, value);
}

void Texture::set_wrap() const
{
    glBindSampler(0, sampler_);
    glSamplerParameteri(sampler_, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glSamplerParameteri(sampler_, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

