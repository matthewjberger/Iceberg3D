#ifndef WINDOW_H
#define WINDOW_H
#include <string>
#include "Defines.h"

namespace iceberg
{
    class ICEBERGAPI Window
    {
    public:
        Window(int id, std::string caption, int width, int height, bool fullscreen);
        virtual ~Window();

        bool fullscreen() const;

        int id() const;

        std::string caption() const;
        virtual void set_caption(std::string caption);

        int width() const;
        int height() const;

        void set_dimensions(int width, int height);

        virtual void Show() = 0;
        virtual void Close() = 0;

    private:
        int id_;
        std::string caption_;
        int width_;
        int height_;
        bool fullscreen_;
    };
}

#endif