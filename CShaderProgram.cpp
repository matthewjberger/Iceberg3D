#include "CShaderProgram.h"

ShaderProgram::ShaderProgram()
{
    // Initialize variables
    mProgramID = 0;
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
        glDeleteProgram(mProgramID);
    }
}

void ShaderProgram::CreateProgram()
{
    mProgramID = glCreateProgram();
}

bool ShaderProgram::AddShader(Shader* shader)
{
    if (!shader->IsLoaded())
    {
        // Print error message
        printf("Error: Tried to attach shader that wasn't loaded");

        // Return status
        return false;
    }

    glAttachShader(mProgramID, shader->GetID());

    // Return status
    return true;
}

bool ShaderProgram::LinkProgram()
{
    // Success flag
    GLint success = GL_TRUE;

    // Make the shader Program
    glLinkProgram(mProgramID);

    // Check if program was created successfully
    glGetProgramiv(mProgramID, GL_COMPILE_STATUS, &success);

    // If program creation failed
    if (success != GL_TRUE)
    {
        // Print an error message
        printf("Couldn't link program %d\n", mProgramID);

        // Print log
        PrintLog();

        // Delete the program
        glDeleteProgram(mProgramID);

        // Set program ID to 0
        mProgramID = 0;

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
    glGetProgramiv(mProgramID, GL_INFO_LOG_LENGTH, &maxLength);

    //Allocate string
    char* infoLog = new char[maxLength];

    //Get info log
    glGetProgramInfoLog(mProgramID, maxLength, &infoLogLength, infoLog);
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
        glUseProgram(mProgramID);
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
    int location = glGetUniformLocation(mProgramID, name.c_str());
    glUniform1fv(location, count, values);
}

void ShaderProgram::SetUniform(string name, const float value)
{
    int location = glGetUniformLocation(mProgramID, name.c_str());
    glUniform1fv(location, 1, &value);
}

// Set vectors

// vec2
void ShaderProgram::SetUniform(string name, vec2* vectors, int count)
{
    int location = glGetUniformLocation(mProgramID, name.c_str());
    glUniform2fv(location, count, (GLfloat*)vectors); // cast vectors to GLfloat arrays
}

void ShaderProgram::SetUniform(string name, const vec2 vector)
{
    int location = glGetUniformLocation(mProgramID, name.c_str());
    glUniform2fv(location, 1, (GLfloat*)&vector); // cast vectors to GLfloat arrays
}

// vec3
void ShaderProgram::SetUniform(string name, vec3* vectors, int count)
{
    int location = glGetUniformLocation(mProgramID, name.c_str());
    glUniform3fv(location, count, (GLfloat*)vectors); // cast vectors to GLfloat arrays
}

void ShaderProgram::SetUniform(string name, const vec3 vector)
{
    int location = glGetUniformLocation(mProgramID, name.c_str());
    glUniform3fv(location, 1, (GLfloat*)&vector); // cast vectors to GLfloat arrays
}

// vec4
void ShaderProgram::SetUniform(string name, vec4* vectors, int count)
{
    int location = glGetUniformLocation(mProgramID, name.c_str());
    glUniform4fv(location, count, (GLfloat*)vectors); // cast vectors to GLfloat arrays
}

void ShaderProgram::SetUniform(string name, const vec4 vector)
{
    int location = glGetUniformLocation(mProgramID, name.c_str());
    glUniform4fv(location, 1, (GLfloat*)&vector); // cast vectors to GLfloat arrays
}

// Set 4x4 matrices
void ShaderProgram::SetUniform(string name, mat4* matrices, int count)
{
    int location = glGetUniformLocation(mProgramID, name.c_str());
    glUniformMatrix4fv(location, count, GL_FALSE, (GLfloat*)matrices);
}

void ShaderProgram::SetUniform(string name, const mat4 matrix)
{
    int location = glGetUniformLocation(mProgramID, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, (GLfloat*)&matrix);
}

// Set ints
void ShaderProgram::SetUniform(string name, int* values, int count)
{
    int location = glGetUniformLocation(mProgramID, name.c_str());
    glUniform1iv(location, 1, values);
}

void ShaderProgram::SetUniform(string name, const int value)
{
    int location = glGetUniformLocation(mProgramID, name.c_str());
    glUniform1i(location, value);
}
