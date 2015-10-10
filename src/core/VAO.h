#ifndef __VAO_H
#define __VAO_H

#include "GlobalIncludes.h"

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
        void DisableAttribute(GLint location = 0);
        void ConfigureAttribute(GLuint index, GLint size, GLenum type,
                                GLboolean normalized, GLsizei stride, const GLvoid* pointer);

    private:

        GLuint vertexArray;
};

#endif
