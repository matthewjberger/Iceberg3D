#include "Core/Game.h"
#include "Program_States/IntroState.h"

int main(int argc, char* args[])
{
    // Create Game and debug instances
    Game* game = Game::GetInstance();

    if (game->initialize() == false)
    {
        printf("Failed to Initialize!");
        return 1;
    }

    if (game->load_content(IntroState::GetInstance()) == false)
    {
        printf("Failed to load content");
        return 1;
    }

    while (game->IsRunning())
    {
        game->HandleEvent();
        game->update();
        game->draw();

        //SDL_UpdateWindowSurface( game->GetWindow() );

        // Update window
        SDL_GL_SwapWindow(game->GetWindow());

        // Control frame rate
        SDL_Delay(1000 / game->GetMaxFPS());
    }

    game->unload_content();
    game->destroy_instance();

    return 0;
}

