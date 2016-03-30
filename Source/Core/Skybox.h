#ifndef SKYBOX_H
#define SKYBOX_H

#include "GlobalIncludes.h"
#include "VAO.h"
#include "VBO.h"
#include "ShaderProgram.h"

class Skybox
{
public:
    Skybox(std::string right, std::string left, std::string top, std::string bottom, std::string back, std::string front);
    ~Skybox();

    void draw(glm::mat4 projectionMatrix, glm::mat4 viewMatrix) const;

private:
    VAO skyboxVAO_;
    VBO skyboxVBO_;
    ShaderProgram skyboxProgram_;
    GLuint textureID_;
};

#endif

