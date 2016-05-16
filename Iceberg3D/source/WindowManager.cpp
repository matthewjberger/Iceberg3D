#include "WindowManager.h"

using namespace iceberg;

WindowManager::WindowManager() : windows_()
{
    currentWindowID_ = 0;
    hasFullscreenWindow_ = false;
}

WindowManager::~WindowManager()
{
    windows_.clear();
}

int WindowManager::window_count() const
{
    return windows_.size();
}

void WindowManager::close_window(int id)
{
    windows_.erase(windows_.find(id));
}

void WindowManager::close_window(Window* window)
{
    close_window(window->id());
}

void WindowManager::add_window(const std::shared_ptr<Window>& window)
{
    windows_[window->id()] = window;
}

int WindowManager::next_id()
{
    return ++currentWindowID_;
}

Window* WindowManager::current_window()
{
    return windows_[currentWindowID_].get();
}