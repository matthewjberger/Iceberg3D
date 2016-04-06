#ifndef SHADER_H
#define SHADER_H

#include "GlobalIncludes.h"

class Shader
{
public:

    Shader();
    ~Shader();

    // Loads shader from file
    bool load(std::string path, GLuint shaderType);

    // Deletes shader
    void delete_shader();

    // Print log
    void print_log();

    // Loaded if shader was compiled successfully
    bool loaded();

    // Returns ID
    GLuint id();

private:

    // Shader ID
    GLuint id_;

    // Shader type
    GLuint type_;

    // Load success flag
    bool loaded_;
};

#endif

