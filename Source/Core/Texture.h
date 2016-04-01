#ifndef TEXTURE_H
#define TEXTURE_H

#include "GlobalIncludes.h"
#include <string>

class Texture
{
public:

    Texture( GLenum type = GL_TEXTURE_2D);
    ~Texture();

    bool load(const std::string& path, bool genMipMaps = false, GLenum target = GL_TEXTURE_2D);
    bool create_from_surface(SDL_Surface* surface, bool genMipMaps = false, GLenum target = GL_TEXTURE_2D);
    void bind(int textureUnit = 0) const;
    void free() const;

    void set_sampler_parameter(GLenum parameter, GLenum value) const;
    void set_filtering(int magnification, int minification);
    void set_wrap() const;

    int minification() const;
    int magnification() const;
    std::string path() const;

private:
    int width_, height_, bpp_;
    GLuint textureID_;
    GLuint sampler_;

    bool mipMapsGenerated_;

    int minification_, magnification_;

    std::string path_;

    GLenum type_;
};
#endif

