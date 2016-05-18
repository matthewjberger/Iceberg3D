#include "GLWindowManager.h"
#include "GLWindow.h"
#include "GLInputManager.h"
#include <vector>

using namespace icebergGL;
GLWindowManager::GLWindowManager() : iceberg::WindowManager()
{
    // TODO: Add error checking, exceptions etc.
    contextLoaded_ = false;
    this->initialize();

    // This window manager initializes its own input manager component
    inputManager_ = std::make_shared<GLInputManager>(this);
}

bool GLWindowManager::detect_version()
{
    // TODO: Possibly store detected version in a configuration file

    GLFWwindow* window = nullptr;

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    auto TryVersion = [&window, this](int major, int minor)
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);

        window = glfwCreateWindow(1, 1, "", nullptr, nullptr);
        if (window != nullptr)
        {
            glMajorVersion_ = major;
            glMinorVersion_ = minor;

            glfwDestroyWindow(window);

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
    }

    return true;
}

GLWindowManager::~GLWindowManager()
{
    glfwTerminate();
}

iceberg::Window* GLWindowManager::create_window(std::string caption, int width, int height, bool fullscreen)
{
    if(!hasFullscreenWindow_)
    {
        GLWindowParams params;
        params.id = next_id();
        params.glMajorVersion = glMajorVersion_;
        params.glMinorVersion = glMajorVersion_;
        params.caption = caption;
        params.width = width;
        params.height = height;
        params.fullscreen = fullscreen;

        add_window(std::make_shared<GLWindow>(params));

        if (!contextLoaded_)
        {
            gladLoadGL();
            contextLoaded_ = true;
        }

        hasFullscreenWindow_ = fullscreen;
    }

    return current_window();
}

void GLWindowManager::update()
{
    glfwPollEvents();

    std::vector<int> windows_to_close;

    for (auto it = windows_.begin(); it != windows_.end(); ++it)
    {
        it->second->update();

        // Find windows marked for closing
        if(it->second->should_close())
        {
            windows_to_close.push_back(it->second->id());
        }
    }

    for(int id : windows_to_close)
    {
        close_window(id);
    }
}

void GLWindowManager::refresh()
{
    for (auto it = windows_.begin(); it != windows_.end(); ++it)
    {
        it->second->refresh();
    }
}

bool GLWindowManager::has_active_windows()
{
    return (windows_.size() > 0);
}

int GLWindowManager::api_major_version()
{
    return glMajorVersion_;
}

int GLWindowManager::api_minor_version()
{
    return glMinorVersion_;
}

std::string GLWindowManager::api_version_string()
{
    return std::to_string(api_major_version()) + "." + std::to_string(api_minor_version());
}
void GLWindowManager::select_window(iceberg::Window* window)
{
    auto glWindow = static_cast<GLWindow*>(window);
    glfwMakeContextCurrent(glWindow->handle());
}