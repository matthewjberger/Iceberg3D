#ifndef CAMERA_H
#define CAMERA_H

#include "Game.h"

namespace iceberg
{
    class ICEBERGAPI Camera
    {
    public:

        Camera(Game* game, glm::vec3 position = glm::vec3(0.0f), glm::vec3 focusPoint = glm::vec3(0.0f), float speed = 0.7);
        ~Camera() {}

        void update(Game *game);
        void enable_input(bool enabled = true);
        glm::mat4 make_mvp(glm::mat4 modelMatrix) const;
        glm::mat4 projection_matrix() const;
        glm::mat4 view_matrix() const;

        void LookAt(Game* game, glm::vec3 position, glm::vec3 focusPoint, glm::vec3 up);

    private:

        void calculate_vectors(Game* game);

        bool inputEnabled_;

        glm::mat4 projectionMatrix_;
        glm::mat4 viewMatrix_;

        glm::vec3 position_;
        glm::vec3 direction_;
        glm::vec3 right_;
        glm::vec3 up_;

        float speed_;

        float horizontalAngle_;
        float verticalAngle_;

        float fieldOfView_;

        float pitchSensitivity_;
        float yawSensitivity_;

        float nearClippingPlane_;
        float farClippingPlane_;

        double mouseX_;
        double mouseY_;
    };
}
#endif

