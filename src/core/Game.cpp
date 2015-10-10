#include "Game.h"

Game *Game::inst = 0;

Game::Game()
{
    // Initialize game variables and settings
    isRunning     = true;
    isFullscreen  = false;

    caption       = "Iceberg3D";

    window        = NULL;
    screenSurface = NULL;

    screenWidth   = 640;
    screenHeight  = 480;

    maxFPS        = 60;

    previousTime = std::chrono::high_resolution_clock::now();
}

Game *Game::GetInstance()
{
    if (inst == 0)
    {
        inst = new Game();
    }

    return inst;
}

bool Game::Initialize()
{
    // Set caption
    caption = "Matthew Berger's Game Engine";

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not be initialized! SDL_Error: %s", SDL_GetError() );

        return false;
    }
    else
    {

#ifdef VIRTUAL_MACHINE
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
#else
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
#endif

        // Create the window
        if (isFullscreen == true)
        {
            window = SDL_CreateWindow(caption.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP);
        }
        else if (isFullscreen == false)
        {
            window = SDL_CreateWindow(caption.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
        }

        if (window == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());

            return false;
        }
        else
        {
            // Create OpenGL Context
            context = SDL_GL_CreateContext(window);

            if (context == NULL)
            {
                printf("OpenGL context could not be created! SDL_Error: %s\n", SDL_GetError());

                return false;
            }
            else
            {
                // Initialize OpenGL

                // Dark blue background
                glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

                // Depth testing
                glEnable(GL_DEPTH_TEST);
                glClearDepth(1.0);

                // Enable culling
                //glEnable(GL_CULL_FACE);
                //glCullFace(GL_BACK);
                //glFrontFace(GL_CW);

                // Initialize GLEW
                glewExperimental = GL_TRUE;

                GLenum glewError = glewInit();

                if (glewError != GLEW_OK)
                {
                    printf("Error initializing GLEW! %s \n", glewGetErrorString(glewError));

                    return false;
                }

                /*
                // Use Vsync
                if (SDL_GL_SetSwapInterval(1) < 0)
                {
                printf("Warning: Unable to set VSync! SDL Error: %s", SDL_GetError());

                return false;
                }*/


                // Initialize screen surface
                screenSurface = SDL_GetWindowSurface(window);
            }

        }
    }

    return true;
}

bool Game::LoadContent(GameState *state)
{
    //-- Load game content here

    ChangeState(state);

    //--

    return true;
}

void Game::UnloadContent()
{

    // Release game content, Free Surfaces, Close Libraries
    if (!GameStates.empty())
    {
        GameStates.back()->Finalize();
        GameStates.pop_back();
    }

    /************************************************/
    // TTF_Quit();
    // Mix_CloseAudio();
    // Destroy Window

    SDL_DestroyWindow( window );
    window   = NULL;

    // Quit subsystems
    SDL_Quit();
}
void Game::ChangeState(GameState *state)
{
    // If there is a state, clean it up and pop it off
    if (!GameStates.empty())
    {
        GameStates.back()->Finalize();
        GameStates.pop_back();
    }

    // Push on the new one and initialize it
    GameStates.push_back(state);
    GameStates.back()->Initialize();
}

void Game::PushState(GameState *state)
{
    // Pause state if there is one already on stack
    if (!GameStates.empty())
    {
        GameStates.back()->Pause();
    }

    // Push state onto stack and initialize it
    GameStates.push_back(state);
    GameStates.back()->Initialize();
}

void Game::PopState()
{
    if (!GameStates.empty())
    {
        // If somethings on the stack and finish up state then pop it off
        GameStates.back()->Finalize();
        GameStates.pop_back();

        // If there's a state left, it is paused, so resume it
        GameStates.back()->Resume();
    }
}

void Game::Update()
{
    // Place Update logic here
    GameStates.back()->Update();

}

void Game::Draw()
{
    // Place Rendering logic here
    GameStates.back()->Draw();

}

void Game::EventHandler()
{
    while( SDL_PollEvent(&event) != 0 )
    {
        //Place Event Handling Functions here
        GameStates.back()->HandleEvents();

        if (event.type == SDL_QUIT)
        {
            this->StopRunning();
        }
        else if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
                case SDLK_F11:
                    this->ToggleFullScreen();
                    break;

                case SDLK_ESCAPE:
                    this->StopRunning();
                    break;
            }
        }
    }
}

void Game::DestroyInstance()
{
    delete inst;

    inst = 0;
}

void Game::ToggleFullScreen()
{
    if (isFullscreen == false)
    {
        SDL_SetWindowFullscreen(window, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP);

        isFullscreen = true;
    }
    else if (isFullscreen == true)
    {
        SDL_SetWindowFullscreen(window, 0);

        isFullscreen = false;
    }
}

bool Game::IsRunning()
{
    return isRunning;
}

int Game::GetMaxFPS()
{
    return maxFPS;
}

int Game::GetScreenWidth()
{
    return screenWidth;
}

int Game::GetScreenHeight()
{
    return screenHeight;
}

SDL_Event Game::GetEvent()
{
    return event;
}

SDL_Surface* Game::GetSurface()
{
    return screenSurface; // null
}

SDL_Window* Game::GetWindow()
{
    return window; // null
}

void Game::SetMaxFPS(int newFPS)
{
    maxFPS = newFPS;
}

void Game::StopRunning()
{
    isRunning = false;
}

float Game::GetTimeDelta()
{
    currentTime       = std::chrono::high_resolution_clock::now();
    float returnValue = std::chrono::duration_cast< std::chrono::duration<float> >(currentTime - previousTime).count();
    previousTime      = std::chrono::high_resolution_clock::now();

    return returnValue;
}

float Game::GetAspectRatio()
{
    // Prevent division by 0
    float adjustedScreenHeight = screenHeight;
    if(screenHeight == 0) adjustedScreenHeight = 1;
    return (float(screenWidth)/float(adjustedScreenHeight));
}
