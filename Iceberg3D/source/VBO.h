#ifndef VBO_H
#define VBO_H

#include "GlobalIncludes.h"

namespace iceberg
{
    class VBO
    {
    public:

        VBO();
        ~VBO();

        void create(GLint size = 0);
        void free();
        void bind(GLuint bufferType = GL_ARRAY_BUFFER);
        void unbind() const;
        void add_data(void* newData, GLuint dataSize);
        void upload_data(GLenum drawingHint = GL_STATIC_DRAW);

    private:

        GLuint buffer_;
        GLuint type_;
        std::vector<GLbyte> data_;
    };
}
#endif