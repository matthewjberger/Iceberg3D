#include "Game.h"
#include "GLWindowManager.h"

using namespace iceberg;

Game::Game(Backend backend)
    :stateMachine_(std::make_shared<StateMachine>())
{
    switch(backend)
    {
    case OPENGL:
        windowManager_ = std::make_shared<icebergGL::GLWindowManager>();
        break;

    default:
        throw std::runtime_error("Invalid backend specified");
    }

    // Begin the timer for delta time calculation
    previousTime_ = std::chrono::high_resolution_clock::now();
}

Game::~Game()
{
}

WindowManager* Game::window_manager() const
{
    return windowManager_.get();
}

void Game::change_state(GameState* state) const
{
    stateMachine_->change_state(state);
}

void Game::update()
{
    currentTime_ = std::chrono::high_resolution_clock::now();
    deltaTime_ = std::chrono::duration_cast<std::chrono::duration<float>>(currentTime_ - previousTime_).count();
    previousTime_ = std::chrono::high_resolution_clock::now();

    windowManager_->update();
    stateMachine_->update();
}

void Game::draw() const
{
    // Update the window
    stateMachine_->draw();
    windowManager_->refresh();
}

void Game::run()
{
    // TODO: Might be better to do this with an event
    while(windowManager_->has_active_windows())
    {
        update();
        draw();
    }
}

float Game::delta_time() const
{
   return deltaTime_;
}

void Game::handle_error(const std::string &errorMessage)
{
    boxer::show(errorMessage.c_str(), "Error", boxer::Style::Warning);
}
