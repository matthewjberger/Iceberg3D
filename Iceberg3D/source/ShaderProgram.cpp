#include "ShaderProgram.h"
#include "Game.h"
using namespace std;
using namespace glm;

ShaderProgram::ShaderProgram()
{
    // Initialize variables
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
        // Update status
        linked_ = false;

        // Delete the program if linked
        glDeleteProgram(programID_);
    }
}

void ShaderProgram::create_program()
{
    programID_ = glCreateProgram();
}

bool ShaderProgram::add_shader_from_file(const string& path, GLuint shaderType) const
{
    Shader* newShader = new Shader();

    newShader->load(path, shaderType);

    add_shader(newShader);

    newShader->delete_shader();

    delete newShader;

    newShader = nullptr;

    return true;
}

bool ShaderProgram::add_shader(Shader* shader) const
{
    if (!shader->loaded())
    {
        // Print error message
        Game::handle_error("Tried to attach shader that wasn't loaded!");

        // Return status
        return false;
    }

    glAttachShader(programID_, shader->id());

    // Return status
    return true;
}

bool ShaderProgram::link_program()
{
    // Success flag
    GLint success = GL_TRUE;

    // Make the shader Program
    glLinkProgram(programID_);

    // Check if program was created successfully
    glGetProgramiv(programID_, GL_COMPILE_STATUS, &success);

    // If program creation failed
    if (success != GL_TRUE)
    {
        // Print an error message
        string errorMessage = "Couldn't link program " + to_string(programID_) + "\n";
        Game::handle_error(errorMessage.c_str());

        // Print log
        print_log();

        // Delete the program
        glDeleteProgram(programID_);

        // Set program ID to 0
        programID_ = 0;

        // Return status
        return false;
    }

    // Update status
    linked_ = true;

    // Return status
    return true;
}

string ShaderProgram::print_log() const
{
    // Shader program log length
    int infoLogLength = 0;
    int maxLength = infoLogLength;
    string log = "No program log information was available.";

    //Get info string length
    glGetProgramiv(programID_, GL_INFO_LOG_LENGTH, &maxLength);

    //Allocate string
    char* infoLog = new char[maxLength];

    //Get info log
    glGetProgramInfoLog(programID_, maxLength, &infoLogLength, infoLog);
    if (infoLogLength > 0)
    {
        //Print Log
        log = infoLog;
        log += "\n";
    }

    //Deallocate string
    delete[] infoLog;

    return log;
}

void ShaderProgram::use() const
{
    if (linked_)
    {
        // If linked, use program
        glUseProgram(programID_);
    }
}

void ShaderProgram::disuse() const
{
    if (linked_)
    {
        // If linked, use program
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

