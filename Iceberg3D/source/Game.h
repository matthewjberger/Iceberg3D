#ifndef GAME_H
#define GAME_H

#include "GlobalIncludes.h"
#include "StateMachine.h"

class GameState;

class Game
{
public:

    Game();
    ~Game();

    bool initialize();

    void update() const;
    void draw() const;
    void handle_events() const;

    void toggle_fullscreen();
    bool running() const;
    void exit() const;

    GLFWwindow* window() const;
    glm::vec2 screen_dimensions() const;
    int fps() const;
    float aspect_ratio() const;

    std::chrono::time_point<std::chrono::high_resolution_clock> previousTime, currentTime;
    float time_delta();

    void change_state(GameState* state) const;

private:

    std::unique_ptr<StateMachine> stateMachine;

    bool fullscreen_;
    std::string caption_;
    std::string iconPath_;
    GLFWwindow* window_;
    int majorVersion_;
    int minorVersion_;

    int screenWidth_;
    int screenHeight_;

    int fps_;
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

