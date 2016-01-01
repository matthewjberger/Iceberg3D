#include "IntroState.h"
#include "../core/GlobalIncludes.h"
void IntroState::Pause() {}
void IntroState::Resume() {}
IntroState *IntroState::inst = 0;

void IntroState::Initialize()
{
}

void IntroState::Finalize()
{
}

void IntroState::HandleEvents()
{
}

void IntroState::Update()
{
}

void IntroState::Draw()
{
	// Clear the screen to Cornflower Blue
	glClearColor(0.392, 0.584, 0.93, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
