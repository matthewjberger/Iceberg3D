#include "VAO.h"

VAO::VAO()
{
    vertexArray = 0;
}

VAO::~VAO()
{
    Free();
}

void VAO::Create()
{
    glGenVertexArrays(1, &vertexArray);
}

void VAO::Free()
{
    glDeleteVertexArrays(1, &vertexArray);
}

void VAO::Bind()
{
    glBindVertexArray(vertexArray);
}

void VAO::Unbind()
{
    glBindVertexArray(0);
}

void VAO::EnableAttribute(GLint location)
{
    glEnableVertexAttribArray(location);
}

void VAO::DisableAttribute(GLint location)
{
    glDisableVertexAttribArray(location);
}

void VAO::ConfigureAttribute(GLuint index, GLint size, GLenum type,
                                GLboolean normalized, GLsizei stride, const GLvoid* pointer)
{
    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}
