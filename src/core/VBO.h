#ifndef __VBO_H
#define __VBO_H

#include "GlobalIncludes.h"

// Vertex Buffer Object class
class VBO
{
    public:

        VBO();
        ~VBO();

        // Creates buffer objects
        void Create(GLint size = 0);

        // Destroys buffer object
        void Free();

        // Binds as current buffer
        void Bind(GLuint bufferType = GL_ARRAY_BUFFER);

        // Unbinds as current buffer
        void Unbind();

        // Adds data
        void AddData( void* newData, GLuint dataSize);

        // Uploads data
        void UploadData(GLenum drawingHint = GL_STATIC_DRAW);

    private:

        // The buffer
        GLuint buffer;

        // Buffer type
        GLuint type;

        // Expandable data vector
        std::vector<GLbyte> data;
};

#endif
