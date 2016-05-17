#include "Camera.h"
#include "Game.h"
#include <GLWindow.h>

using namespace iceberg;
   
Camera::Camera(Game* game, glm::vec3 position, glm::vec3 focusPoint, float speed)
{
    // Initialize variables
    direction_ = glm::vec3(0, 0, 0);
    right_ = glm::vec3(0, 0, 0);
    up_ = glm::vec3(0, 0, 0);

    speed_ = speed;
    position_ = position;

    fieldOfView_ = 45.0f;
    pitchSensitivity_ = 0.005f;
    yawSensitivity_ = 0.005f;

    horizontalAngle_ = glm::pi<float>();
    verticalAngle_ =  0.0f;

    nearClippingPlane_ = 0.1f;
    farClippingPlane_ = 10000.0f;
 
    mouseX_ = game->window_manager()->current_window()->width() / 2;
    mouseY_ = game->window_manager()->current_window()->height() / 2;

    inputEnabled_ = false;

    InputManager* inputManager = game->window_manager()->input_manager();
    inputManager->hide_cursor();
    inputManager->set_cursor_pos(game->window_manager()->current_window()->width()/2, game->window_manager()->current_window()->height()/2);

    calculate_vectors(game, inputManager);
    LookAt(game, position_, focusPoint, up_);
}

void Camera::calculate_vectors(Game* game)
{
    InputManager* inputManager = game->window_manager()->input_manager();
    inputManager->get_cursor_pos(&mouseX_, &mouseY_);
    inputManager->set_cursor_pos(game->window_manager()->current_window()->width()/2, game->window_manager()->current_window()->height()/2);

    float width = game->window_manager()->current_window()->width() / 2;
    float height = game->window_manager()->current_window()->height() / 2;

    horizontalAngle_ += yawSensitivity_ * float(width - mouseX_);
    verticalAngle_ += pitchSensitivity_ * float(height - mouseY_);

    // 1.55f radians is 89 degrees, which is a reasonable vertical constraint
    if (verticalAngle_ > 1.55f)
        verticalAngle_ = 1.55f;
    else if (verticalAngle_ < -1.55f)
        verticalAngle_ = -1.55f;

    direction_ = glm::vec3(
        cos(verticalAngle_) * sin(horizontalAngle_),
        sin(verticalAngle_),
        cos(verticalAngle_) * cos(horizontalAngle_)
    );

    right_ = glm::vec3(
        sin(horizontalAngle_ - glm::pi<float>() / 2),
        0,
        cos(horizontalAngle_ - glm::pi<float>() / 2)
    );

    up_ = cross(right_, direction_);
}

void Camera::update(Game *game)
{
    if (!inputEnabled_) return;

    InputManager* inputManager = game->window_manager()->input_manager();

    calculate_vectors(game, inputManager);

    // Move forward
    if (inputManager->key_pressed('w'))
    {
        position_ += direction_ * speed_ * game->delta_time();
    }

    // Move backward
    if (inputManager->key_pressed('s'))
    {
        position_ -= direction_ * speed_ * game->delta_time();
    }

    // Strafe left
    if (inputManager->key_pressed('a'))
    {
        position_ += right_ * speed_ * game->delta_time();
    }

    // Strafe right
    if (inputManager->key_pressed('d'))
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
    projectionMatrix_ = glm::perspective(fieldOfView_, game->window_manager()->current_window()->aspect_ratio(), nearClippingPlane_, farClippingPlane_);
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

