#ifndef GAME_H
#define GAME_H

// Define this symbol (VIRTUAL_MACHINE) if using a virtual machine
// Currently, vmware doesn't support OpenGL 3
// If unsure, install the mesa-utils package and then type
// glxinfo | grep "OpenGL" to get the OpenGL version information
// for your machine
#define VIRTUAL_MACHINE

#include "GlobalIncludes.h"

class GameState;

class Game
{
public:

    Game();
    ~Game() {};

    bool initialize();
    bool load_content(GameState* state);
    void unload_content();
    void update();
    void draw();
    void HandleEvent();
    void change_state(GameState* state);
    void push_state(GameState* state);
    void pop_state();
    void toggle_fullscreen();

    // TODO: Refactor class to make these unnecessary
    // using the component pattern
    // Member Accessors
    SDL_Event GetEvent() const;
    bool IsRunning() const;
    void StopRunning();
    SDL_Window* GetWindow() const;
    SDL_Surface* GetSurface() const;
    int GetScreenWidth() const;
    int GetScreenHeight() const;
    int GetMaxFPS() const;
    void SetMaxFPS(int newFPS);
    float GetAspectRatio() const;

    std::vector<GameState *> GameStates; //GameState stack

    std::chrono::time_point<std::chrono::high_resolution_clock> previousTime, currentTime;
    float GetTimeDelta();

private:

    bool isRunning;
    bool isFullscreen;
    std::string caption;
    SDL_Window* window;
    SDL_Surface* screenSurface;
    SDL_Event event;
    SDL_GLContext context;

    int screenWidth;
    int screenHeight;

    int maxFPS;

    SDL_DisplayMode currentDisplayMode;
};

class GameState
{

public:
    virtual ~GameState() {};

    virtual void initialize() = 0;
    virtual void finalize() = 0;

    virtual void pause() = 0;
    virtual void resume() = 0;

    virtual void handle_events() = 0;
    virtual void draw() = 0;
    virtual void update() = 0;

    void ChangeState(GameState* state)
    {
        game_->change_state(state);
    }

protected:
    GameState(Game* game) : game_(game){};
    Game* game_;

};


#endif

