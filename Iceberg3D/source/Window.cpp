#include "Window.h"

using namespace iceberg;

Window::Window(int id, std::string caption, int width, int height, bool fullscreen)
{
    id_ = id;
    caption_ = caption;
    width_ = width;
    height_ = height;
    fullscreen_ = fullscreen;
}

Window::~Window(){}

int Window::id() const
{
    return id_;
}

int Window::width() const
{
    return width_;
}

int Window::height() const
{
    return height_;
}

std::string Window::caption() const
{
    return caption_;
}


bool Window::fullscreen() const
{
    return fullscreen_;
}

void Window::set_dimensions(int width, int height)
{
    width_ = width;
    height_ = height;
}

void Window::set_caption(std::string caption)
{
    caption_ = caption;
}