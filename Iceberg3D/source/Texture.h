#ifndef TEXTURE_H
#define TEXTURE_H

#include "GlobalIncludes.h"

class Texture
{
public:

    Texture(aiTextureType type = aiTextureType_DIFFUSE, GLenum bindTarget = GL_TEXTURE_2D);
    ~Texture();

    bool load(const std::string& path, GLenum target = GL_TEXTURE_2D);
    void bind(int textureUnit = 0) const;
    void unbind(int textureUnit = 0) const;

    void set_wrap() const;
    GLuint id() const;

    std::string path() const;
    aiTextureType type() const;

private:

    void free() const;

    int width_, height_, channels_;
    GLuint textureID_;

    std::string path_;
    aiTextureType type_;

    GLenum bindTarget_;
};
#endif
