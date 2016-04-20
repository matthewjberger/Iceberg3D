#include "Game.h"

using namespace std;
using namespace glm;

#include <stb_image.h>

GLFWwindow* Game::window_;

Game::Game()
    :stateMachine_(make_unique<StateMachine>())
{
    // Initialize game variables and settings
    fullscreen_ = true;

    caption_ = "Iceberg3D";
    iconPath_ = "assets/icebergIcon.png";

    screenWidth_ = 1024;
    screenHeight_ = 768;

    glMajorVersion_ = 4;
    glMinorVersion_ = 5;

    majorVersion_ = 0;
    minorVersion_ = 1;
    patchVersion_ = 0;

    fps_ = 60;

    window_ = nullptr;

    // Begin the timer for delta time calculation
    previousTime_ = std::chrono::high_resolution_clock::now();
}

Game::~Game()
{
    glfwTerminate();
}

bool Game::create_window()
{
    // TODO: Possibly store detected version in a configuration file

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    auto TryVersion = [this](int major, int minor)
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);

        window_ = glfwCreateWindow(screenWidth_, screenHeight_, caption_.c_str(), nullptr, nullptr);
        if (window_ != nullptr)
        {
            glMajorVersion_ = major;
            glMinorVersion_ = minor;

            return true;
        }

        return false;
    };

    // OpenGL 4.5 - 4.0
    for (int minorVersion = 5; minorVersion >= 0; minorVersion--)
    {
        if (TryVersion(4, minorVersion)) return true;
    }
    
    // OpenGL 3.3 Core
    if (TryVersion(3, 3)) return true;

    // Failed to create an OpenGL context
    return false;
}

bool Game::initialize()
{
    // Initialize SDL
    if (glfwInit() == GL_FALSE)
    {
        handle_error("GLFW could not be initialized!");
        return false;
    }
    else
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, glMajorVersion_);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, glMinorVersion_);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
        if(!create_window())
        {
            handle_error("Error: Failed to create OpenGL context!");
            return false;
        }

        glfwMakeContextCurrent(window_);
        gladLoadGL();

        build_caption();

        // Additional settings
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
    }

    return true;
}

void Game::build_caption() const
{
    // Program Version
    string programVersion =  to_string(majorVersion_) + "."
                           + to_string(minorVersion_) + "."
                           + to_string(patchVersion_);

    // OpenGL Version
    string glVersion = (const char*)glGetString(GL_VERSION);
    string fullCaption = caption_ + " - Version: " + programVersion 
                                  + " - OpenGL Version: " + glVersion;

    glfwSetWindowTitle(window_, fullCaption.c_str());

    // Caption
    int x, y, c;
    GLFWimage image;
    image.pixels = stbi_load(iconPath_.c_str(), &x, &y, &c, 0);
    image.width = x;
    image.height = y;
    if (image.pixels != NULL)
    {
        glfwSetWindowIcon(window_, 1, &image);
    }
    else
    {
        string errorMessage = "Failed to load icon: " + iconPath_;
        handle_error(errorMessage.c_str());
    }
}

void Game::change_state(GameState* state) const
{
    stateMachine_->change_state(state);
}

void Game::update()
{
    currentTime_ = std::chrono::high_resolution_clock::now();
    deltaTime_ = std::chrono::duration_cast<std::chrono::duration<float>>(currentTime_ - previousTime_).count();
    previousTime_ = std::chrono::high_resolution_clock::now();

    stateMachine_->update();
}

void Game::draw() const
{
    // Clear the screen to Cornflower Blue
    glClearColor(0.392f, 0.584f, 0.93f, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    stateMachine_->draw();

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

    stateMachine_->handle_events();
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

bool Game::running()
{
    return !glfwWindowShouldClose(window_);
}

int Game::fps() const
{
    return fps_;
}

GLFWwindow* Game::window()
{
    return window_;
}

glm::vec2 Game::screen_dimensions() const
{
    return glm::vec2(screenWidth_, screenHeight_);
}

void Game::exit()
{
    if (window_ == NULL) return;
    glfwSetWindowShouldClose(window_, true);
}

float Game::delta_time() const
{
   return deltaTime_;
}

float Game::aspect_ratio() const
{
    // Prevent division by 0
    float width = float(screenWidth_);
    float height = float(screenHeight_);
    glfwSetWindowAspectRatio(window_, width, height);
    return(height == 0) ? (width) : (width / height);
}

void Game::handle_error(std::string errorMessage)
{
    boxer::show(errorMessage.c_str(), "Error", boxer::Style::Warning);
    exit();
}
