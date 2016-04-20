#include "Camera.h"
#include "Game.h"

using namespace std;
using namespace glm;

Camera::Camera(Game* game, vec3 position, glm::vec3 focusPoint, float speed)
{
    // Initialize variables
    direction_ = vec3(0, 0, 0);
    right_ = vec3(0, 0, 0);
    up_ = vec3(0, 0, 0);

    speed_ = speed;
    position_ = position;

    fieldOfView_ = 45.0f;
    pitchSensitivity_ = 0.005f;
    yawSensitivity_ = 0.005f;

    horizontalAngle_ = pi<float>();
    verticalAngle_ =  0.0f;

    nearClippingPlane_ = 0.1f;
    farClippingPlane_ = 10000.0f;
 
    mouseX_ = game->screen_dimensions().x / 2;
    mouseY_ = game->screen_dimensions().y / 2;

    inputEnabled_ = false;

    glfwSetInputMode(game->window(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    glfwSetCursorPos(game->window(), game->screen_dimensions().x / 2, game->screen_dimensions().y / 2);

    calculate_vectors(game);
    LookAt(game, position_, focusPoint, up_);
}

void Camera::calculate_vectors(Game* game)
{
    glfwGetCursorPos(game->window(), &mouseX_, &mouseY_);
    glfwSetCursorPos(game->window(), game->screen_dimensions().x/2, game->screen_dimensions().y/2);

    horizontalAngle_ += yawSensitivity_ * float((game->screen_dimensions().x / 2) - mouseX_);
    verticalAngle_ += pitchSensitivity_ * float((game->screen_dimensions().y / 2) - mouseY_);

    // 1.55f radians is 89 degrees, which is a reasonable vertical constraint
    if (verticalAngle_ > 1.55f)
        verticalAngle_ = 1.55f;
    else if (verticalAngle_ < -1.55f)
        verticalAngle_ = -1.55f;

    direction_ = vec3(
        cos(verticalAngle_) * sin(horizontalAngle_),
        sin(verticalAngle_),
        cos(verticalAngle_) * cos(horizontalAngle_)
    );

    right_ = vec3(
        sin(horizontalAngle_ - pi<float>() / 2),
        0,
        cos(horizontalAngle_ - pi<float>() / 2)
    );

    up_ = cross(right_, direction_);
}

void Camera::update(Game *game)
{
    if (!inputEnabled_) return;

    calculate_vectors(game);

    // Move forward
    if (glfwGetKey(game->window(), GLFW_KEY_W))
    {
        position_ += direction_ * speed_ * game->delta_time();
    }

    // Move backward
    if (glfwGetKey(game->window(), GLFW_KEY_S))
    {
        position_ -= direction_ * speed_ * game->delta_time();
    }

    // Strafe left
    if (glfwGetKey(game->window(), GLFW_KEY_D))
    {
        position_ += right_ * speed_ * game->delta_time();
    }

    // Strafe right
    if (glfwGetKey(game->window(), GLFW_KEY_A))
    {
        position_ -= right_ * speed_ * game->delta_time();
    }

    LookAt(game, position_, position_ + direction_, up_);
}

glm::mat4 Camera::make_mvp(glm::mat4 modelMatrix) const
{
    glm::mat4 mvpMatrix = projectionMatrix_ * viewMatrix_ * modelMatrix;
    return mvpMatrix;
}

void Camera::enable_input(bool enabled)
{
    inputEnabled_ = enabled;
}

void Camera::LookAt(Game *game, glm::vec3 position, glm::vec3 focusPoint, glm::vec3 up)
{
    projectionMatrix_ = perspective(fieldOfView_, game->aspect_ratio(), nearClippingPlane_, farClippingPlane_);
    position_ = position;
    viewMatrix_ = glm::lookAt(position_, focusPoint, up_);
}

glm::mat4 Camera::projection_matrix() const
{
    return projectionMatrix_;
}

glm::mat4 Camera::view_matrix() const
{
    return viewMatrix_;
}

