#include "ExampleState.h"

int main()
{
    // The most basic possible setup
    iceberg::Game game(iceberg::OPENGL);
    ExampleState state(&game);
    auto window = game.window_manager()->create_window("Iceberg3D - Basic Triangle", 320, 240);
    window->set_icon("assets/icon.png");
    game.change_state(&state);
    game.run();

    return 0;
}