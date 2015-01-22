#include "CCamera.h"
#include "CoreGame.h"

Camera::Camera(vec3 pos)
{
	// Get game instance
	Game *game = Game::GetInstance();

	// Initialize variables
	position  = pos;
	direction = vec3(0, 0, 0);
	right     = vec3(0, 0, 0);
	up        = vec3(0, 0, 0);

	horizontalAngle = float(PI);
	verticalAngle = 0.0f;

	initialFOV = 45.0f;
	curFOV = initialFOV;

	speed = 0.70f;

	pitchSensitivity = 0.0005f;
	yawSensitivity = 0.0005f;

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

void Camera::Update(mat4 &Projection, mat4 &ModelView)
{
	Projection = mat4(1.0f);
	ModelView = mat4(1.0f);

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
	verticalAngle += pitchSensitivity* float((game->GetScreenHeight() / 2) - mouseY);
	
	// Set new direction by converting spherical coordinates to cartesian
	direction = vec3(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
		);

	// Calculate right vector
	right = vec3(
		sin(horizontalAngle - PI / 2),
		0,
		cos(horizontalAngle - PI / 2)
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

	Projection = perspective(initialFOV, 4.0f / 3.0f, 0.1f, 1000.0f);
	ModelView = lookAt(position, position + direction, up);
}