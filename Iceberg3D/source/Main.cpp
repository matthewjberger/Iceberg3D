#include "Game.h"
#include "IntroState.h"

int main()
{
    // Create Game and States 
    std::unique_ptr<iceberg::Game> game = std::make_unique<iceberg::Game>();
    std::unique_ptr<IntroState> intro = std::make_unique<IntroState>(game.get());

    if (game->initialize() == false)
    {
        // TODO: Create trace log
        game->handle_error("Failed to Initialize!");
        return 1;
    }

    game->change_state(intro.get());

    while (game->running())
    {
        game->handle_events();
        game->update();
        game->draw();

        // TODO: Control frame rate
    }

    return 0;
}

