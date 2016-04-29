#include "ExampleState.h"

int main()
{
    // Create Game and States 
    std::shared_ptr<iceberg::Game> game = std::make_shared<iceberg::Game>();
    std::shared_ptr<ExampleState> Example = std::make_shared<ExampleState>(game.get());

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