#include "Skybox.h"
#include <stb_image.h>

using namespace iceberg;

Skybox::Skybox(const SkyboxParameters &skyboxParameters)
{
    std::vector<const GLchar*> faces;
    faces.push_back(skyboxParameters.right.c_str());
    faces.push_back(skyboxParameters.left.c_str());
    faces.push_back(skyboxParameters.top.c_str());
    faces.push_back(skyboxParameters.bottom.c_str());
    faces.push_back(skyboxParameters.back.c_str());
    faces.push_back(skyboxParameters.front.c_str());

    std::string vertexShaderSource = 
        "#version 330 core\n"
        "layout (location = 0) in vec3 position;\n"
        "out vec3 TexCoords;\n"
        "uniform mat4 projection;\n"
        "uniform mat4 view;\n"
        "void main()\n"
        "{\n"
        "    vec4 finalPos = projection * view * vec4(position, 1.0f);\n"
        "    gl_Position = finalPos.xyww;\n"
        "    TexCoords = position;\n"
        "}\n";

    std::string fragmentShaderSource =
        "#version 330 core\n"
        "in vec3 TexCoords;\n"
        "out vec4 color;\n"
        "uniform samplerCube skybox;\n"
        "void main()\n"
        "{    \n"
        "    color = texture(skybox, TexCoords);\n"
        "}\n";

    skyboxProgram_.create_program();
    skyboxProgram_.add_shader_from_source(vertexShaderSource, GL_VERTEX_SHADER);
    skyboxProgram_.add_shader_from_source(fragmentShaderSource, GL_FRAGMENT_SHADER);
    skyboxProgram_.link_program();

    cubemap_ = std::make_unique<Texture>(aiTextureType_DIFFUSE, GL_TEXTURE_CUBE_MAP);

    for (GLuint i = 0; i < faces.size(); i++)
    {
        cubemap_->load(faces[i], GL_TEXTURE_CUBE_MAP_POSITIVE_X + i);
    }

    cubemap_->set_wrap();

    // TODO: Use an IBO here
    GLfloat skyboxVertices[] =
    {
        // Positions
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f, 1.0f,
        -1.0f,  1.0f, 1.0f,
         1.0f,  1.0f, 1.0f,
         1.0f,  1.0f, 1.0f,
         1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f,

        -1.0f, 1.0f, -1.0f,
         1.0f, 1.0f, -1.0f,
         1.0f, 1.0f,  1.0f,
         1.0f, 1.0f,  1.0f,
        -1.0f, 1.0f,  1.0f,
        -1.0f, 1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };

    skyboxVAO_.create();
    skyboxVBO_.create();

    skyboxVAO_.bind();

    skyboxVBO_.bind();
    skyboxVBO_.add_data(&skyboxVertices, sizeof(skyboxVertices));
    skyboxVBO_.upload_data();

    skyboxVAO_.enable_attribute(0);
    skyboxVAO_.configure_attribute(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    skyboxVAO_.unbind();
}

Skybox::~Skybox()
{
}

void Skybox::draw(const Camera* camera) const
{
    glDepthFunc(GL_LEQUAL);

    skyboxProgram_.use();

    glm::mat4 view = glm::mat4(glm::mat3(camera->view_matrix()));
    skyboxProgram_.set_uniform("projection", camera->projection_matrix());
    skyboxProgram_.set_uniform("view", view);

    skyboxVAO_.bind();

    cubemap_->bind();
    skyboxProgram_.set_uniform("skybox", 0);

    glDrawArrays(GL_TRIANGLES, 0, 36);

    skyboxVAO_.unbind();

    glDepthFunc(GL_LESS);
}

