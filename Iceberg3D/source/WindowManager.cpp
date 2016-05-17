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
    auto it = windows_.find(id);
    if (it == windows_.end()) return;
    windows_.erase(it);
}

void WindowManager::close_window(Window* window)
{
    close_window(window->id());
}

void WindowManager::add_window(const std::shared_ptr<Window>& window)
{
    windows_.emplace(window->id(), window);
}

int WindowManager::next_id()
{
    return ++currentWindowID_;
}

Window* WindowManager::current_window()
{
    return get_window(currentWindowID_);
}

void WindowManager::select_window(int id)
{
    select_window(get_window(id));
}

Window* WindowManager::get_window(int id)
{
    auto it = windows_.find(id);
    if (it == windows_.end()) return nullptr;
    auto window = it->second;
    return window.get();
}