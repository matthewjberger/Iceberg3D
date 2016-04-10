#include "Camera.h"
#include "Game.h"

using namespace std;
using namespace glm;

Camera::Camera(Game* game, vec3 position_, glm::vec3 focusPoint, float speed_)
{
    // Initialize variables
    direction_ = vec3(0, 0, 0);
    right_ = vec3(0, 0, 0);
    up_ = vec3(0, 0, 0);

    horizontalAngle_ = float(pi<float>());
    verticalAngle_ = 0.0f;
    initialFOV_ = 45.0f;
    this->speed_ = speed_;
    pitchSensitivity_ = 0.005f;
    yawSensitivity_ = 0.005f;

    mouseX_ = game->screen_dimensions().x / 2;
    mouseY_ = game->screen_dimensions().y / 2;

    inputEnabled_ = false;

    calculate_vectors(game, mouseX_, mouseY_);
    LookAt(game, position_, focusPoint, up_);
}

// Calculate direction_, right_, and up_ vectors based on mouse offsets interpreted as angles
void Camera::calculate_vectors(Game* game, int mouseX_, int mouseY_)
{
    // up_date angles
    horizontalAngle_ += yawSensitivity_ * float((game->screen_dimensions().x / 2) - mouseX_);
    verticalAngle_ += pitchSensitivity_ * float((game->screen_dimensions().y / 2) - mouseY_);

    // 1.55f radians is 89 degrees, which is a reasonable vertical constraint
    if (verticalAngle_ > 1.55f)
        verticalAngle_ = 1.55f;
    else if (verticalAngle_ < -1.55f)
        verticalAngle_ = -1.55f;

    // Set new direction_ by converting spherical coordinates to Cartesian
    direction_ = vec3(
        cos(verticalAngle_) * sin(horizontalAngle_),
        sin(verticalAngle_),
        cos(verticalAngle_) * cos(horizontalAngle_)
    );

    // Calculate right_ vector
    right_ = vec3(
        sin(horizontalAngle_ - pi<float>() / 2),
        0,
        cos(horizontalAngle_ - pi<float>() / 2)
    );

    // Calculate up_ vector
    up_ = cross(right_, direction_);
}

void Camera::update(Game *game)
{
    if (!inputEnabled_) return;

    // Hide the mouse
    glfwSetInputMode(game->window(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    // If the mouse moved
    glfwGetCursorPos(game->window(), &mouseX_, &mouseY_);

    // Reset mouse to center of the screen
    glfwSetCursorPos(game->window(), game->screen_dimensions().x/2, game->screen_dimensions().y/2);

    // Calculate up_, right_, and direction_ vectors
    calculate_vectors(game, mouseX_, mouseY_);

    // Move forward if 'W' is pressed
    if (glfwGetKey(game->window(), GLFW_KEY_W))
    {
        position_ += direction_ * speed_;
    }

    // Move backward if 'S' is pressed
    if (glfwGetKey(game->window(), GLFW_KEY_S))
    {
        position_ -= direction_ * speed_;
    }

    // Strafe left if 'D' is pressed
    if (glfwGetKey(game->window(), GLFW_KEY_D))
    {
        position_ += right_ * speed_;
    }

    // Strafe right_ if 'A' is pressed
    if (glfwGetKey(game->window(), GLFW_KEY_A))
    {
        position_ -= right_ * speed_;
    }

    projectionMatrix_ = perspective(initialFOV_, game->aspect_ratio(), 0.1f, 1000.0f);
    viewMatrix_ = lookAt(position_, position_ + direction_, up_);
}

float Camera::pitch() const
{
    return pitchSensitivity_;
}

float Camera::yaw() const
{
    return yawSensitivity_;
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

void Camera::LookAt(Game *game, glm::vec3 position_, glm::vec3 focusPoint, glm::vec3 up_)
{
    this->projectionMatrix_ = perspective(initialFOV_, game->aspect_ratio(), 0.1f, 1000.0f);
    this->position_ = position_;
    this->viewMatrix_ = glm::lookAt(position_, focusPoint, up_);
}

glm::mat4 Camera::projection_matrix() const
{
    return projectionMatrix_;
}

glm::mat4 Camera::view_matrix() const
{
    return viewMatrix_;
}

