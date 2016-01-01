#include "Shader.h"
using namespace std;

Shader::Shader()
{
    // Initialize variables
    shaderID = 0;
    type     = 0;
    loaded   = false;
}

Shader::~Shader()
{
    // Delete the shader
    DeleteShader();
}

void Shader::DeleteShader()
{
    if (IsLoaded())
    {
        // Delete the shader
        glDeleteShader(shaderID);

        // Set shaderID to 0
        shaderID = 0;

        // Set loaded to false
        loaded = false;
    }
}

bool Shader::Load(std::string path, GLuint shaderType)
{
    //  Success flag
    GLint compiled = GL_FALSE;

    // Create a shader of the correct type
    shaderID = glCreateShader(shaderType);

    // Input stream
    ifstream file(path.c_str());

    // Source string
    string shaderSource;

    // Clear file flags
    file.clear();

    // If the file opened successfully
    if (file.good())
    {
        // Get total length of file
        file.seekg(0, ios::end);

        // Set string size to length of file
        shaderSource.reserve((unsigned int)file.tellg());

        // Reset cursor to beginning of file
        file.seekg(0, ios::beg);

        // Read in file as one string
        shaderSource.assign((istreambuf_iterator<char>(file)), (istreambuf_iterator<char>()));

    }
    else
    {
        // Print error message
        printf("Couldn't open file %s\n", path.c_str());

        // Set string to empty
        shaderSource = "";

        // Return false
        return false;
    }

    // Close file
    file.close();

    // Set shader source
    glShaderSource(shaderID, 1, (const GLchar**)&shaderSource, NULL);

    // Compile shader
    glCompileShader(shaderID);

    // Check if shader compiled successfully
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compiled);

    // If compilation failed
    if (compiled != GL_TRUE)
    {
        // Print an error message
        printf("Couldn't compile shader %d\n\n Source code\n%s\n", shaderID, shaderSource.c_str());

        // Print shader log
        PrintLog();

        // Delete the shader
        glDeleteShader(shaderID);

        // Set shaderID to 0
        shaderID = 0;

        // Return false
        return false;
    }

    // Set type
    type = shaderType;

    // loaded succesfully
    loaded = true;

    // Return success
    return true;
}

void Shader::PrintLog()
{
    //Make sure name is shader
    if (glIsShader(shaderID))
    {
        //Shader log length
        int infoLogLength = 0;
        int maxLength = infoLogLength;

        //Get info string length
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

        //Allocate string
        char* infoLog = new char[maxLength];

        //Get info log
        glGetShaderInfoLog(shaderID, maxLength, &infoLogLength, infoLog);

        if (infoLogLength > 0)
        {
            //Print Log
            printf("%s\n", infoLog);
        }

        //Deallocate string
        delete[] infoLog;
    }
    else
    {
        printf("Name %d is not a shader\n", shaderID);
    }
}

bool Shader::IsLoaded()
{
    return loaded;
}

GLuint Shader::GetID()
{
    return shaderID;
}

