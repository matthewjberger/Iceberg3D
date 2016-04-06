#ifndef GAME_H
#define GAME_H

// Define this symbol (VIRTUAL_MACHINE) if using a virtual machine
// Currently, vmware doesn't support OpenGL 3
// If unsure, install the mesa-utils package and then type
// glxinfo | grep "OpenGL" to get the OpenGL version information
// for your machine
#define VIRTUAL_MACHINE

#include "GlobalIncludes.h"
#include "StateMachine.h"

class GameState;

class Game
{
public:

    Game();

    ~Game();

    bool initialize();
    bool initialize_opengl();

    void update();
    void draw();
    void handle_events();

    void toggle_fullscreen();
    bool running() const;
    void exit();

    SDL_Window* window() const;
    glm::vec2 screen_dimensions() const;
    int fps() const;
    float aspect_ratio() const;

    std::chrono::time_point<std::chrono::high_resolution_clock> previousTime, currentTime;
    float time_delta();

    void change_state(GameState* state);
    SDL_Event event() const;

private:

    std::unique_ptr<StateMachine> stateMachine;

    bool running_;
    bool fullscreen_;
    std::string caption_;
    SDL_Window* window_;
    SDL_Surface* screenSurface_;
    SDL_Event event_;
    SDL_GLContext context_;

    int screenWidth_;
    int screenHeight_;

    int fps_;

    SDL_DisplayMode currentDisplayMode_;
};

class GameState : public ProgramState
{

public:
    virtual ~GameState() {};

    void ChangeState(GameState* state) const
    {
        game_->change_state(state);
    }

protected:
    GameState(Game* game) : game_(game){};
    Game* game_;

};

#endif

