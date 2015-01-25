#pragma once

#include "Globals.h"

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
        void AddData( void* data, GLuint dataSize);

        // Uploads data
        void UploadData(GLenum drawingHint);


    private:

        // The buffer
        GLuint mBuffer;

        // Buffer type
        GLuint mType;

        // Expandable data vector
        vector<GLbyte> mData;
};
