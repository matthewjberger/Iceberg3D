#include "IntroState.h"
#include "../Core/GlobalIncludes.h"

void IntroState::pause(){}
void IntroState::resume(){}

void IntroState::initialize()
{
    // Initialize resources
    model = new Model("Assets/house/house.obj");
    model->load_texture("Assets/house/houseTexture.jpg", true);

    shaderProgram.create_program();
    shaderProgram.add_shader_from_file("Shaders/modelVert.glsl", GL_VERTEX_SHADER);
    shaderProgram.add_shader_from_file("Shaders/modelFrag.glsl", GL_FRAGMENT_SHADER);
    shaderProgram.link_program();
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    camera = new Camera(game_, glm::vec3(0.0, 8.0, -8.0));
    camera->enable_input();

    SkyboxParameters skyboxParameters;

    skyboxParameters.right  = "Assets/skybox/right.jpg";
    skyboxParameters.left   = "Assets/skybox/left.jpg";
    skyboxParameters.top    = "Assets/skybox/top.jpg";
    skyboxParameters.bottom = "Assets/skybox/bottom.jpg";
    skyboxParameters.front  = "Assets/skybox/front.jpg";
    skyboxParameters.back   = "Assets/skybox/back.jpg";

    skybox = new Skybox(skyboxParameters);
}

void IntroState::finalize()
{
    // Free resources
    model->free();
    shaderProgram.delete_program();
    delete camera;
    camera = nullptr;
    delete skybox;
    skybox = nullptr;
}

void IntroState::handle_events()
{
    // Handle input logic
}

void IntroState::update()
{
    // Update logic
    static float angle = 0.0f;
    angle += game_->time_delta() * M_PI / 2;
    camera->update(game_);
    modelMatrix = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(1.0f, 1.0f, 1.0f));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f, 0.2f, 0.2f));
    glm::mat4 mvp = camera->make_mvp(modelMatrix);
    shaderProgram.set_uniform("mvpMatrix", &mvp);
    shaderProgram.set_uniform("sampler2D", 0);
}

void IntroState::draw()
{
    // Clear the screen to Cornflower Blue
    glClearColor(0.392f, 0.584f, 0.93f, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // TODO: Allow skyboxes to be drawn last
    skybox->draw(camera->projection_matrix(), camera->view_matrix());

    shaderProgram.use();
    model->draw();
}

