#ifndef GLWINDOW_H
#define GLWINDOW_H

#include "GLHeaders.h"
#include "Window.h"

namespace icebergGL
{
    class ICEBERGAPI Window : public iceberg::Window
    {
    public:
        Window(int id, std::string caption, int width, int height, bool fullscreen = false);
        virtual ~Window();

        void Show() override;
        void Close() override;
    };
}

#endif