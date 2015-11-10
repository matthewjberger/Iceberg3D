#include "Skybox.h"

using namespace std;
using namespace glm;

Skybox::Skybox(string right, string left, string top, string bottom, string back, string front)
{
    vector<const GLchar*> faces;
    faces.push_back(right.c_str());
    faces.push_back(left.c_str());
    faces.push_back(top.c_str());
    faces.push_back(bottom.c_str());
    faces.push_back(back.c_str());
    faces.push_back(front.c_str());

    skyboxProgram.CreateProgram();
    skyboxProgram.AddShaderFromFile("Shaders/skyVert.glsl", GL_VERTEX_SHADER);
    skyboxProgram.AddShaderFromFile("Shaders/skyFrag.glsl", GL_FRAGMENT_SHADER);
    skyboxProgram.LinkProgram();

    glGenTextures(1, &textureID);
    glActiveTexture(GL_TEXTURE0);

    SDL_Surface* image = NULL;

    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    for(GLuint i = 0; i < faces.size(); i++)
    {
        image = IMG_Load(faces[i]);

        // Check for errors
        if (image == NULL)
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
        image = NULL;

    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

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

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
        1.0f,  1.0f, -1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f,  1.0f
    };

    skyboxVAO.Create();
    skyboxVBO.Create();

    skyboxVAO.Bind();
    skyboxVBO.Bind();

    skyboxVBO.AddData(&skyboxVertices, sizeof(skyboxVertices));
    skyboxVBO.UploadData();

    skyboxVAO.EnableAttribute(0);
    skyboxVAO.ConfigureAttribute(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (GLvoid*)0);
    skyboxVAO.Unbind();

}

Skybox::~Skybox()
{
}

void Skybox::Draw(glm::mat4 projectionMatrix, glm::mat4 viewMatrix)
{
    glDepthFunc(GL_LEQUAL);

    skyboxProgram.UseProgram();

    glm::mat4 view = glm::mat4(glm::mat3(viewMatrix));
    skyboxProgram.SetUniform("projection", projectionMatrix);
    skyboxProgram.SetUniform("view", view);

    skyboxVAO.Bind();

    glActiveTexture(GL_TEXTURE0);
    skyboxProgram.SetUniform("skybox", 0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    skyboxVAO.Unbind();

    glDepthFunc(GL_LESS);
}

