#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include "Window.h"
#include <map>
#include <memory>

namespace iceberg
{
    class ICEBERGAPI WindowManager
    {
    public:
        WindowManager();
        virtual ~WindowManager();

        int window_count() const;

        virtual bool initialize() = 0;
        virtual std::shared_ptr<iceberg::Window> create_window(std::string caption, int width, int height, bool fullscreen = false) = 0;
        virtual void update() = 0;
        virtual void refresh() = 0;
        virtual bool has_active_windows() = 0;

        void close_window(int id);
        void close_window(Window* window);

        Window* current_window();

        virtual int api_major_version() = 0;
        virtual int api_minor_version() = 0;
        virtual std::string api_version_string() = 0;

    protected:
        void add_window(const std::shared_ptr<Window>& window);
        int next_id();
        bool hasFullscreenWindow_;
        std::map<int, std::shared_ptr<Window>> windows_;
        int currentWindowID_;
    };
}


#endif