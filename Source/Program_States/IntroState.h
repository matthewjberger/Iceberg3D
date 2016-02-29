#include "../Core/Game.h"
#include "../Core/ShaderProgram.h"
#include "../Core/VAO.h"
#include "../Core/VBO.h"
#include "../Core/Camera.h"
#include "../Core/Texture.h"
#include "../Core/Model.h"
#include "../Core/Skybox.h"
#include "../Core/PhysicsManager.h"

class IntroState : public GameState
{
public:
	void Initialize();
	void Finalize();

	void Pause();
	void Resume();

	void Draw();
	void HandleEvents();
	void Update();

	static IntroState *GetInstance()
	{
		if (inst == 0) inst = new IntroState();
		return inst;
	}

private:
	IntroState() {}
	~IntroState() {}
	static IntroState *inst;

	/**************************/
	/* Place State Items here */
	/**************************/
	Model *model;
	Model *asteroid;
	ShaderProgram shaderProgram;
	glm::mat4 modelMatrix;
	Camera* camera;
	GLuint textureID;

	glm::mat4* modelMatrices;
	Skybox *skybox;
};
