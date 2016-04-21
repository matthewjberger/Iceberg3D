#include "Shader.h"
#include "Game.h"
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

bool Shader::load(const std::string &path, GLuint shadertype_)
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
        string errorMessage = "Couldn't open file: " + path;
        Game::handle_error(errorMessage);
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
        string errorMessage = "Couldn't compile shader #";
        errorMessage += to_string(id_);
        errorMessage += "\n\nSource Code:\n\n";
        errorMessage += shaderSource.c_str();
        errorMessage += "\n\nShader Log:\n\n";
        errorMessage += print_log();
        Game::handle_error(errorMessage.c_str());
        glDeleteShader(id_);
        id_ = 0;

        return false;
    }

    type_ = shadertype_;
    loaded_ = true;

    return true;
}

string Shader::print_log() const
{
    string log = "";

    if (glIsShader(id_))
    {
        int infoLogLength = 0;
        int maxLength = infoLogLength;

        glGetShaderiv(id_, GL_INFO_LOG_LENGTH, &maxLength);

        char* infoLog = new char[maxLength];
        glGetShaderInfoLog(id_, maxLength, &infoLogLength, infoLog);

        if (infoLogLength > 0)
        {
            log += infoLog;
            log += "\n";
        }

        delete[] infoLog;
    }
    else
    {
        log = "Name " + to_string(id_) + " is not a shader\n";
    }

    return log;
}

bool Shader::loaded() const
{
    return loaded_;
}

GLuint Shader::id() const
{
    return id_;
}

