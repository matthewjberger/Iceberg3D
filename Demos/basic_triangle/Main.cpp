#include "ExampleState.h"

int main()
{
    // Create Game and example program state
    std::unique_ptr<iceberg::Game> game = std::make_unique<iceberg::Game>(iceberg::OPENGL);
    std::unique_ptr<ExampleState> Example = std::make_unique<ExampleState>(game.get());

    auto window = game->window_manager()->create_window("Iceberg3D", 640, 480);
    window->set_caption("Iceberg3D Engine - OpenGL Version: " + game->window_manager()->api_version_string());
    window->set_icon("assets/icon.png");
    game->change_state(Example.get());
    game->run();

    return 0;
}