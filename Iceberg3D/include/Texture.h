#ifndef TEXTURE_H
#define TEXTURE_H

#include "GlobalIncludes.h"

namespace iceberg
{
    class ICEBERGAPI Texture
    {
    public:

        Texture(aiTextureType type = aiTextureType_DIFFUSE, GLenum bindTarget = GL_TEXTURE_2D);
        ~Texture();

        bool load(const std::string& path, GLenum target = GL_TEXTURE_2D);
        void create_from_data(int width, int height, const unsigned char* data, GLenum pixelFormat, GLenum target = GL_TEXTURE_2D);
        void bind(int textureUnit = 0) const;
        void unbind(int textureUnit = 0) const;

        void set_wrap() const;
        GLuint id() const;

        std::string path() const;
        aiTextureType type() const;

        glm::vec2 dimensions() const;

    private:

        void free() const;

        int width_, height_, channels_;
        GLuint textureID_;

        std::string path_;
        aiTextureType type_;

        GLenum bindTarget_;
    };
}
#endif