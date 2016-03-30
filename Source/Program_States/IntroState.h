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
    Model* model;
    Model* asteroid;
    ShaderProgram shaderProgram;
    glm::mat4 modelMatrix;
    Camera* camera;
    GLuint textureID;

    glm::mat4* modelMatrices;
    Skybox* skybox;
};

