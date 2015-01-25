#include "CShaderProgram.h"

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

bool ShaderProgram::AddShader(Shader* shader)
{
    if (!shader->IsLoaded())
    {
        // Print error message
        printf("Error: Tried to attach shader that wasn't loaded");

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
        glUseProgram(NULL);
    }
}
