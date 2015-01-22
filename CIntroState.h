#include "CoreGame.h"
#include "CShaderProgram.h"
#include "CVBO.h"
#include "CCamera.h"

class IntroState : public GameState
{
public:
	void Init(Game *game);
	void Finalize();

	void Pause();
	void Resume();

	void Draw(Game *game);
	void HandleEvents(Game *game);
	void Update(Game *game);

	static IntroState *GetInstance()
	{
		if (inst == 0)
		{
			inst = new IntroState();
		}

		return inst;
	}

protected:
	IntroState(){}


private:
	static IntroState *inst;

	/**************************/
	/* Place State Items here */

	// Shader program
	ShaderProgram mainProg;
	ShaderProgram colorProg;

	// Shaders
	Shader vShader, fShader;
	Shader vColorShader, fColorShader;

	// Vertex Array Object
	GLuint VAO;
	GLuint colorVAO;

	// Vertex Buffer Object
	VBO triVBO;

	// Texture
	Texture quadTexture;
	Texture otherTexture;
	Texture floorTexture;

	// Projection matrix
	mat4 ProjectionMatrix;
	
	// Projection matrix location
	GLuint ProjectionMatrixLoc;

	// ModelView matrix
	mat4 ModelViewMatrix;

	// ModelView matrix location
	GLuint ModelViewMatrixLoc;

	// Sampler location
	GLuint samplerLoc;

	// Color location
	GLuint colorLoc;

	// Camera
	Camera *myCamera;

	// Angle for rotation
	float angle;


	/**************************/
};


