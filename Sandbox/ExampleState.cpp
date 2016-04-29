#include "ExampleState.h"
#include "GlobalIncludes.h"

using namespace iceberg;

void ExampleState::pause() {}
void ExampleState::resume() {}
void ExampleState::finalize() {}
void ExampleState::handle_events() {}

void ExampleState::initialize()
{
	/* Initialize state items */
    textManager = new TextManager(game_);
    textManager->load_font("c:/windows/fonts/arialbd.ttf", 48);
}

void ExampleState::update()
{
	/* Update state items */
}

void ExampleState::draw()
{
	/* Render state items */
    textManager->RenderText("Matthew Berger", 30, 120);
}