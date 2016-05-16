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
    std::shared_ptr<iceberg::VAO> triVAO;
    std::shared_ptr<iceberg::Buffer> triVBO;
    std::shared_ptr<iceberg::ShaderProgram> triProgram;
};