#ifndef GLWINDOW_H
#define GLWINDOW_H

#include "GLHeaders.h"
#include "Window.h"

namespace icebergGL
{
    struct GLWindowParams
    {
        int id;
        std::string caption;
        int width; int height;
        bool fullscreen;
        int glMajorVersion;
        int glMinorVersion;
    };

    class ICEBERGAPI GLWindow : public iceberg::Window
    {
    public:
        GLWindow(GLWindowParams params);
        virtual ~GLWindow();

        void show() override;
        void close() override;
        void update() override;
        void set_caption(std::string caption) override;
        void set_icon(std::string path) override;

        GLFWwindow* handle() const;

    private:
        GLFWwindow* window_;
    };
}

#endif