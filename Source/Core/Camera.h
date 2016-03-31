#ifndef CAMERA_H
#define CAMERA_H

#include "Game.h"

class Camera
{
public:

    Camera(Game* game, glm::vec3 position = glm::vec3(0.0f), glm::vec3 focusPoint = glm::vec3(0.0f), float speed = 0.7);

    ~Camera(){}

    void update(Game *game);

    void enable_input(bool enabled = true);

    glm::mat4 make_mvp(glm::mat4 modelMatrix) const;
    glm::mat4 projection_matrix() const;
    glm::mat4 view_matrix() const;

    float pitch() const;
    float yaw() const;

    void LookAt(Game* game, glm::vec3 position, glm::vec3 focusPoint, glm::vec3 up);

private:

    void calculate_vectors(Game* game, int mouseX, int mouseY);

    bool inputEnabled_;

    glm::mat4 projectionMatrix_;
    glm::mat4 viewMatrix_;

    glm::vec3 position_;
    glm::vec3 direction_;
    glm::vec3 right_;
    glm::vec3 up_;

    float horizontalAngle_;
    float verticalAngle_;

    float initialFOV_;
    float curFOV_;

    float speed_;
    float pitchSensitivity_;
    float yawSensitivity_;

    int mouseX_;
    int mouseY_;
};

#endif

