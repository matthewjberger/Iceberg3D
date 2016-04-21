#include "ShaderProgram.h"
#include "Game.h"
using namespace std;
using namespace glm;

ShaderProgram::ShaderProgram()
{
    programID_ = 0;
    linked_ = false;
}

ShaderProgram::~ShaderProgram()
{
    delete_program();
}

void ShaderProgram::delete_program()
{
    if (linked_)
    {
        linked_ = false;
        glDeleteProgram(programID_);
    }
}

void ShaderProgram::create_program()
{
    programID_ = glCreateProgram();
}

bool ShaderProgram::add_shader_from_file(const string& path, GLuint shaderType) const
{
    unique_ptr<Shader> newShader = make_unique<Shader>();
    newShader->load(path, shaderType);
    add_shader(newShader.get());

    return true;
}

bool ShaderProgram::add_shader_from_source(const string& shaderSource, GLuint shaderType) const
{
    unique_ptr<Shader> newShader = make_unique<Shader>();
    newShader->create_from_string(shaderSource, shaderType);
    add_shader(newShader.get());

    return true;
}

bool ShaderProgram::add_shader(Shader* shader) const
{
    if (!shader->loaded())
    {
        Game::handle_error("Tried to attach shader that wasn't loaded!");
        return false;
    }

    glAttachShader(programID_, shader->id());

    return true;
}

bool ShaderProgram::link_program()
{
    GLint success = GL_TRUE;

    glLinkProgram(programID_);
    glGetProgramiv(programID_, GL_COMPILE_STATUS, &success);

    if (success != GL_TRUE)
    {
        string errorMessage = "Couldn't link program " + to_string(programID_) + "\n";
        Game::handle_error(errorMessage.c_str());
        print_log();
        glDeleteProgram(programID_);
        programID_ = 0;
        return false;
    }

    linked_ = true;

    return true;
}

string ShaderProgram::print_log() const
{
    int infoLogLength = 0;
    int maxLength = infoLogLength;
    string log = "No program log information was available.";

    glGetProgramiv(programID_, GL_INFO_LOG_LENGTH, &maxLength);

    char* infoLog = new char[maxLength];

    glGetProgramInfoLog(programID_, maxLength, &infoLogLength, infoLog);
    if (infoLogLength > 0)
    {
        log = infoLog;
        log += "\n";
    }

    delete[] infoLog;

    return log;
}

void ShaderProgram::use() const
{
    if (linked_)
    {
        glUseProgram(programID_);
    }
}

void ShaderProgram::disuse() const
{
    if (linked_)
    {
        glUseProgram(0);
    }
}

// Set floats
void ShaderProgram::set_uniform(const string& name, float* values, int count) const
{
    int location = glGetUniformLocation(programID_, name.c_str());
    glUniform1fv(location, count, values);
}

void ShaderProgram::set_uniform(const string& name, const float value) const
{
    int location = glGetUniformLocation(programID_, name.c_str());
    glUniform1fv(location, 1, &value);
}

// Set vectors

// vec2
void ShaderProgram::set_uniform(const string& name, vec2* vectors, int count) const
{
    int location = glGetUniformLocation(programID_, name.c_str());
    glUniform2fv(location, count, (GLfloat*)vectors); // cast vectors to GLfloat arrays
}

void ShaderProgram::set_uniform(const string& name, const vec2& vector) const
{
    int location = glGetUniformLocation(programID_, name.c_str());
    glUniform2fv(location, 1, (GLfloat*)&vector); // cast vectors to GLfloat arrays
}

// vec3
void ShaderProgram::set_uniform(const string& name, vec3* vectors, int count) const
{
    int location = glGetUniformLocation(programID_, name.c_str());
    glUniform3fv(location, count, (GLfloat*)vectors); // cast vectors to GLfloat arrays
}

void ShaderProgram::set_uniform(const string& name, const vec3& vector) const
{
    int location = glGetUniformLocation(programID_, name.c_str());
    glUniform3fv(location, 1, (GLfloat*)&vector); // cast vectors to GLfloat arrays
}

// vec4
void ShaderProgram::set_uniform(const string& name, vec4* vectors, int count) const
{
    int location = glGetUniformLocation(programID_, name.c_str());
    glUniform4fv(location, count, (GLfloat*)vectors); // cast vectors to GLfloat arrays
}

void ShaderProgram::set_uniform(const string& name, const vec4& vector) const
{
    int location = glGetUniformLocation(programID_, name.c_str());
    glUniform4fv(location, 1, (GLfloat*)&vector); // cast vectors to GLfloat arrays
}

// Set 4x4 matrices
void ShaderProgram::set_uniform(const string& name, mat4* matrices, int count) const
{
    int location = glGetUniformLocation(programID_, name.c_str());
    glUniformMatrix4fv(location, count, GL_FALSE, (GLfloat*)matrices);
}

void ShaderProgram::set_uniform(const string& name, const mat4& matrix) const
{
    int location = glGetUniformLocation(programID_, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, (GLfloat*)&matrix);
}

// Set integers
void ShaderProgram::set_uniform(const string& name, int* values, int count) const
{
    int location = glGetUniformLocation(programID_, name.c_str());
    glUniform1iv(location, count, values);
}

void ShaderProgram::set_uniform(const string& name, const int& value) const
{
    int location = glGetUniformLocation(programID_, name.c_str());
    glUniform1i(location, value);
}

GLint ShaderProgram::get_attribute_location(const string& attributeName) const
{
    GLint location = glGetAttribLocation(programID_, const_cast<const char*>(attributeName.c_str()));
    return location;
}

GLint ShaderProgram::get_uniform_location(const string& uniformName) const
{
    GLint location = glGetUniformLocation(programID_, const_cast<const char*>(uniformName.c_str()));
    return location;
}

GLuint ShaderProgram::id() const
{
    return programID_;
}

