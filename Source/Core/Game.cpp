#include "Game.h"

using namespace std;
using namespace glm;

Game::Game()
    :stateMachine(make_unique<StateMachine>())
{
    // Initialize game variables and settings
    running_ = true;
    fullscreen_ = false;

    caption_ = "Iceberg3D";
    screenWidth_ = 640;
    screenHeight_ = 480;

    fps_ = 60;

    window_ = nullptr;
    screenSurface_ = nullptr;
    context_ = nullptr;

    // Begin the timer for delta time calculation
    previousTime = std::chrono::high_resolution_clock::now();
}

Game::~Game()
{
    TTF_Quit();

    SDL_DestroyWindow(window_);
    window_ = nullptr;

    // Quit subsystems
    TTF_Quit();
    SDL_Quit();
}

bool Game::initialize()
{
    // Set caption
    caption_ = "Matthew Berger's Game Engine";

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not be initialized! SDL_Error: %s", SDL_GetError());

        return false;
    }
    else
    {
        // Create the window
        if (fullscreen_ == true)
        {
            window_ = SDL_CreateWindow(caption_.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth_, screenHeight_, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP);
        }
        else if (fullscreen_ == false)
        {
            window_ = SDL_CreateWindow(caption_.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth_, screenHeight_, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
        }

        if (window_ == nullptr)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());

            return false;
        }
        else
        {
            if (!initialize_opengl())
            {
                return false;
            }

            // Initialize screen surface
            screenSurface_ = SDL_GetWindowSurface(window_);

            // Use VSync
            if (SDL_GL_SetSwapInterval(1) < 0)
            {
                printf("Warning: Unable to set VSync! SDL Error: %s", SDL_GetError());

                return false;
            }

            // Initialize Sub Systems
            if (TTF_Init() != 0)
            {
                printf("Error initializing SDL_ttf! %s \n", TTF_GetError());

                return false;
            }
        }
    }

    return true;
}

bool Game::initialize_opengl()
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

    // Create OpenGL Context
    context_ = SDL_GL_CreateContext(window_);

    if (context_ == nullptr)
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
        glDepthFunc(GL_LESS);

        // Enable culling
        glEnable(GL_CULL_FACE);
        //glCullFace(GL_BACK);
        //glFrontFace(GL_CW);

        // Initialize GLEW
        glewExperimental = GL_TRUE;

        GLenum glewError = glewInit();

        if (glewError != GLEW_OK)
        {
            printf("Error initializing GLEW! %p \n", glewGetErrorString(glewError));

            return false;
        }
    }

    return true;
}

void Game::change_state(GameState* state)
{
    stateMachine->change_state(state);
}

void Game::update()
{
    stateMachine->update();
}

void Game::draw()
{
    stateMachine->draw();

    // Update the window
    SDL_GL_SwapWindow(window_);

    // TODO: Implement 2D rendering with SDL as option
    //SDL_UpdateWindowSurface( game->GetWindow() );
}

void Game::handle_events()
{
    // TODO: Make a component base class
    // TODO: Make a derived InputComponent class and use it here
    while (SDL_PollEvent(&event_) != 0)
    {
        stateMachine->handle_events();

        if (event_.type == SDL_QUIT)
        {
            this->exit();
        }
        else if (event_.type == SDL_KEYDOWN)
        {
            switch (event_.key.keysym.sym)
            {
            case SDLK_F11:
                this->toggle_fullscreen();
                break;

            case SDLK_ESCAPE:
                this->exit();
                break;
            }
        }
    }
}

void Game::toggle_fullscreen()
{
    if (fullscreen_ == false)
    {
        SDL_SetWindowFullscreen(window_, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP);

        fullscreen_ = true;
    }
    else if (fullscreen_ == true)
    {
        SDL_SetWindowFullscreen(window_, 0);

        fullscreen_ = false;
    }
}

bool Game::running() const
{
    return running_;
}

int Game::fps() const
{
    return fps_;
}

SDL_Window* Game::window() const
{
    return window_;
}

glm::vec2 Game::screen_dimensions() const
{
    return glm::vec2(screenWidth_, screenHeight_);
}

void Game::exit()
{
    running_ = false;
}

float Game::time_delta()
{
    currentTime = std::chrono::high_resolution_clock::now();
    float returnValue = std::chrono::duration_cast<std::chrono::duration<float>>(currentTime - previousTime).count();
    previousTime = std::chrono::high_resolution_clock::now();

    return returnValue;
}

float Game::aspect_ratio() const
{
    // Prevent division by 0
    float width = float(screenWidth_);
    float height = float(screenHeight_);
    return (height == 0) ? (width) : (width / height);
}

SDL_Event Game::event() const
{
    return event_;
}
    