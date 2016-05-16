#include "GLWindowManager.h"
#include "GlWindow.h"

icebergGL::WindowManager::WindowManager() : iceberg::WindowManager(){}
icebergGL::WindowManager::~WindowManager() {}

bool icebergGL::WindowManager::initialize()
{
    // TODO: Initialize windowing subsystem here
    return true;
}

iceberg::Window* icebergGL::WindowManager::create_window(std::string caption, int width, int height, bool fullscreen)
{
    iceberg::Window* window = nullptr;

    if(!hasFullscreenWindow)
    {
        int nextID = next_id();

        window = new icebergGL::Window(nextID, caption, width, height, fullscreen);

        if(window != nullptr)
        {
            add_window(window);
        }
    }

    return window;
}
