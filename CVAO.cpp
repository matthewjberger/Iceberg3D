#include "CVAO.h"

VAO::VAO()
{
    mVertexArray = 0;
}

VAO::~VAO()
{
    Free();
}

void VAO::Create()
{
    glGenVertexArrays(1, &mVertexArray);
}

void VAO::Free()
{
    glDeleteVertexArrays(1, &mVertexArray);
}

void VAO::Bind()
{
    glBindVertexArray(mVertexArray);
}

void VAO::Unbind()
{
    glBindVertexArray(0);
}

void VAO::EnableAttribute(GLint location)
{
    glEnableVertexAttribArray(location);
}

void VAO::ConfigureAttribute(GLuint index, GLint size, GLenum type, 
                                GLboolean normalized, GLsizei stride, const GLvoid* pointer)
{
    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}
