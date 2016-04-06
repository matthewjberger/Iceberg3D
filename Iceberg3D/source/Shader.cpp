#include "Shader.h"
using namespace std;

Shader::Shader()
{
    // Initialize variables
    id_ = 0;
    type_ = 0;
    loaded_ = false;
}

Shader::~Shader()
{
    // Delete the shader
    delete_shader();
}

void Shader::delete_shader()
{
    if (loaded())
    {
        // Delete the shader
        glDeleteShader(id_);

        // Set shaderID to 0
        id_ = 0;

        // Set loaded to false
        loaded_ = false;
    }
}

bool Shader::load(std::string path, GLuint shadertype_)
{
    //  Success flag
    GLint compiled = GL_FALSE;

    // Create a shader of the correct type_
    id_ = glCreateShader(shadertype_);

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
        shaderSource.reserve(static_cast<unsigned int>(file.tellg()));

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
    glShaderSource(id_, 1, (const GLchar**)&shaderSource, nullptr);

    // Compile shader
    glCompileShader(id_);

    // Check if shader compiled successfully
    glGetShaderiv(id_, GL_COMPILE_STATUS, &compiled);

    // If compilation failed
    if (compiled != GL_TRUE)
    {
        // Print an error message
        printf("Couldn't compile shader %d\n\n Source code\n%s\n", id_, shaderSource.c_str());

        // Print shader log
        print_log();

        // Delete the shader
        glDeleteShader(id_);

        // Set shaderID to 0
        id_ = 0;

        // Return false
        return false;
    }

    // Set type_
    type_ = shadertype_;

    // loaded successfully
    loaded_ = true;

    // Return success
    return true;
}

void Shader::print_log()
{
    //Make sure name is shader
    if (glIsShader(id_))
    {
        //Shader log length
        int infoLogLength = 0;
        int maxLength = infoLogLength;

        //Get info string length
        glGetShaderiv(id_, GL_INFO_LOG_LENGTH, &maxLength);

        //Allocate string
        char* infoLog = new char[maxLength];

        //Get info log
        glGetShaderInfoLog(id_, maxLength, &infoLogLength, infoLog);

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
        printf("Name %d is not a shader\n", id_);
    }
}

bool Shader::loaded()
{
    return loaded_;
}

GLuint Shader::id()
{
    return id_;
}

