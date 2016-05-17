#include "GLInputManager.h"
#include <GLWindow.h>

using namespace icebergGL;

void GLInputManager::get_cursor_pos(double* x, double* y)
{
    glfwGetCursorPos(current_window_handle(), x, y);
}

void GLInputManager::set_cursor_pos(int x, int y)
{
    glfwSetCursorPos(current_window_handle(), x, y);
}

void GLInputManager::hide_cursor()
{
    glfwSetInputMode(current_window_handle(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

void GLInputManager::show_cursor()
{
    glfwSetInputMode(current_window_handle(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

GLFWwindow* GLInputManager::current_window_handle() const
{
    auto glWindow = static_cast<GLWindow*>(parent_->current_window());
    if (glWindow == nullptr) return nullptr;
    return glWindow->handle();
}

bool GLInputManager::key_pressed(char keySymbol)
{
    return glfwGetKey(current_window_handle(), keySymbol);
}