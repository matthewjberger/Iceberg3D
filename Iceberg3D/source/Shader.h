#ifndef SHADER_H
#define SHADER_H

#include "GlobalIncludes.h"

class Shader
{
public:

    Shader();
    ~Shader();

    bool load(std::string path, GLuint shaderType);
    void delete_shader();
    std::string print_log() const;
    bool loaded() const;
    GLuint id() const;

private:

    GLuint id_;
    GLuint type_;
    bool loaded_;
};

#endif

