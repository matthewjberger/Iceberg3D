#include "../Core/Game.h"
#include "../Core/ShaderProgram.h"
#include "../Core/Camera.h"
#include "../Core/Model.h"
#include "../Core/Skybox.h"

class IntroState : public GameState
{
public:
    void Initialize() override;
    void Finalize() override;

    void Pause() override;
    void Resume() override;

    void Draw() override;
    void HandleEvents() override;
    void Update() override;

    static IntroState* GetInstance()
    {
        if (inst == nullptr) inst = new IntroState();
        return inst;
    }

private:
    IntroState()
    {
    }

    ~IntroState()
    {
    }

    static IntroState* inst;

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

