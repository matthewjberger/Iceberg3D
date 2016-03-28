#ifndef VBO_H
#define VBO_H

#include "GlobalIncludes.h"

// Vertex Buffer Object class
class VBO
{
    public:

        VBO();
        ~VBO();

        // Creates buffer objects
        void create(GLint size = 0);

        // Destroys buffer object
        void free();

        // Binds as current buffer
        void bind(GLuint bufferType = GL_ARRAY_BUFFER);

        // Unbinds as current buffer
        void unbind();

        // Adds data
        void add_data( void* newData, GLuint dataSize);

        // Uploads data
        void upload_data(GLenum drawingHint = GL_STATIC_DRAW);

    private:

        // The buffer
        GLuint buffer_;

        // Buffer type
        GLuint type_;

        // Expandable data vector
        std::vector<GLbyte> data_;
};

#endif
