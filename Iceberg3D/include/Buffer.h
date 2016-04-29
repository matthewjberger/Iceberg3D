#ifndef VBO_H
#define VBO_H

#include "GlobalIncludes.h"

namespace iceberg
{
    class ICEBERGAPI Buffer
    {
    public:

        Buffer(GLint size = 0);
        ~Buffer();

        void bind(GLuint bufferType = GL_ARRAY_BUFFER);
        void unbind() const;
        void add_data(void* newData, GLuint dataSize);
        void upload_data(GLenum drawingHint = GL_STATIC_DRAW);
        bool update_buffer(const GLvoid* data, GLsizeiptr size, GLintptr offset) const;

    private:

        void free();
        void create(GLint size);
        GLuint buffer_;
        GLuint type_;
        std::vector<GLbyte> data_;
        bool uploaded_;
    };
}
#endif