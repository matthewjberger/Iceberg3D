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
        void refresh() override;
        bool has_active_windows() override;
        std::shared_ptr<iceberg::Window> create_window(std::string caption, int width, int height, bool fullscreen) override;

        int api_major_version() override;
        int api_minor_version() override;
        std::string api_version_string() override;

    private:
        bool detect_version();
        bool contextLoaded_;
        int glMajorVersion_;
        int glMinorVersion_;
    };
}

#endif