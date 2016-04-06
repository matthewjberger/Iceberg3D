#include "Game.h"
#include "IntroState.h"

int main(int argc, char* args[])
{
    // Create Game and States 
    Game* game = new Game();
    IntroState* intro = new IntroState(game);

    if (game->initialize() == false)
    {
        // TODO: Use SDL message boxes to display these errors
        // TODO: Create trace log
        printf("Failed to Initialize!");
        return 1;
    }

    game->change_state(intro);

    while (game->running())
    {
        game->handle_events();
        game->update();
        game->draw();

        // Control frame rate
        SDL_Delay(1000 / game->fps());
    }

    delete game;
    game = nullptr;

    return 0;
}

