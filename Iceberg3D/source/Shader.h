#ifndef SHADER_H
#define SHADER_H

#include "GlobalIncludes.h"

namespace iceberg
{
    class ICEBERGAPI Shader
    {
    public:
        Shader();
        ~Shader();

        bool load(const std::string &path, GLuint shaderType);
        bool create_from_string(const std::string &shaderSource, GLuint shaderType);
        void delete_shader();
        std::string print_log() const;
        bool loaded() const;
        GLuint id() const;

    private:
        GLuint id_;
        GLuint type_;
        bool loaded_;
    };
}
#endif