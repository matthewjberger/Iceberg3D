#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "Defines.h"
#include "KeyCode.h"

namespace iceberg
{
    class ICEBERGAPI InputManager
    {
    public:
        virtual ~InputManager(){};

        virtual void hide_cursor() = 0;
        virtual void show_cursor() = 0;
        virtual void set_cursor_pos(int xPos, int yPos) = 0;
        virtual void get_cursor_pos(double *xPos, double *yPos) = 0;
        virtual bool key_pressed(int keySymbol) = 0;
    };
}

#endif