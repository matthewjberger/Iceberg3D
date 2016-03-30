#include "Core/Game.h"
#include "Program_States/IntroState.h"

int main(int argc, char* args[])
{
    // Create Game and debug instances
    Game* game = new Game();
    IntroState* intro = new IntroState(game);

    if (game->initialize() == false)
    {
        // TODO: Use SDL message boxes to display these errors
        // TODO: Create trace log
        printf("Failed to Initialize!");
        return 1;
    }

    if (game->load_content(intro) == false)
    {
        printf("Failed to load content");
        return 1;
    }

    while (game->running())
    {
        game->handle_events();
        game->update();
        game->draw();

        // Control frame rate
        SDL_Delay(1000 / game->fps());
    }

    game->unload_content();

    delete game;
    game = nullptr;

    return 0;
}

