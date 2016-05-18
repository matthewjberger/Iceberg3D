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
    std::shared_ptr<iceberg::VAO> quadVAO;
    std::shared_ptr<iceberg::Buffer> quadVBO;
    std::shared_ptr<iceberg::Buffer> quadIBO;
    std::shared_ptr<iceberg::ShaderProgram> quadProgram;
    std::shared_ptr<iceberg::Texture> quadTexture;
};

