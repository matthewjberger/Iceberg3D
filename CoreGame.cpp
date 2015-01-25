#include "CoreGame.h"
#include "CIntroState.h"

Game::Game()
{
    // Initialize game variables and settings
    m_Running = true;
    m_FullScreen = false;

    char* caption = "";

    window = NULL;
    screenSurface = NULL;

    defaultColor = { 0, 0, 0 };

    screenWidth  = 1024;
    screenHeight = 768;

    maxFPS = 60;
}

Game::~Game()
{
}

Game *Game::inst = 0;

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
        // Use OpenGL 3
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        // Create the window
        if (m_FullScreen == true)
        {
            window = SDL_CreateWindow(caption, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP);
        }
        else if (m_FullScreen == false)
        {
            window = SDL_CreateWindow(caption, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
        }

        if (window == NULL)
        {
            printf("Window could not be created! SDL_Error: %s", SDL_GetError());

            return false;
        }
        else
        {
            // Create OpenGL Context
            context = SDL_GL_CreateContext(window);

            if (context == NULL)
            {
                printf("OpenGL context could not be created! SDL_Error: %s", SDL_GetError());

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

                //Check for error
                GLenum error = glGetError();
                if (error != GL_NO_ERROR)
                {
                    printf("Error initializing OpenGL! %s\n", gluErrorString(error));
                    //return false;
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

bool Game::LoadContent()
{
    //-- Load game content here

    ChangeState(IntroState::GetInstance());

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
    GameStates.back()->Init(this);
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
    GameStates.back()->Init(this);
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
    GameStates.back()->Update(this);

}

void Game::Draw()
{
    // Place Rendering logic here
    GameStates.back()->Draw(this);

}

void Game::EventHandler()
{
    while( SDL_PollEvent(&event) != 0 )
    {
        //Place Event Handling Functions here
        GameStates.back()->HandleEvents(this);

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
    if (m_FullScreen == false)
    {
        SDL_SetWindowFullscreen(window, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP);

        m_FullScreen = true;
    }
    else if (m_FullScreen == true)
    {
        SDL_SetWindowFullscreen(window, 0);

        m_FullScreen = false;
    }
}

void Game::CycleColors(SDL_Color &color, int increment)
{
    if ((color.r == 255) && (0 <= color.g) && (color.g < 255) && (color.b == 0))
    {
        color.g += increment;
    }
    else if ((0 < color.r) && (color.r <= 255) && (color.g == 255) && (color.b == 0))
    {
        color.r -= increment;
    }
    else if ((color.r == 0) && (color.g == 255) && (0 <= color.b) && (color.b < 255))
    {
        color.b += increment;
    }
    else if ((color.r == 0) && (0 < color.g) && (color.g <= 255) && (color.b == 255))
    {
        color.g -= increment;
    }
    else if ((0 <= color.r) && (color.r <= 255) && (color.g == 0) && (color.b == 255))
    {
        color.r += increment;
    }
    else if ((color.r == 255) && (color.g == 0) && (0 < color.b) && (color.b <= 255))
    {
        color.b -= increment;
    }
}

