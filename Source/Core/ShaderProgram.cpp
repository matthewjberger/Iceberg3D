#include "ShaderProgram.h"
using namespace std;
using namespace glm;

ShaderProgram::ShaderProgram()
{
    // Initialize variables
    programID = 0;
    linked    = false;
}

ShaderProgram::~ShaderProgram()
{
    DeleteProgram();
}

void ShaderProgram::DeleteProgram()
{
    if (linked)
    {
        // Update status
        linked = false;

        // Delete the program if linked
        glDeleteProgram(programID);
    }
}

void ShaderProgram::CreateProgram()
{
    programID = glCreateProgram();
}

bool ShaderProgram::AddShaderFromFile(std::string path, GLuint shaderType)
{
    Shader *newShader = new Shader();

    newShader->Load(path, shaderType);

    AddShader(newShader);

    newShader->DeleteShader();

    delete newShader;

    newShader = NULL;

    return true;
}

bool ShaderProgram::AddShader(Shader* shader)
{
    if (!shader->IsLoaded())
    {
        // Print error message
        printf("Error: Tried to attach shader that wasn't loaded!\n");

        // Return status
        return false;
    }

    glAttachShader(programID, shader->GetID());

    // Return status
    return true;
}

bool ShaderProgram::LinkProgram()
{
    // Success flag
    GLint success = GL_TRUE;

    // Make the shader Program
    glLinkProgram(programID);

    // Check if program was created successfully
    glGetProgramiv(programID, GL_COMPILE_STATUS, &success);

    // If program creation failed
    if (success != GL_TRUE)
    {
        // Print an error message
        printf("Couldn't link program %d\n", programID);

        // Print log
        PrintLog();

        // Delete the program
        glDeleteProgram(programID);

        // Set program ID to 0
        programID = 0;

        // Return status
        return false;
    }

    // Update status
    linked = true;

    // Return status
    return true;
}

void ShaderProgram::PrintLog()
{
    // Shader program log length
    int infoLogLength = 0;
    int maxLength = infoLogLength;

    //Get info string length
    glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);

    //Allocate string
    char* infoLog = new char[maxLength];

    //Get info log
    glGetProgramInfoLog(programID, maxLength, &infoLogLength, infoLog);
    if (infoLogLength > 0)
    {
        //Print Log
        printf("%s\n", infoLog);
    }

    //Deallocate string
    delete[] infoLog;
}

void ShaderProgram::UseProgram()
{
    if (linked)
    {
        // If linked, use program
        glUseProgram(programID);
    }
}

void ShaderProgram::DisUseProgram()
{
    if (linked)
    {
        // If linked, use program
        glUseProgram(0);
    }
}

// Set floats
void ShaderProgram::SetUniform(string name, float* values, int count)
{
    int location = glGetUniformLocation(programID, name.c_str());
    glUniform1fv(location, count, values);
}

void ShaderProgram::SetUniform(string name, const float value)
{
    int location = glGetUniformLocation(programID, name.c_str());
    glUniform1fv(location, 1, &value);
}

// Set vectors

// vec2
void ShaderProgram::SetUniform(string name, vec2* vectors, int count)
{
    int location = glGetUniformLocation(programID, name.c_str());
    glUniform2fv(location, count, (GLfloat*)vectors); // cast vectors to GLfloat arrays
}

void ShaderProgram::SetUniform(string name, const vec2 &vector)
{
    int location = glGetUniformLocation(programID, name.c_str());
    glUniform2fv(location, 1, (GLfloat*)&vector); // cast vectors to GLfloat arrays
}

// vec3
void ShaderProgram::SetUniform(string name, vec3* vectors, int count)
{
    int location = glGetUniformLocation(programID, name.c_str());
    glUniform3fv(location, count, (GLfloat*)vectors); // cast vectors to GLfloat arrays
}

void ShaderProgram::SetUniform(string name, const vec3 &vector)
{
    int location = glGetUniformLocation(programID, name.c_str());
    glUniform3fv(location, 1, (GLfloat*)&vector); // cast vectors to GLfloat arrays
}

// vec4
void ShaderProgram::SetUniform(string name, vec4* vectors, int count)
{
    int location = glGetUniformLocation(programID, name.c_str());
    glUniform4fv(location, count, (GLfloat*)vectors); // cast vectors to GLfloat arrays
}

void ShaderProgram::SetUniform(string name, const vec4 &vector)
{
    int location = glGetUniformLocation(programID, name.c_str());
    glUniform4fv(location, 1, (GLfloat*)&vector); // cast vectors to GLfloat arrays
}

// Set 4x4 matrices
void ShaderProgram::SetUniform(string name, mat4* matrices, int count)
{
    int location = glGetUniformLocation(programID, name.c_str());
    glUniformMatrix4fv(location, count, GL_FALSE, (GLfloat*)matrices);
}

void ShaderProgram::SetUniform(string name, const mat4 &matrix)
{
    int location = glGetUniformLocation(programID, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, (GLfloat*)&matrix);
}

// Set ints
void ShaderProgram::SetUniform(string name, int* values, int count)
{
    int location = glGetUniformLocation(programID, name.c_str());
    glUniform1iv(location, count, values);
}

void ShaderProgram::SetUniform(string name, const int &value)
{
    int location = glGetUniformLocation(programID, name.c_str());
    glUniform1i(location, value);
}

GLint ShaderProgram::GetAttributeLocation(std::string attributeName)
{
    GLint location = glGetAttribLocation(programID, const_cast<const char*>(attributeName.c_str()));
    return location;
}

GLint ShaderProgram::GetUniformLocation(std::string uniformName)
{
    GLint location = glGetUniformLocation(programID, const_cast<const char*>(uniformName.c_str()));
    return location;
}

GLuint ShaderProgram::GetID()
{
    return programID;
}
