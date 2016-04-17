#include "Game.h"

using namespace std;
using namespace glm;

#include <stb_image.h>

Game::Game()
    :stateMachine(make_unique<StateMachine>())
{
    // Initialize game variables and settings
    fullscreen_ = true;

    caption_ = "Iceberg3D";
    iconPath_ = "assets/icebergIcon.png";

    screenWidth_ = 1376;
    screenHeight_ = 768;

    majorVersion_ = 4;
    minorVersion_ = 3;

    fps_ = 60;

    window_ = nullptr;

    // Begin the timer for delta time calculation
    previousTime = std::chrono::high_resolution_clock::now();
}

Game::~Game()
{
    glfwTerminate();
}

bool Game::initialize()
{
    // Initialize SDL
    if (glfwInit() == GL_FALSE)
    {
        printf("GLFW could not be initialized!");
        return false;
    }
    else
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVersion_);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVersion_);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
        window_ = glfwCreateWindow(screenWidth_, screenHeight_, caption_.c_str(), nullptr, nullptr);
        if(window_ == nullptr)
        {
            printf("Error: Failed to create OpenGL context!\n");
            return false;
        }

        glfwMakeContextCurrent(window_);
        gladLoadGL();
        printf("OpenGL version: %p\n", glGetString(GL_VERSION));

        int x, y, c;
        GLFWimage image; 
        image.pixels = stbi_load(iconPath_.c_str(), &x, &y, &c, 0);
        image.width = x;
        image.height = y;
        if(image.pixels != NULL)
        {
            glfwSetWindowIcon(window_, 1, &image);
        }
        else
        {
            printf("Failed to load icon: %s", iconPath_.c_str());
        }

        // Additional settings
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
    }

    return true;
}

void Game::change_state(GameState* state) const
{
    stateMachine->change_state(state);
}

void Game::update() const
{
    stateMachine->update();
}

void Game::draw() const
{
    // Clear the screen to Cornflower Blue
    glClearColor(0.392f, 0.584f, 0.93f, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    stateMachine->draw();

    // Update the window
    glfwSwapBuffers(window_);
}

void Game::handle_events() const
{
    // TODO: Make a component base class
    // TODO: Make a derived InputComponent class and use it here
    glfwPollEvents();

    if(glfwGetKey(window_, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        exit();
    }

    stateMachine->handle_events();
}

void Game::toggle_fullscreen()
{
    if (fullscreen_ == false)
    {
        // Set fullscreen

        fullscreen_ = true;
    }
    else if (fullscreen_ == true)
    {
        // Set windowed

        fullscreen_ = false;
    }
}

bool Game::running() const
{
    return !glfwWindowShouldClose(window_);
}

int Game::fps() const
{
    return fps_;
}

GLFWwindow* Game::window() const
{
    return window_;
}

glm::vec2 Game::screen_dimensions() const
{
    return glm::vec2(screenWidth_, screenHeight_);
}

void Game::exit() const
{
    glfwSetWindowShouldClose(window_, true);
}

float Game::time_delta()
{
    currentTime = std::chrono::high_resolution_clock::now();
    float returnValue = std::chrono::duration_cast<std::chrono::duration<float>>(currentTime - previousTime).count();
    previousTime = std::chrono::high_resolution_clock::now();

    return returnValue;
}

float Game::aspect_ratio() const
{
    // Prevent division by 0
    float width = float(screenWidth_);
    float height = float(screenHeight_);
    return (height == 0) ? (width) : (width / height);
}