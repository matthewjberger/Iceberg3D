#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include "Window.h"
#include <map>

namespace iceberg
{
    class ICEBERGAPI WindowManager
    {
    public:
        WindowManager();
        virtual ~WindowManager();

        int window_count() const;

        virtual bool initialize() = 0;
        virtual Window* create_window(std::string caption, int width, int height, bool fullscreen) = 0;

        void close_window(int id);
        void close_window(Window* window);

    protected:
        void add_window(Window* window);
        int next_id();
        bool hasFullscreenWindow;

    private:
        std::map<int, Window*> windows_;
        int currentWindowID;
    };
}


#endif