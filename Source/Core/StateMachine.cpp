#include "StateMachine.h"

StateMachine::StateMachine(){}

StateMachine::~StateMachine()
{
    unload_all();
}

void StateMachine::change_state(ProgramState* state)
{
    // If there is a state, clean it up, and pop it off the stack
    if (!programStates_.empty())
    {
        programStates_.back()->finalize();
        delete programStates_.back();
        programStates_.back() = nullptr;
        programStates_.pop_back();
    }

    // Push on the new one and initialize it
    programStates_.push_back(state);
    programStates_.back()->initialize();
}

void StateMachine::unload_all()
{
    // Free all remaining game states
    while (!programStates_.empty())
    {
        if (programStates_.back() != nullptr)
        {
            delete programStates_.back();
            programStates_.back() = nullptr;
        }

        programStates_.pop_back();
    }
}

void StateMachine::push_state(ProgramState* state)
{
    // Pause state if there is one already on stack
    if (!programStates_.empty())
    {
        programStates_.back()->pause();
    }

    // Push state onto stack and initialize it
    programStates_.push_back(state);
    programStates_.back()->initialize();
}

void StateMachine::pop_state()
{
    if (!programStates_.empty())
    {
        // If somethings on the stack and finish up state then pop it off
        programStates_.back()->finalize();
        programStates_.pop_back();

        // If there's a state left, it is paused, so resume it
        programStates_.back()->resume();
    }
}

void StateMachine::update()
{
    programStates_.back()->update();
}

void StateMachine::draw()
{
    programStates_.back()->draw();
}

void StateMachine::handle_events()
{
    programStates_.back()->handle_events();
}

