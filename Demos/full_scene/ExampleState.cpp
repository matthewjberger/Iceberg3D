#include "ExampleState.h"
#include "GlobalIncludes.h"

using namespace iceberg;

void ExampleState::pause() {}
void ExampleState::resume() {}
void ExampleState::finalize() {}

void ExampleState::initialize()
{
    // Initialize resources
    model = std::make_shared<Model>("assets/deadpool/dead 123456.obj");

    modelProgram = std::make_shared<ShaderProgram>();
    modelProgram->create_program();
    modelProgram->add_shader_from_file("shaders/modelVert.glsl", GL_VERTEX_SHADER);
    modelProgram->add_shader_from_file("shaders/modelFrag.glsl", GL_FRAGMENT_SHADER);
    modelProgram->link_program();

    camera = std::make_shared<Camera>(game_, glm::vec3(12.0, 14.0, 30.0), glm::vec3(0), 100.0);
    camera->enable_input();

    SkyboxParameters snowySkybox;
    snowySkybox.right = "assets/ame_powder/powderpeak_rt.tga";
    snowySkybox.left = "assets/ame_powder/powderpeak_lf.tga";
    snowySkybox.top = "assets/ame_powder/powderpeak_up.tga";
    snowySkybox.bottom = "assets/ame_powder/powderpeak_dn.tga";
    snowySkybox.front = "assets/ame_powder/powderpeak_ft.tga";
    snowySkybox.back = "assets/ame_powder/powderpeak_bk.tga";

    skybox = std::make_shared<Skybox>(snowySkybox);

    textManager = std::make_shared<TextManager>(game_);
    textManager->load_font("fonts/inconsolata.ttf", 24);

    angle = 0.0f;
}

void ExampleState::update()
{
    angle += game_->delta_time() * float(glm::pi<float>());
    camera->update(game_);
}

void ExampleState::draw()
{
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    modelProgram->use();
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            // TODO: Instanced Rendering
            model->transform()->translate(glm::mat4(1.0f), glm::vec3(8.0f * i, 8.0f * j, 0.0f));
            model->transform()->rotate(angle, glm::vec3(0.0f, 1.0f, 0.0f));
            model->transform()->scale(glm::vec3(0.02f, 0.02f, 0.02f));
            glm::mat4 mvp = camera->make_mvp(model->transform()->model_matrix());
            modelProgram->set_uniform("mvpMatrix", &mvp);
            model->draw(modelProgram.get());
        }
    }
    glDisable(GL_CULL_FACE);

    skybox->draw(camera->projection_matrix(), camera->view_matrix());

    textManager->render_text("Welcome to the Iceberg3D Game Engine!", 30, 30, 1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}