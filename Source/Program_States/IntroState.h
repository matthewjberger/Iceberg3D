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
	ShaderProgram shaderProgram;
	Camera* camera;
	Skybox *skybox;
	Model* models[4];
	Texture sunTexture;
	PhysicsManager* physicsManager;
};
