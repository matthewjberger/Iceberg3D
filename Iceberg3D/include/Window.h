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
        virtual void set_caption(std::string caption) = 0;
        virtual void set_icon(std::string iconPath) = 0;
        virtual float aspect_ratio() = 0;

        int width() const;
        int height() const;

        void set_dimensions(int width, int height);

        virtual void show() = 0;
        virtual void close() = 0;
        virtual void update() = 0;
        virtual void refresh() = 0;
        virtual bool should_close() = 0;

    protected:
        int id_;
        std::string caption_;
        int width_;
        int height_;
        bool fullscreen_;
    };
}

#endif