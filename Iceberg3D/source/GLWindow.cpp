#include "GLWindow.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

using namespace icebergGL;

icebergGL::GLWindow::GLWindow(GLWindowParams params) :
    iceberg::Window(params.id, params.caption, params.width, params.height, params.fullscreen)
{
    if(!params.fullscreen)
    {
        window_ = glfwCreateWindow(params.width, params.height, params.caption.c_str(), nullptr, nullptr);
    }
    else
    {
        
        window_ = glfwCreateWindow(params.width, params.height, params.caption.c_str(), glfwGetPrimaryMonitor(), nullptr);
    }

    if (window_ != nullptr)
    {
        glfwMakeContextCurrent(window_);
    }
    else
    {
        printf("Could not create a glfw window!");
    }
}

GLWindow::~GLWindow()
{
    close();
}

void GLWindow::show()
{
    glfwShowWindow(window_);
}

void GLWindow::close()
{
    glfwDestroyWindow(window_);
}

void GLWindow::update()
{
    // Clear the screen
    glClearColor(0.392f, 0.584f, 0.93f, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLWindow::refresh()
{
    glfwSwapBuffers(window_);
}

GLFWwindow* GLWindow::handle() const
{
    return window_;
}

void GLWindow::set_caption(std::string caption)
{
    caption_ = caption;
    glfwSetWindowTitle(window_, caption_.c_str());
}

void GLWindow::set_icon(std::string path)
{
    int x, y, c;
    GLFWimage image;
    image.pixels = stbi_load(path.c_str(), &x, &y, &c, 0);
    image.width = x;
    image.height = y;
    if (image.pixels != NULL)
    {
        glfwSetWindowIcon(window_, 1, &image);
    }
    else
    {
        printf("Failed to load icon: %s", path.c_str());
    }
}

float GLWindow::aspect_ratio()
{
    // Prevent division by 0
    float width = float(width_);
    float height = float(height_);
    glfwSetWindowAspectRatio(window_, width, height);
    return(height == 0) ? (width) : (width / height);
}

bool GLWindow::should_close()
{
    return glfwWindowShouldClose(window_);
}

void GLWindow::mark_for_closing()
{
    glfwSetWindowShouldClose(window_, true);
}
