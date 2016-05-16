#include "GLWindowManager.h"
#include "GlWindow.h"

icebergGL::GLWindowManager::GLWindowManager() : iceberg::WindowManager(){}
icebergGL::GLWindowManager::~GLWindowManager() {}

bool icebergGL::GLWindowManager::initialize()
{
    // TODO: Initialize windowing subsystem here
    return true;
}

iceberg::Window* icebergGL::GLWindowManager::create_window(std::string caption, int width, int height, bool fullscreen)
{
    iceberg::Window* window = nullptr;

    if(!hasFullscreenWindow)
    {
        int nextID = next_id();

        window = new icebergGL::GLWindow(nextID, caption, width, height, fullscreen);

        if(window != nullptr)
        {
            add_window(window);
        }
    }

    return window;
}
