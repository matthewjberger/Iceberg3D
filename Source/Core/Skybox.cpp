#include "Skybox.h"

using namespace std;
using namespace glm;

Skybox::Skybox(const SkyboxParameters &skyboxParameters)
{
    // TODO: use the Texture class here and throw they can't be loaded properly
    vector<const GLchar*> faces;
    faces.push_back(skyboxParameters.right.c_str());
    faces.push_back(skyboxParameters.left.c_str());
    faces.push_back(skyboxParameters.top.c_str());
    faces.push_back(skyboxParameters.bottom.c_str());
    faces.push_back(skyboxParameters.back.c_str());
    faces.push_back(skyboxParameters.front.c_str());

    skyboxProgram_.create_program();
    skyboxProgram_.add_shader_from_file("Shaders/skyVert.glsl", GL_VERTEX_SHADER);
    skyboxProgram_.add_shader_from_file("Shaders/skyFrag.glsl", GL_FRAGMENT_SHADER);
    skyboxProgram_.link_program();

    glGenTextures(1, &textureID_);
    glActiveTexture(GL_TEXTURE0);

    SDL_Surface* image = nullptr;

    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID_);
    for (GLuint i = 0; i < faces.size(); i++)
    {
        image = IMG_Load(faces[i]);

        // Check for errors
        if (image == nullptr)
        {
            printf("Couldn't load image %s./nIMG_Error: %s", faces[i], IMG_GetError());
            break;
        }

        // Set pixel mode
        int pixelMode = GL_RGB;

        // Check for alpha component and set pixel mode appropriately
        if (image->format->BytesPerPixel == 4)
        {
            pixelMode = GL_RGBA;
        }

        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, pixelMode, image->w, image->h, 0, pixelMode, GL_UNSIGNED_BYTE, image->pixels);

        SDL_FreeSurface(image);
        image = nullptr;
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    // TODO: Load in a cube model here instead
    GLfloat skyboxVertices[] =
        {
            // Positions
            -1.0f, 1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f, -1.0f,

            -1.0f, -1.0f, 1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f, -1.0f, 1.0f,

            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,

            -1.0f, -1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, -1.0f, 1.0f,
            -1.0f, -1.0f, 1.0f,

            -1.0f, 1.0f, -1.0f,
            1.0f, 1.0f, -1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, -1.0f,

            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f, 1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f, 1.0f,
            1.0f, -1.0f, 1.0f
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

void Skybox::draw(glm::mat4 projectionMatrix, glm::mat4 viewMatrix) const
{
    glDepthFunc(GL_LEQUAL);

    skyboxProgram_.use();

    glm::mat4 view = glm::mat4(glm::mat3(viewMatrix));
    skyboxProgram_.set_uniform("projection", projectionMatrix);
    skyboxProgram_.set_uniform("view", view);

    skyboxVAO_.bind();

    glActiveTexture(GL_TEXTURE0);
    skyboxProgram_.set_uniform("skybox", 0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID_);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    skyboxVAO_.unbind();

    glDepthFunc(GL_LESS);
}

