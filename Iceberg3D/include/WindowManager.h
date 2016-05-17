#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include "Window.h"
#include "InputManager.h"
#include <map>
#include <memory>

namespace iceberg
{
    class ICEBERGAPI WindowManager
    {
    public:
        WindowManager();
        virtual ~WindowManager();

        virtual bool initialize() = 0;
        virtual Window* create_window(std::string caption, int width, int height, bool fullscreen = false) = 0;
        virtual void update() = 0;
        virtual void refresh() = 0;
        virtual bool has_active_windows() = 0;

        virtual void select_window(Window* window) = 0;

        virtual int api_major_version() = 0;
        virtual int api_minor_version() = 0;
        virtual std::string api_version_string() = 0;

        Window* current_window();
        Window* get_window(int id);
        void close_window(int id);
        void close_window(Window* window);
        int window_count() const;
        void select_window(int id);
        InputManager* input_manager() const;

    protected:
        void add_window(const std::shared_ptr<Window>& window);
        int next_id();
        bool hasFullscreenWindow_;
        int currentWindowID_;
        std::map<int, std::shared_ptr<Window>> windows_;
        std::shared_ptr<InputManager> inputManager_;
    };
}


#endif