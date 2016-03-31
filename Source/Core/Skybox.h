#ifndef SKYBOX_H
#define SKYBOX_H

#include "GlobalIncludes.h"
#include "VAO.h"
#include "VBO.h"
#include "ShaderProgram.h"

struct SkyboxParameters
{
    std::string left;
    std::string right;
    std::string top;
    std::string bottom;
    std::string front;
    std::string back;
};

class Skybox
{
public:
    Skybox(const SkyboxParameters &skyboxParameters);
    ~Skybox();

    void draw(glm::mat4 projectionMatrix, glm::mat4 viewMatrix) const;

private:
    VAO skyboxVAO_;
    VBO skyboxVBO_;
    ShaderProgram skyboxProgram_;
    GLuint textureID_;
};

#endif

