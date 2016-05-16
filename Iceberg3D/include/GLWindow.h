#ifndef GLWINDOW_H
#define GLWINDOW_H

#include "GLHeaders.h"
#include "Window.h"

namespace icebergGL
{
    class ICEBERGAPI GLWindow : public iceberg::Window
    {
    public:
        GLWindow(int id, std::string caption, int width, int height, bool fullscreen = false);
        virtual ~GLWindow();

        void Show() override;
        void Close() override;
    };
}

#endif