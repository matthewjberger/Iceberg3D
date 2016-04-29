#ifndef GAME_H
#define GAME_H

#include "GlobalIncludes.h"
#include "StateMachine.h"

namespace iceberg
{
    class ICEBERGAPI GameState;

    class ICEBERGAPI Game
    {
    public:
        Game();
        ~Game();

        bool initialize();

        void update();
        void draw() const;
        void handle_events() const;
        
        void set_icon(const std::string& path);
        void set_caption(const std::string& caption);
        
        void toggle_fullscreen();
        static bool running();
        static void exit();
        static void handle_error(const std::string &errorMessage);

        glm::vec2 screen_dimensions() const;
        int fps() const;
        float aspect_ratio() const;

        float delta_time() const;

        void change_state(GameState* state) const;
        static GLFWwindow* window();

    private:
        static GLFWwindow* window_;
        void build_caption(); // default caption
        bool create_window();

        std::shared_ptr<StateMachine> stateMachine_;
        std::chrono::time_point<std::chrono::high_resolution_clock> previousTime_, currentTime_;

        bool fullscreen_;
        std::string caption_;

        int majorVersion_, minorVersion_, patchVersion_;
        int glMajorVersion_, glMinorVersion_;

        int screenWidth_;
        int screenHeight_;

        int fps_;

        float deltaTime_;
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