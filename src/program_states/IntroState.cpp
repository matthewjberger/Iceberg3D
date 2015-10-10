#include "IntroState.h"
#include "../core/GlobalIncludes.h"
void IntroState::Pause(){}
void IntroState::Resume(){}
IntroState *IntroState::inst = 0;

void IntroState::Initialize()
{
    // Initialize resources
}

void IntroState::Finalize()
{
    // Free resources
}

void IntroState::HandleEvents()
{
    // Handle input logic
}

void IntroState::Update()
{
    // Update logic
}

void IntroState::Draw()
{
    // Render logic
    // Clear the screen
    glClearColor(0.3f, 0.5f, 1.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


