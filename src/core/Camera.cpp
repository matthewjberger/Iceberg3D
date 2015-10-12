#include "Camera.h"
#include "Game.h"

Camera::Camera(vec3 pos)
{
    // Get game instance
    Game *game = Game::GetInstance();

    // Initialize variables
    position  = pos;
    direction = vec3(0, 0, 0);
    right     = vec3(0, 0, 0);
    up        = vec3(0, 0, 0);

    horizontalAngle  = float(pi<float>());
    verticalAngle    = 0.0f;
    initialFOV       = 45.0f;
    curFOV           = initialFOV;
    speed            = 0.70f;
    pitchSensitivity = 0.005f;
    yawSensitivity   = 0.005f;

    mouseX = game->GetScreenWidth() / 2;
    mouseY = game->GetScreenHeight() / 2;

    forward = false;

    // Set mouse to center of the screen
    SDL_WarpMouseInWindow(game->GetWindow(), game->GetScreenWidth() / 2, game->GetScreenHeight() / 2);

    // Hide the mouse
    SDL_ShowCursor(SDL_DISABLE);
}

Camera::~Camera()
{
}

void Camera::Update()
{
    projectionMatrix = mat4(1.0f);
    viewMatrix       = mat4(1.0f);

    // Grab the game instance
    Game *game = Game::GetInstance();

    // Get keyboard state
    const Uint8 *keystates = SDL_GetKeyboardState(NULL);

    // Hide the mouse
    SDL_ShowCursor(SDL_DISABLE);

    // If the mouse moved
    SDL_GetMouseState(&mouseX, &mouseY);

    // Reset mouse to center of the screen
    SDL_WarpMouseInWindow(game->GetWindow(), game->GetScreenWidth() / 2, game->GetScreenHeight() / 2);

    // Update angles
    horizontalAngle += yawSensitivity  * float((game->GetScreenWidth() / 2) - mouseX);
    verticalAngle   += pitchSensitivity* float((game->GetScreenHeight() / 2) - mouseY);

    // 1.55f radians is 89 degrees, which is a reasonable vertical constraint
    if(verticalAngle > 1.55f)
        verticalAngle = 1.55f;
    else if(verticalAngle < -1.55f)
        verticalAngle = -1.55f;

    // Set new direction by converting spherical coordinates to cartesian
    direction = vec3(
            cos(verticalAngle) * sin(horizontalAngle),
            sin(verticalAngle),
            cos(verticalAngle) * cos(horizontalAngle)
            );

    // Calculate right vector
    right = vec3(
            sin(horizontalAngle - pi<float>() / 2),
            0,
            cos(horizontalAngle - pi<float>() / 2)
            );

    // Calculate up vector
    up = cross(right, direction);

    // Move forward if 'W' is pressed
    if (keystates[SDL_SCANCODE_W])
    {
        position += direction*speed;
    }

    // Move backward if 'S' is pressed
    if (keystates[SDL_SCANCODE_S])
    {
        position -= direction*speed;
    }

    // Strafe left if 'D' is pressed
    if (keystates[SDL_SCANCODE_D])
    {
        position += right*speed;
    }

    // Strafe right if 'A' is pressed
    if (keystates[SDL_SCANCODE_A])
    {
        position -= right*speed;
    }

    projectionMatrix = perspective(initialFOV, Game::GetInstance()->GetAspectRatio(), 0.1f, 1000.0f);
    viewMatrix       = lookAt(position, position + direction, up);
}

float Camera::GetPitchSensitivity()
{
    return pitchSensitivity;
}

float Camera::GetYawSensitivity()
{
    return yawSensitivity;
}

void Camera::SetPitchSensitivity(float newSens)
{
    pitchSensitivity = newSens;
}

void Camera::SetYawSensitivity(float newSens)
{
    yawSensitivity = newSens;
}

glm::mat4 Camera::GetMVP(glm::mat4 &modelMatrix)
{
    glm::mat4 mvpMatrix = projectionMatrix * viewMatrix * modelMatrix;
    return mvpMatrix;
}

