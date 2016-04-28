#include "VAO.h"

using namespace iceberg;

VAO::VAO()
{
    vertexArray = 0;
    create();
}

VAO::~VAO()
{
    free();
}

void VAO::create()
{
    glGenVertexArrays(1, &vertexArray);
}

void VAO::free() const
{
    glDeleteVertexArrays(1, &vertexArray);
}

void VAO::bind() const
{
    glBindVertexArray(vertexArray);
}

void VAO::unbind()
{
    glBindVertexArray(0);
}

void VAO::enable_attribute(GLint location)
{
    glEnableVertexAttribArray(location);
}

void VAO::disable_attribute(GLint location)
{
    glDisableVertexAttribArray(location);
}

void VAO::configure_attribute(GLuint index, GLint size, GLenum type,
                              GLboolean normalized, GLsizei stride, const GLvoid* pointer)
{
    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}

