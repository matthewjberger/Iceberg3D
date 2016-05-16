#include "GLWindow.h"

icebergGL::Window::Window(int id, std::string caption, int width, int height, bool fullscreen) :
    iceberg::Window(id, caption, width, height, fullscreen)
{
    int result = 1;

    if(!fullscreen)
    {

    }
    else
    {
        
    }
}

icebergGL::Window::~Window(){}

void icebergGL::Window::Show()
{
    // Nothing to do...
}

void icebergGL::Window::Close()
{
    
}