#ifndef SHADER_H
#define SHADER_H

#include "GlobalIncludes.h"

class Shader
{
    public:

        Shader();
        ~Shader();

        // Loads shader from file
        bool Load(std::string path, GLuint shaderType);

        // Deletes shader
        void DeleteShader();

        // Print log
        void PrintLog();

        // Loaded if shader was compiled succesfully
        bool IsLoaded();

        // Returns ID
        GLuint GetID();

    private:

        // Shader ID
        GLuint shaderID;

        // Shader type
        GLuint type;

        // Load success flag
        bool loaded;
};

#endif
