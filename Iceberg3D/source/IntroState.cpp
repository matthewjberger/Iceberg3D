#include "IntroState.h"
#include "GlobalIncludes.h"

using namespace std;
using namespace glm;

void IntroState::pause(){}
void IntroState::resume(){}
void IntroState::finalize(){}
void IntroState::handle_events(){}

void IntroState::initialize()
{
    //// Initialize resources
    model = make_unique<Model>("Assets/house/house.obj");

    texture = make_unique<Texture>();
    texture->load("Assets/skybox/front.jpg");

    shaderProgram = make_shared<ShaderProgram>();
    shaderProgram->create_program();
    shaderProgram->add_shader_from_file("Shaders/triVert.glsl", GL_VERTEX_SHADER);
    shaderProgram->add_shader_from_file("Shaders/triFrag.glsl", GL_FRAGMENT_SHADER);
    shaderProgram->link_program();

    GLfloat vertices[] = {
        // Positions          // Colors           // Texture Coords
        0.25f - 0.5f,  0.25f - 0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // Top Right
        0.25f - 0.5f, -0.25f - 0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // Bottom Right
        -0.25f - 0.5f, -0.25f - 0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // Bottom Left
        -0.25f - 0.5f,  0.25f - 0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // Top Left 
    };
    GLuint indices[] = {  // Note that we start from 0!
        0, 1, 3,   // First Triangle
        1, 2, 3    // Second Triangle
    };

    triVAO.create();
    triVBO.create();
    triIBO.create();

    triVAO.bind();

    triVBO.bind();
    triVBO.add_data(&vertices, sizeof(vertices));
    triVBO.upload_data();

    triIBO.bind(GL_ELEMENT_ARRAY_BUFFER);
    triIBO.add_data(&indices, sizeof(indices));
    triIBO.upload_data();

    triVAO.enable_attribute(0);
    triVAO.configure_attribute(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
    triVAO.enable_attribute(1);
    triVAO.configure_attribute(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    triVAO.enable_attribute(2);
    triVAO.configure_attribute(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));

    triVAO.unbind();

    camera = make_unique<Camera>(game_, vec3(0.0, 25.0, -70.0));
    camera->enable_input();

    SkyboxParameters skyboxParameters;
    skyboxParameters.right = "Assets/skybox/right.jpg";
    skyboxParameters.left = "Assets/skybox/left.jpg";
    skyboxParameters.top = "Assets/skybox/top.jpg";
    skyboxParameters.bottom = "Assets/skybox/bottom.jpg";
    skyboxParameters.front = "Assets/skybox/front.jpg";
    skyboxParameters.back = "Assets/skybox/back.jpg";

    skybox = make_unique<Skybox>(skyboxParameters);
}

void IntroState::update()
{
    // Update logic
    static float angle = 0.0f;
    angle += game_->time_delta() * float(pi<float>())/2;

    camera->update(game_);

    model->transform_manager()->rotate(mat4(1.0f), angle, vec3(0.0f, 1.0f, 0.0f));

    mat4 mvp = camera->make_mvp(model->transform_manager()->model_matrix());
    shaderProgram->set_uniform("mvpMatrix", &mvp);
}

void IntroState::draw()
{
    skybox->draw(camera.get());

    shaderProgram->use();
    model->draw(shaderProgram.get(), camera.get());
    texture->bind();
    triVAO.bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

