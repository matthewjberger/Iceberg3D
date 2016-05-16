#ifndef GL_WINDOW_MANAGER_H
#define GL_WINDOW_MANAGER_H

#include "WindowManager.h"
#include "GLWindow.h"

namespace icebergGL
{
    class ICEBERGAPI GLWindowManager : public iceberg::WindowManager
    {
    public:
        GLWindowManager();
        virtual ~GLWindowManager();

        bool initialize() override;
        void update() override;
        std::shared_ptr<iceberg::Window> create_window(std::string caption, int width, int height, bool fullscreen) override;

    private:
        bool detect_version();
        int glMajorVersion_;
        int glMinorVersion_;
    };
}

#endif