#include "Iceberg.h"

class ExampleState : public iceberg::GameState
{
public:
    ExampleState(iceberg::Game* game) : GameState(game){}
    ~ExampleState(){}

    void initialize() override;
    void finalize() override;

    void pause() override;
    void resume() override;

    void draw() override;
    void update() override;

private:
    std::shared_ptr<iceberg::Model> model;
    std::shared_ptr<iceberg::ShaderProgram> modelProgram;
    std::shared_ptr<iceberg::Camera> camera;
    std::shared_ptr<iceberg::Skybox> skybox;
    std::shared_ptr<iceberg::TextManager> textManager;

    float angle;
};