#ifndef __SKYBOX_H
#define __SKYBOX_H

#include "GlobalIncludes.h"
#include "VAO.h"
#include "VBO.h"
#include "ShaderProgram.h"

class Skybox
{
    public:
        Skybox(string right, string left, string top, string bottom, string back, string front);
        ~Skybox();

        void Draw(glm::mat4 projectionMatrix, glm::mat4 viewMatrix);

    private:
        VAO skyboxVAO;
        VBO skyboxVBO;
        ShaderProgram skyboxProgram;
        GLuint textureID;

};

#endif
