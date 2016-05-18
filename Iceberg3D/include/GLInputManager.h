#ifndef GLINPUT_MANAGER_H
#define GLINPUT_MANAGER_H

#include "InputManager.h"
#include "GLWindowManager.h"
#include "GLHeaders.h"

namespace icebergGL
{
    class GLInputManager : public iceberg::InputManager
    {
    public:
        GLInputManager(icebergGL::GLWindowManager* parent);

        void hide_cursor() override;
        void show_cursor() override;
        void set_cursor_pos(int x, int y) override;
        void get_cursor_pos(double *x, double* y) override;
        bool key_pressed(int keySymbol) override;

    private:
        GLWindowManager* parent_;
        GLFWwindow* current_window_handle() const;
        std::map<int, int> keyMap_;
        void load_keymap();
    };
}

#endif