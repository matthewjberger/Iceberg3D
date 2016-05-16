#include "GLWindowManager.h"

using namespace icebergGL;
GLWindowManager::GLWindowManager() : iceberg::WindowManager(){}
GLWindowManager::~GLWindowManager() {}

bool GLWindowManager::detect_version()
{
    // TODO: Possibly store detected version in a configuration file

    GLFWwindow* window = nullptr;

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    auto TryVersion = [&window, this](int major, int minor)
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);

        window = glfwCreateWindow(10, 10, "", nullptr, nullptr);
        if (window != nullptr)
        {
            glMajorVersion_ = major;
            glMinorVersion_ = minor;

            return true;
        }

        return false;
    };

    // OpenGL 4.5 - 4.0
    for (int minorVersion = 5; minorVersion >= 0; minorVersion--)
    {
        if (TryVersion(4, minorVersion)) return true;
    }

    // OpenGL 3.3 Core
    if (TryVersion(3, 3)) return true;

    // Failed to create an OpenGL context
    return false;
}

bool GLWindowManager::initialize()
{
    // Initialize windowing subsystem
    if(glfwInit() == GL_FALSE)
    {
        printf("Could not initialize glfw!");
        return false;
    }
    else
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, glMajorVersion_);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, glMinorVersion_);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
        if(!detect_version())
        {
            printf("Could not detect OpenGL version!");
            return false;
        }

        gladLoadGL();
    }

    return true;
}

std::shared_ptr<iceberg::Window> GLWindowManager::create_window(std::string caption, int width, int height, bool fullscreen)
{
    std::shared_ptr<iceberg::Window> window = nullptr;

    if(!hasFullscreenWindow)
    {
        GLWindowParams params;
        params.id = next_id();
        params.glMajorVersion = glMajorVersion_;
        params.glMinorVersion = glMajorVersion_;
        params.caption = caption;
        params.width = width;
        params.height = height;
        params.fullscreen = fullscreen;

        window = std::make_shared<icebergGL::GLWindow>(params);

        if(window != nullptr)
        {
            add_window(window.get());
        }
    }

    return window;
}

void GLWindowManager::update()
{
    std::map<int, iceberg::Window*>::iterator iterator;

    for (iterator = windows_.begin(); iterator != windows_.end(); ++iterator)
    {
        if (iterator->second != nullptr)
        {
            iterator->second->update();
        }
    }
}