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
    void handle_events() override;
    void update() override;

private:
    std::unique_ptr<iceberg::VAO> quadVAO;
    std::unique_ptr<iceberg::VBO> quadVBO;
    std::unique_ptr<iceberg::VBO> quadIBO;
    std::unique_ptr<iceberg::ShaderProgram> quadProgram;
    std::unique_ptr<iceberg::Texture> quadTexture;
};

