#ifndef CSHADER_PROGRAM_H
#define CSHADER_PROGRAM_H

#include "CShader.h"

class ShaderProgram
{
    public:
        ShaderProgram();
        ~ShaderProgram();

        void CreateProgram();
        void DeleteProgram();

        bool AddShader(Shader* shader);
        bool LinkProgram();

        void PrintLog();

        void UseProgram();
        void DisUseProgram();

        GLuint GetID()
        {
            return programID;
        }

    private:

        GLuint programID;

        bool linked;
};

#endif
