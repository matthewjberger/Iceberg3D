#pragma once

#include "Globals.h"

class VAO
{
    public:

        VAO();
        ~VAO();

        void Create();
        void Free();
        void Bind();
        void Unbind();
        void EnableAttribute(GLint location = 0);
        void ConfigureAttribute(GLuint index, GLint size, GLenum type, 
                                GLboolean normalized, GLsizei stride, const GLvoid* pointer);

    private:

        GLuint mVertexArray;
};
