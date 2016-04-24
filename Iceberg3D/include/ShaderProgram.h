#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include "Shader.h"

namespace iceberg
{
    class ICEBERGAPI ShaderProgram
    {
    public:
        ShaderProgram();
        ~ShaderProgram();

        void create_program();
        void delete_program();

        bool add_shader(Shader* shader) const;
        bool add_shader_from_file(const std::string& path, GLuint shaderType) const;
        bool add_shader_from_source(const std::string& shaderSource, GLuint shaderType) const;

        bool link_program();

        std::string print_log() const;

        void use() const;
        void disuse() const;

        // Set floats
        void set_uniform(const std::string& name, float* values, int count = 1) const;
        void set_uniform(const std::string& name, const float value) const;

        // Set vectors
        void set_uniform(const std::string& name, glm::vec2* vectors, int count = 1) const;
        void set_uniform(const std::string& name, const glm::vec2& vector) const;

        void set_uniform(const std::string& name, glm::vec3* vectors, int count = 1) const;
        void set_uniform(const std::string& name, const glm::vec3& vector) const;

        void set_uniform(const std::string& name, glm::vec4* vectors, int count = 1) const;
        void set_uniform(const std::string& name, const glm::vec4& vector) const;

        // Set 4x4 matrices
        void set_uniform(const std::string& name, glm::mat4* matrices, int count = 1) const;
        void set_uniform(const std::string& name, const glm::mat4& matrix) const;

        // Set integers
        void set_uniform(const std::string& name, int* values, int count = 1) const;
        void set_uniform(const std::string& name, const int& value) const;

        // Get attribute locations
        GLint get_attribute_location(const std::string& attributeName) const;

        // Get uniform locations
        GLint get_uniform_location(const std::string& uniformName) const;

        GLuint id() const;

    private:
        GLuint programID_;

        bool linked_;
    };
}
#endif