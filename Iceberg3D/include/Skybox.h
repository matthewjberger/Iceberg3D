#ifndef SKYBOX_H
#define SKYBOX_H

#include "GlobalIncludes.h"
#include "VAO.h"
#include "Buffer.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "Camera.h"

namespace iceberg
{
    struct ICEBERGAPI SkyboxParameters
    {
        std::string left;
        std::string right;
        std::string top;
        std::string bottom;
        std::string front;
        std::string back;
    };

    class ICEBERGAPI Skybox
    {
    public:
        Skybox(const SkyboxParameters &skyboxParameters);
        ~Skybox();

        void draw(glm::mat4 projectionMatrix, glm::mat4 viewMatrix) const;

    private:
        std::shared_ptr<VAO> skyboxVAO_;
        std::shared_ptr<Buffer> skyboxVBO_;
        std::shared_ptr<ShaderProgram> skyboxProgram_;
        std::shared_ptr<Texture> cubemap_;
    };
}
#endif