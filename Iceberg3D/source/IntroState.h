#include "Iceberg.h"

class ICEBERGAPI IntroState : public iceberg::GameState
{
public:

    IntroState(iceberg::Game* game) : GameState(game){}
    ~IntroState(){}

    void initialize() override;
    void finalize() override;

    void pause() override;
    void resume() override;

    void draw() override;
    void handle_events() override;
    void update() override;

private:

    std::unique_ptr<iceberg::Model> model;
    std::shared_ptr<iceberg::ShaderProgram> modelProgram;
    std::unique_ptr<iceberg::Camera> camera;
    std::unique_ptr<iceberg::Skybox> skybox;

    float angle;
};

