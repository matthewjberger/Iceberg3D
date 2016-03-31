#ifndef STATEMACHINE_H
#define STATEMACHINE_H
#include <vector>

class ProgramState
{
public:
    virtual ~ProgramState() {};

    virtual void initialize() = 0;
    virtual void finalize() = 0;

    virtual void pause() = 0;
    virtual void resume() = 0;

    virtual void handle_events() = 0;
    virtual void draw() = 0;
    virtual void update() = 0;
};

class StateMachine
{
public:
    StateMachine();
    ~StateMachine();

    void update();
    void draw();
    void handle_events();

    void change_state(ProgramState* state);
    void push_state(ProgramState* state);
    void pop_state();

    void unload_all();

private:
    std::vector<ProgramState *> programStates_;
};

#endif