#include "IntroState.h"
#include "../Core/GlobalIncludes.h"

void IntroState::pause(){}
void IntroState::resume(){}

void IntroState::initialize()
{
    // Initialize resources
    model_ = new Model("Assets/house/house.obj");
    model_->load_texture("Assets/house/houseTexture.jpg", true);
    asteroid_ = new Model("Assets/asteroid/asteroid.obj");
    asteroid_->load_texture("Assets/asteroid/asteroid.jpg", false);

    shaderProgram_.create_program();
    shaderProgram_.add_shader_from_file("Shaders/modelVert.glsl", GL_VERTEX_SHADER);
    shaderProgram_.add_shader_from_file("Shaders/modelFrag.glsl", GL_FRAGMENT_SHADER);
    shaderProgram_.link_program();
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    camera_ = new Camera(game_, glm::vec3(0.0, 8.0, -8.0));
    camera_->enable_input();

    skybox_ = new Skybox("Assets/ame_starfield/starfield_rt.tga",
                        "Assets/ame_starfield/starfield_lf.tga",
                        "Assets/ame_starfield/starfield_rt.tga",
                        "Assets/ame_starfield/starfield_dn.tga",
                        "Assets/ame_starfield/starfield_bk.tga",
                        "Assets/ame_starfield/starfield_ft.tga"
    );

    // This asteroid belt code was copied from
    // an example written by Joey DeVries from learnopengl.com
    GLuint amount = 1000;
    modelMatrices_ = new glm::mat4[amount];
    srand(SDL_GetTicks()); // initialize random seed
    GLfloat radius = 25.0;
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
        modelMatrices_[i] = model;
    }
}

void IntroState::finalize()
{
    // Free resources
    model_->free();
    asteroid_->free();
    shaderProgram_.delete_program();
    delete camera_;
    camera_ = nullptr;
    delete skybox_;
    skybox_ = nullptr;
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
    camera_->update(game_);
    modelMatrix_ = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(1.0f, 1.0f, 1.0f));
    modelMatrix_ = glm::scale(modelMatrix_, glm::vec3(0.2f, 0.2f, 0.2f));
    glm::mat4 mvp = camera_->make_mvp(modelMatrix_);
    shaderProgram_.set_uniform("mvpMatrix", &mvp);
    shaderProgram_.set_uniform("sampler2D", 0);
}

void IntroState::draw()
{
    // Clear the screen to Cornflower Blue
    glClearColor(0.392f, 0.584f, 0.93f, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    skybox_->draw(camera_->projection_matrix(), camera_->view_matrix());

    shaderProgram_.use();
    model_->draw();

    for (GLuint i = 0; i < 1000; i++)
    {
        shaderProgram_.set_uniform("mvpMatrix", camera_->make_mvp(modelMatrices_[i]));
        asteroid_->draw();
    }
}

