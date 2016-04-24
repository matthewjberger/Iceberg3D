#ifndef SKYBOX_H
#define SKYBOX_H

#include "GlobalIncludes.h"
#include "VAO.h"
#include "VBO.h"
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

        void draw(const Camera* camera) const;

    private:
        VAO skyboxVAO_;
        VBO skyboxVBO_;

        ShaderProgram skyboxProgram_;
        std::unique_ptr<Texture> cubemap_;
    };
}
#endif