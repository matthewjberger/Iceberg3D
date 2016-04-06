#ifndef TEXTURE_H
#define TEXTURE_H

#include "GlobalIncludes.h"

class Texture
{
public:

    Texture(aiTextureType type = aiTextureType_DIFFUSE, GLenum bindTarget = GL_TEXTURE_2D);
    ~Texture();

    bool load(const std::string& path, bool genMipMaps = false, GLenum target = GL_TEXTURE_2D);
    bool create_from_surface(SDL_Surface* surface, bool genMipMaps = false, GLenum target = GL_TEXTURE_2D);
    void bind(int textureUnit = 0) const;
    void unbind(int textureUnit = 0) const;

    void set_sampler_parameter(GLenum parameter, GLenum value) const;
    void set_filtering(int magnification, int minification);
    void set_wrap() const;

    int minification() const;
    int magnification() const;
    std::string path() const;
    aiTextureType type() const;
    GLuint sampler() const;

private:

    void free() const;

    int width_, height_;
    GLuint textureID_;
    GLuint sampler_;

    bool mipMapsGenerated_;

    int minification_, magnification_;

    std::string path_;
    aiTextureType type_;

    GLenum bindTarget_;
};
#endif
