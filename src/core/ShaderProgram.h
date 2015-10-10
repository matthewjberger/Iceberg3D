#ifndef __SHADER_PROGRAM_H
#define __SHADER_PROGRAM_H

#include "Shader.h"

class ShaderProgram
{
    public:
        ShaderProgram();
        ~ShaderProgram();

        void CreateProgram();
        void DeleteProgram();

        bool AddShader(Shader* shader);
        bool AddShaderFromFile(std::string path, GLuint shaderType);
        bool LinkProgram();

        void PrintLog();

        void UseProgram();
        void DisUseProgram();

        // Set floats
        void SetUniform(std::string name, float* values, int count=1);
        void SetUniform(std::string name, const float value);

        // Set vectors
        void SetUniform(std::string name, glm::vec2* vectors, int count=1);
        void SetUniform(std::string name, const glm::vec2 &vector);

        void SetUniform(std::string name, glm::vec3* vectors, int count=1);
        void SetUniform(std::string name, const glm::vec3 &vector);

        void SetUniform(std::string name, glm::vec4* vectors, int count=1);
        void SetUniform(std::string name, const glm::vec4 &vector);

        // Set 4x4 matrices
        void SetUniform(std::string name, glm::mat4* matrices, int count=1);
        void SetUniform(std::string name, const glm::mat4 &matrix);

        // Set integers
        void SetUniform(std::string name, int* values, int count=1);
        void SetUniform(std::string name, const int &value);

        // Get attribute locations
        GLint GetAttributeLocation(std::string attributeName);

        // Get uniform locations
        GLint GetUniformLocation(std::string uniformName);

        GLuint GetID();

    private:

        GLuint programID;

        bool linked;
};

#endif
