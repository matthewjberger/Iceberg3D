/*
    *************************
    Iceberg3D Graphics Engine
    Created by Matt Berger
    *************************

    API's used:
    SDL2/OpenGL
    
    Extension Libraries:
    SDL_image 2.0
    SDL_ttf 2.0
    SDL_mixer 2.0
    GLEW
    GLM
    GLU
*/

#include "CoreGame.h"

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

    if (game->LoadContent() == false)
    {
        printf("Failed to load content");
        return 1;
    }

    while (game->isRunning())
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
