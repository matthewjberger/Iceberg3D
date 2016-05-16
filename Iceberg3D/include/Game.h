#ifndef GAME_H
#define GAME_H

#include "GlobalIncludes.h"
#include "StateMachine.h"
#include "WindowManager.h"

namespace iceberg
{
    enum ICEBERGAPI Backend
    {
        OPENGL
    };

    class ICEBERGAPI GameState;

    class ICEBERGAPI Game
    {
    public:
        Game(Backend backend);
        ~Game();

        void run();
        float delta_time() const;
        void change_state(GameState* state) const;

        WindowManager* window_manager() const;
        static void handle_error(const std::string &errorMessage);

    private:
        std::shared_ptr<WindowManager> windowManager_;
        std::shared_ptr<StateMachine> stateMachine_;
        std::chrono::time_point<std::chrono::high_resolution_clock> previousTime_, currentTime_;

        float deltaTime_;

        void update();
        void draw() const;
 
    };

    class ICEBERGAPI GameState : public ProgramState
    {
    public:
        virtual ~GameState() {};

        void ChangeState(GameState* state) const
        {
            game_->change_state(state);
        }

    protected:
        GameState(Game* game) : game_(game) {};
        Game* game_;
    };
}
#endif