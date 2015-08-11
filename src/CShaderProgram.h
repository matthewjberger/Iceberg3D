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

        // Set floats
        void SetUniform(string name, float* values, int count=1);
        void SetUniform(string name, const float value);

        // Set vectors
        void SetUniform(string name, vec2* vectors, int count=1);
        void SetUniform(string name, const vec2 vector);

        void SetUniform(string name, vec3* vectors, int count=1);
        void SetUniform(string name, const vec3 vector);

        void SetUniform(string name, vec4* vectors, int count=1);
        void SetUniform(string name, const vec4 vector);

        // Set 4x4 matrices
        void SetUniform(string name, mat4* matrices, int count=1);
        void SetUniform(string name, const mat4 matrix);

        // Set integers
        void SetUniform(string name, int* values, int count=1);
        void SetUniform(string name, const int value);
        

        GLuint GetID()
        {
            return mProgramID;
        }

    private:

        GLuint mProgramID;

        bool linked;
};

#endif
