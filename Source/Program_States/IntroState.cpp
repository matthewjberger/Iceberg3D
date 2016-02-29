#include "IntroState.h"
#include "../Core/GlobalIncludes.h"
void IntroState::Pause() {}
void IntroState::Resume() {}
IntroState *IntroState::inst = 0;

void IntroState::Initialize()
{
	// Initialize resources
	model = new Model("Assets/house/house.obj");
	model->LoadTexture("Assets/house/houseTexture.jpg", true);
	asteroid = new Model("Assets/asteroid/asteroid.obj");
	asteroid->LoadTexture("Assets/asteroid/asteroid.jpg", false);

	shaderProgram.CreateProgram();
	shaderProgram.AddShaderFromFile("Shaders/modelVert.glsl", GL_VERTEX_SHADER);
	shaderProgram.AddShaderFromFile("Shaders/modelFrag.glsl", GL_FRAGMENT_SHADER);
	shaderProgram.LinkProgram();
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	camera = new Camera(glm::vec3(0.0, 8.0, -8.0));
	camera->EnableInput();


	skybox = new Skybox("Assets/ame_starfield/starfield_rt.tga",
		"Assets/ame_starfield/starfield_lf.tga",
		"Assets/ame_starfield/starfield_rt.tga",
		"Assets/ame_starfield/starfield_dn.tga",
		"Assets/ame_starfield/starfield_bk.tga",
		"Assets/ame_starfield/starfield_ft.tga"
		);

	GLuint amount = 1000;
	modelMatrices = new glm::mat4[amount];
	srand(SDL_GetTicks()); // initialize random seed
	GLfloat radius = 50.0;
	GLfloat offset = 2.5f;
	for (GLuint i = 0; i < amount; i++)
	{
		glm::mat4 model;
		// 1. Translation: displace along circle with 'radius' in range [-offset, offset]
		GLfloat angle = (GLfloat)i / (GLfloat)amount * 360.0f;
		GLfloat displacement = (rand() % (GLint)(2 * offset * 100)) / 100.0f - offset;
		GLfloat x = sin(angle) * radius + displacement;
		displacement = (rand() % (GLint)(2 * offset * 100)) / 100.0f - offset;
		GLfloat y = displacement * 0.4f; // y value has smaller displacement
		displacement = (rand() % (GLint)(2 * offset * 100)) / 100.0f - offset;
		GLfloat z = cos(angle) * radius + displacement;
		model = glm::translate(model, glm::vec3(x, y, z));
		// 2. Scale: Scale between 0.05 and 0.25f
		GLfloat scale = (rand() % 20) / 100.0f + 0.05;
		model = glm::scale(model, glm::vec3(scale));
		// 3. Rotation: add random rotation around a (semi)randomly picked rotation axis vector
		GLfloat rotAngle = (rand() % 360);
		model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));
		// 4. Now add to list of matrices
		modelMatrices[i] = model;
	}
}

void IntroState::Finalize()
{
	// Free resources
	model->Free();
	asteroid->Free();
	shaderProgram.DeleteProgram();
	delete camera;
	camera = NULL;
	delete skybox;
	skybox = NULL;
}

void IntroState::HandleEvents()
{
	// Handle input logic
}

void IntroState::Update()
{
	// Update logic
	static float angle = 0.0f;
	angle += Game::GetInstance()->GetTimeDelta() * M_PI / 2;
	camera->Update();
	modelMatrix = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(1.0f, 1.0f, 1.0f));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f, 0.2f, 0.2f));
	glm::mat4 mvp = camera->GetMVP(modelMatrix);
	shaderProgram.SetUniform("mvpMatrix", &mvp);
	shaderProgram.SetUniform("sampler2D", 0);
}

void IntroState::Draw()
{
	// Clear the screen to Cornflower Blue
	glClearColor(0.392f, 0.584f, 0.93f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	skybox->Draw(camera->projectionMatrix, camera->viewMatrix);

	shaderProgram.UseProgram();
	model->Draw();

	for (GLuint i = 0; i < 1000; i++)
	{
		shaderProgram.SetUniform("mvpMatrix", camera->GetMVP(modelMatrices[i]));
		asteroid->Draw();
	}
}
