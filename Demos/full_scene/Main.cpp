#include "ExampleState.h"

int main()
{
    // Create Game and States 
    std::unique_ptr<iceberg::Game> game = std::make_unique<iceberg::Game>();
    std::unique_ptr<ExampleState> Example = std::make_unique<ExampleState>(game.get());

    if (game->initialize() == false)
    {
        // TODO: Create trace log
        game->handle_error("Failed to Initialize!");
        return 1;
    }

    game->set_icon("assets/icon.png"); // Must be called after window initialization
    game->change_state(Example.get());

    while (game->running())
    {
        game->handle_events();
        game->update();
        game->draw();

        // TODO: Control frame rate
    }

    return 0;
}