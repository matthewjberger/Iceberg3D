#include "Shader.h"
using namespace std;

Shader::Shader()
{
    id_ = 0;
    type_ = 0;
    loaded_ = false;
}

Shader::~Shader()
{
    delete_shader();
}

void Shader::delete_shader()
{
    if (loaded())
    {
        glDeleteShader(id_);
        id_ = 0;
        loaded_ = false;
    }
}

bool Shader::load(std::string path, GLuint shadertype_)
{
    GLint compiled = GL_FALSE;
    id_ = glCreateShader(shadertype_);
    ifstream file(path.c_str());
    string shaderSource;

    if (file.good())
    {
        shaderSource = string(istreambuf_iterator<char>(file),
                             (istreambuf_iterator<char>()));
    }
    else
    {
        printf("Couldn't open file %s\n", path.c_str());
        shaderSource = "";
        return false;
    }

    file.close();

    // Create the shader
    const char* source = shaderSource.c_str();
    glShaderSource(id_, 1, &source, nullptr);
    glCompileShader(id_);
    glGetShaderiv(id_, GL_COMPILE_STATUS, &compiled);
    if (compiled != GL_TRUE)
    {
        printf("Couldn't compile shader %d\n\n Source code\n%s\n", id_, shaderSource.c_str());
        print_log();
        glDeleteShader(id_);
        id_ = 0;

        return false;
    }

    type_ = shadertype_;
    loaded_ = true;

    return true;
}

void Shader::print_log() const
{
    if (glIsShader(id_))
    {
        int infoLogLength = 0;
        int maxLength = infoLogLength;

        glGetShaderiv(id_, GL_INFO_LOG_LENGTH, &maxLength);

        char* infoLog = new char[maxLength];
        glGetShaderInfoLog(id_, maxLength, &infoLogLength, infoLog);

        if (infoLogLength > 0)
        {
            printf("%s\n", infoLog);
        }

        delete[] infoLog;
    }
    else
    {
        printf("Name %d is not a shader\n", id_);
    }
}

bool Shader::loaded() const
{
    return loaded_;
}

GLuint Shader::id() const
{
    return id_;
}

