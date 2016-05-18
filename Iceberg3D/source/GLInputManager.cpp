#include "GLInputManager.h"
#include <GLWindow.h>

using namespace icebergGL;

GLInputManager::GLInputManager(icebergGL::GLWindowManager* parent)
{
    parent_ = parent;
    load_keymap();
}


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

bool GLInputManager::key_pressed(int keySymbol)
{
    char upper = toupper(keySymbol);
    auto it = keyMap_.find(keySymbol);
    
    // Ignore invalid keypresses
    if (it == keyMap_.end()) return false;

    bool pressed = glfwGetKey(current_window_handle(), it->second);
    if (pressed)
    {
        return true;
    }
    return false;
}

void GLInputManager::load_keymap()
{
    using namespace iceberg;
    keyMap_.emplace(ICEBERG_KEY_UNKNOWN, GLFW_KEY_UNKNOWN);
    keyMap_.emplace(ICEBERG_KEY_SPACE, GLFW_KEY_SPACE);
    keyMap_.emplace(ICEBERG_KEY_APOSTROPHE, GLFW_KEY_APOSTROPHE);
    keyMap_.emplace(ICEBERG_KEY_COMMA, GLFW_KEY_COMMA);
    keyMap_.emplace(ICEBERG_KEY_MINUS, GLFW_KEY_MINUS);
    keyMap_.emplace(ICEBERG_KEY_PERIOD, GLFW_KEY_PERIOD);
    keyMap_.emplace(ICEBERG_KEY_SLASH, GLFW_KEY_SLASH);
    keyMap_.emplace(ICEBERG_KEY_0, GLFW_KEY_0);
    keyMap_.emplace(ICEBERG_KEY_1, GLFW_KEY_1);
    keyMap_.emplace(ICEBERG_KEY_2, GLFW_KEY_2);
    keyMap_.emplace(ICEBERG_KEY_3, GLFW_KEY_3);
    keyMap_.emplace(ICEBERG_KEY_4, GLFW_KEY_4);
    keyMap_.emplace(ICEBERG_KEY_5, GLFW_KEY_5);
    keyMap_.emplace(ICEBERG_KEY_6, GLFW_KEY_6);
    keyMap_.emplace(ICEBERG_KEY_7, GLFW_KEY_7);
    keyMap_.emplace(ICEBERG_KEY_8, GLFW_KEY_8);
    keyMap_.emplace(ICEBERG_KEY_9, GLFW_KEY_9);
    keyMap_.emplace(ICEBERG_KEY_SEMICOLON, GLFW_KEY_SEMICOLON);
    keyMap_.emplace(ICEBERG_KEY_EQUAL, GLFW_KEY_EQUAL);
    keyMap_.emplace(ICEBERG_KEY_A, GLFW_KEY_A);
    keyMap_.emplace(ICEBERG_KEY_B, GLFW_KEY_B);
    keyMap_.emplace(ICEBERG_KEY_C, GLFW_KEY_C);
    keyMap_.emplace(ICEBERG_KEY_D, GLFW_KEY_D);
    keyMap_.emplace(ICEBERG_KEY_E, GLFW_KEY_E);
    keyMap_.emplace(ICEBERG_KEY_F, GLFW_KEY_F);
    keyMap_.emplace(ICEBERG_KEY_G, GLFW_KEY_G);
    keyMap_.emplace(ICEBERG_KEY_H, GLFW_KEY_H);
    keyMap_.emplace(ICEBERG_KEY_I, GLFW_KEY_I);
    keyMap_.emplace(ICEBERG_KEY_J, GLFW_KEY_J);
    keyMap_.emplace(ICEBERG_KEY_K, GLFW_KEY_K);
    keyMap_.emplace(ICEBERG_KEY_L, GLFW_KEY_L);
    keyMap_.emplace(ICEBERG_KEY_M, GLFW_KEY_M);
    keyMap_.emplace(ICEBERG_KEY_N, GLFW_KEY_N);
    keyMap_.emplace(ICEBERG_KEY_O, GLFW_KEY_O);
    keyMap_.emplace(ICEBERG_KEY_P, GLFW_KEY_P);
    keyMap_.emplace(ICEBERG_KEY_Q, GLFW_KEY_Q);
    keyMap_.emplace(ICEBERG_KEY_R, GLFW_KEY_R);
    keyMap_.emplace(ICEBERG_KEY_S, GLFW_KEY_S);
    keyMap_.emplace(ICEBERG_KEY_T, GLFW_KEY_T);
    keyMap_.emplace(ICEBERG_KEY_U, GLFW_KEY_U);
    keyMap_.emplace(ICEBERG_KEY_V, GLFW_KEY_V);
    keyMap_.emplace(ICEBERG_KEY_W, GLFW_KEY_W);
    keyMap_.emplace(ICEBERG_KEY_X, GLFW_KEY_X);
    keyMap_.emplace(ICEBERG_KEY_Y, GLFW_KEY_Y);
    keyMap_.emplace(ICEBERG_KEY_Z, GLFW_KEY_Z);
    keyMap_.emplace(ICEBERG_KEY_LEFT_BRACKET, GLFW_KEY_LEFT_BRACKET);
    keyMap_.emplace(ICEBERG_KEY_BACKSLASH, GLFW_KEY_BACKSLASH);
    keyMap_.emplace(ICEBERG_KEY_RIGHT_BRACKET, GLFW_KEY_RIGHT_BRACKET);
    keyMap_.emplace(ICEBERG_KEY_GRAVE_ACCENT, GLFW_KEY_GRAVE_ACCENT);
    keyMap_.emplace(ICEBERG_KEY_WORLD_1, GLFW_KEY_WORLD_1);
    keyMap_.emplace(ICEBERG_KEY_WORLD_2, GLFW_KEY_WORLD_2);
    keyMap_.emplace(ICEBERG_KEY_ESCAPE, GLFW_KEY_ESCAPE);
    keyMap_.emplace(ICEBERG_KEY_ENTER, GLFW_KEY_ENTER);
    keyMap_.emplace(ICEBERG_KEY_TAB, GLFW_KEY_TAB);
    keyMap_.emplace(ICEBERG_KEY_BACKSPACE, GLFW_KEY_BACKSPACE);
    keyMap_.emplace(ICEBERG_KEY_INSERT, GLFW_KEY_INSERT);
    keyMap_.emplace(ICEBERG_KEY_DELETE, GLFW_KEY_DELETE);
    keyMap_.emplace(ICEBERG_KEY_RIGHT, GLFW_KEY_RIGHT);
    keyMap_.emplace(ICEBERG_KEY_LEFT, GLFW_KEY_LEFT);
    keyMap_.emplace(ICEBERG_KEY_DOWN, GLFW_KEY_DOWN);
    keyMap_.emplace(ICEBERG_KEY_UP, GLFW_KEY_UP);
    keyMap_.emplace(ICEBERG_KEY_PAGE_UP, GLFW_KEY_PAGE_UP);
    keyMap_.emplace(ICEBERG_KEY_PAGE_DOWN, GLFW_KEY_PAGE_DOWN);
    keyMap_.emplace(ICEBERG_KEY_HOME, GLFW_KEY_HOME);
    keyMap_.emplace(ICEBERG_KEY_END, GLFW_KEY_END);
    keyMap_.emplace(ICEBERG_KEY_CAPS_LOCK, GLFW_KEY_CAPS_LOCK);
    keyMap_.emplace(ICEBERG_KEY_SCROLL_LOCK, GLFW_KEY_SCROLL_LOCK);
    keyMap_.emplace(ICEBERG_KEY_NUM_LOCK, GLFW_KEY_NUM_LOCK);
    keyMap_.emplace(ICEBERG_KEY_PRINT_SCREEN, GLFW_KEY_PRINT_SCREEN);
    keyMap_.emplace(ICEBERG_KEY_PAUSE, GLFW_KEY_PAUSE);
    keyMap_.emplace(ICEBERG_KEY_F1, GLFW_KEY_F1);
    keyMap_.emplace(ICEBERG_KEY_F2, GLFW_KEY_F2);
    keyMap_.emplace(ICEBERG_KEY_F3, GLFW_KEY_F3);
    keyMap_.emplace(ICEBERG_KEY_F4, GLFW_KEY_F4);
    keyMap_.emplace(ICEBERG_KEY_F5, GLFW_KEY_F5);
    keyMap_.emplace(ICEBERG_KEY_F6, GLFW_KEY_F6);
    keyMap_.emplace(ICEBERG_KEY_F7, GLFW_KEY_F7);
    keyMap_.emplace(ICEBERG_KEY_F8, GLFW_KEY_F8);
    keyMap_.emplace(ICEBERG_KEY_F9, GLFW_KEY_F9);
    keyMap_.emplace(ICEBERG_KEY_F10, GLFW_KEY_F10);
    keyMap_.emplace(ICEBERG_KEY_F11, GLFW_KEY_F11);
    keyMap_.emplace(ICEBERG_KEY_F12, GLFW_KEY_F12);
    keyMap_.emplace(ICEBERG_KEY_F13, GLFW_KEY_F13);
    keyMap_.emplace(ICEBERG_KEY_F14, GLFW_KEY_F14);
    keyMap_.emplace(ICEBERG_KEY_F15, GLFW_KEY_F15);
    keyMap_.emplace(ICEBERG_KEY_F16, GLFW_KEY_F16);
    keyMap_.emplace(ICEBERG_KEY_F17, GLFW_KEY_F17);
    keyMap_.emplace(ICEBERG_KEY_F18, GLFW_KEY_F18);
    keyMap_.emplace(ICEBERG_KEY_F19, GLFW_KEY_F19);
    keyMap_.emplace(ICEBERG_KEY_F20, GLFW_KEY_F20);
    keyMap_.emplace(ICEBERG_KEY_F21, GLFW_KEY_F21);
    keyMap_.emplace(ICEBERG_KEY_F22, GLFW_KEY_F22);
    keyMap_.emplace(ICEBERG_KEY_F23, GLFW_KEY_F23);
    keyMap_.emplace(ICEBERG_KEY_F24, GLFW_KEY_F24);
    keyMap_.emplace(ICEBERG_KEY_F25, GLFW_KEY_F25);
    keyMap_.emplace(ICEBERG_KEY_KP_0, GLFW_KEY_KP_0);
    keyMap_.emplace(ICEBERG_KEY_KP_1, GLFW_KEY_KP_1);
    keyMap_.emplace(ICEBERG_KEY_KP_2, GLFW_KEY_KP_2);
    keyMap_.emplace(ICEBERG_KEY_KP_3, GLFW_KEY_KP_3);
    keyMap_.emplace(ICEBERG_KEY_KP_4, GLFW_KEY_KP_4);
    keyMap_.emplace(ICEBERG_KEY_KP_5, GLFW_KEY_KP_5);
    keyMap_.emplace(ICEBERG_KEY_KP_6, GLFW_KEY_KP_6);
    keyMap_.emplace(ICEBERG_KEY_KP_7, GLFW_KEY_KP_7);
    keyMap_.emplace(ICEBERG_KEY_KP_8, GLFW_KEY_KP_8);
    keyMap_.emplace(ICEBERG_KEY_KP_9, GLFW_KEY_KP_9);
    keyMap_.emplace(ICEBERG_KEY_KP_DECIMAL, GLFW_KEY_KP_DECIMAL);
    keyMap_.emplace(ICEBERG_KEY_KP_DIVIDE, GLFW_KEY_KP_DIVIDE);
    keyMap_.emplace(ICEBERG_KEY_KP_MULTIPLY, GLFW_KEY_KP_MULTIPLY);
    keyMap_.emplace(ICEBERG_KEY_KP_SUBTRACT, GLFW_KEY_KP_SUBTRACT);
    keyMap_.emplace(ICEBERG_KEY_KP_ADD, GLFW_KEY_KP_ADD);
    keyMap_.emplace(ICEBERG_KEY_KP_ENTER, GLFW_KEY_KP_ENTER);
    keyMap_.emplace(ICEBERG_KEY_KP_EQUAL, GLFW_KEY_KP_EQUAL);
    keyMap_.emplace(ICEBERG_KEY_LEFT_SHIFT, GLFW_KEY_LEFT_SHIFT);
    keyMap_.emplace(ICEBERG_KEY_LEFT_CONTROL, GLFW_KEY_LEFT_CONTROL);
    keyMap_.emplace(ICEBERG_KEY_LEFT_ALT, GLFW_KEY_LEFT_ALT);
    keyMap_.emplace(ICEBERG_KEY_LEFT_SUPER, GLFW_KEY_LEFT_SUPER);
    keyMap_.emplace(ICEBERG_KEY_RIGHT_SHIFT, GLFW_KEY_RIGHT_SHIFT);
    keyMap_.emplace(ICEBERG_KEY_RIGHT_CONTROL, GLFW_KEY_RIGHT_CONTROL);
    keyMap_.emplace(ICEBERG_KEY_RIGHT_ALT, GLFW_KEY_RIGHT_ALT);
    keyMap_.emplace(ICEBERG_KEY_RIGHT_SUPER, GLFW_KEY_RIGHT_SUPER);
    keyMap_.emplace(ICEBERG_KEY_MENU, GLFW_KEY_MENU);
    keyMap_.emplace(ICEBERG_KEY_LAST, GLFW_KEY_LAST);
}