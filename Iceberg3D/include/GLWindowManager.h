#ifndef GL_WINDOW_MANAGER_H
#define GL_WINDOW_MANAGER_H

#include "WindowManager.h"

namespace icebergGL
{
    class ICEBERGAPI GLWindowManager : public iceberg::WindowManager
    {
    public:
        GLWindowManager();
        virtual ~GLWindowManager();

        bool initialize() override;
        iceberg::Window* create_window(std::string caption, int width, int height, bool fullscreen) override;
    };
}

#endif