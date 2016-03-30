#include "../Core/Game.h"
#include "../Core/ShaderProgram.h"
#include "../Core/Camera.h"
#include "../Core/Model.h"
#include "../Core/Skybox.h"

class IntroState : public GameState
{
public:

    IntroState(Game* game) : GameState(game){}
    ~IntroState(){}

    void initialize() override;
    void finalize() override;

    void pause() override;
    void resume() override;

    void draw() override;
    void handle_events() override;
    void update() override;

private:

    /**************************/
    /* Place State Items here */
    /**************************/
    Model* model_;
    Model* asteroid_;
    ShaderProgram shaderProgram_;
    glm::mat4 modelMatrix_;
    Camera* camera_;
    GLuint textureID_;

    glm::mat4* modelMatrices_;
    Skybox* skybox_;
};

