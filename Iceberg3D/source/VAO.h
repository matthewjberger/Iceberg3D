#ifndef VAO_H
#define VAO_H

#include "GlobalIncludes.h"

namespace iceberg
{
    class VAO
    {
    public:

        VAO();
        ~VAO();

        void create();
        void free() const;
        void bind() const;
        static void unbind();
        static void enable_attribute(GLint location = 0);
        static void disable_attribute(GLint location = 0);
        static void configure_attribute(GLuint index, GLint size, GLenum type,
            GLboolean normalized, GLsizei stride, const GLvoid* pointer);

    private:

        GLuint vertexArray;
    };
}
#endif