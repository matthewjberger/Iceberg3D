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
    // Initialize resources
    model = make_unique<Model>("assets/deadpool/dead 123456.obj");

    modelProgram = make_shared<ShaderProgram>();
    modelProgram->create_program();
    modelProgram->add_shader_from_file("shaders/modelVert.glsl", GL_VERTEX_SHADER);
    modelProgram->add_shader_from_file("shaders/modelFrag.glsl", GL_FRAGMENT_SHADER);
    modelProgram->link_program();

    camera = make_unique<Camera>(game_, vec3(0.0, 25.0, -70.0), glm::vec3(0), 100.0);
    camera->enable_input();

    SkyboxParameters snowySkybox;
    snowySkybox.right = "Assets/ame_powder/powderpeak_rt.tga";
    snowySkybox.left = "Assets/ame_powder/powderpeak_lf.tga";
    snowySkybox.top = "Assets/ame_powder/powderpeak_up.tga";
    snowySkybox.bottom = "Assets/ame_powder/powderpeak_dn.tga";
    snowySkybox.front = "Assets/ame_powder/powderpeak_ft.tga";
    snowySkybox.back = "Assets/ame_powder/powderpeak_bk.tga";

    skybox = make_unique<Skybox>(snowySkybox);

    angle = 0.0f;
}

void IntroState::update()
{
    angle += game_->delta_time() * float(pi<float>());
    camera->update(game_);
}

void IntroState::draw()
{
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    modelProgram->use();
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            // TODO: Instanced Rendering
            model->transform_manager()->translate(glm::mat4(1.0f), vec3(200.0f * i, 200.0f * j, 0.0f));
            model->transform_manager()->rotate(model->transform_manager()->model_matrix(), angle, vec3(0.0f, 1.0f, 0.0f));
            mat4 mvp = camera->make_mvp(model->transform_manager()->model_matrix());
            modelProgram->set_uniform("mvpMatrix", &mvp);
            model->draw(modelProgram.get(), camera.get());
        }
    }
    glDisable(GL_CULL_FACE);

    skybox->draw(camera.get());
}

