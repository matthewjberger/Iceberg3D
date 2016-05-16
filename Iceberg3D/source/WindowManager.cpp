#include "WindowManager.h"

using namespace iceberg;

WindowManager::WindowManager() : windows_()
{
    currentWindowID = 0;
    hasFullscreenWindow = false;
}

WindowManager::~WindowManager()
{
    std::map<int, Window*>::iterator iterator;

    for(iterator = windows_.begin(); iterator != windows_.end(); ++iterator)
    {
        // TODO: Use smart pointers
        if(iterator->second != nullptr)
        {
            delete iterator->second;
        }
    }

    windows_.clear();
}

int WindowManager::window_count() const
{
    return windows_.size();
}

void WindowManager::close_window(int id)
{
    if(windows_[id])
    {
        delete windows_[id];
    }

    windows_.erase(windows_.find(id));
}

void WindowManager::close_window(Window* window)
{
    close_window(window->id());
}

void WindowManager::add_window(Window* window)
{
    windows_[window->id()] = window;
}

int WindowManager::next_id()
{
    return ++currentWindowID;
}