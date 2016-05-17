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

    // HACK: This casting will be removed when the input abstraction is created
    auto glWindow = static_cast<icebergGL::GLWindow*>(game->window_manager()->current_window());
    if (!glWindow) return;
    auto window = glWindow->handle();
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    glfwSetCursorPos(window, game->window_manager()->current_window()->width() / 2, game->window_manager()->current_window()->height() / 2);

    calculate_vectors(game);
    LookAt(game, position_, focusPoint, up_);
}

void Camera::calculate_vectors(Game* game)
{
    auto glWindow = static_cast<icebergGL::GLWindow*>(game->window_manager()->current_window());
    auto window = glWindow->handle();
 
    glfwGetCursorPos(window, &mouseX_, &mouseY_);
    glfwSetCursorPos(window, game->window_manager()->current_window()->width() / 2, game->window_manager()->current_window()->height() / 2);

    float width = glWindow->width() / 2;
    float height = glWindow->height() / 2;

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

    // HACK: This casting will be removed when the input abstraction is created
    auto glWindow = static_cast<icebergGL::GLWindow*>(game->window_manager()->current_window());
    if (!glWindow) return;
    auto window = glWindow->handle();

    calculate_vectors(game);

    // Move forward
    if (glfwGetKey(window, GLFW_KEY_W))
    {
        position_ += direction_ * speed_ * game->delta_time();
    }

    // Move backward
    if (glfwGetKey(window, GLFW_KEY_S))
    {
        position_ -= direction_ * speed_ * game->delta_time();
    }

    // Strafe left
    if (glfwGetKey(window, GLFW_KEY_D))
    {
        position_ += right_ * speed_ * game->delta_time();
    }

    // Strafe right
    if (glfwGetKey(window, GLFW_KEY_A))
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

