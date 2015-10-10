#include "core/Game.h"
#include "program_states/IntroState.h"

int main(int argc, char *args[])
{
    // Create Game and debug instances
    Game *game = Game::GetInstance();

    bool fullscreen = false;

    if (game->Initialize() == false)
    {
        printf("Failed to Initialize!");
        return 1;
    }

    if (game->LoadContent(IntroState::GetInstance()) == false)
    {
        printf("Failed to load content");
        return 1;
    }

    while (game->IsRunning())
    {

        game->EventHandler();
        game->Update();
        game->Draw();

        //SDL_UpdateWindowSurface( game->GetWindow() );

        // Update window
        SDL_GL_SwapWindow(game->GetWindow());

        // Control framerate
        SDL_Delay(1000 / game->GetMaxFPS());

    }

    game->UnloadContent();
    game->DestroyInstance();

    return 0;
}
