#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "State.h"
#include "tokenprotocol.h"
#include "Event.h"
#include <Arduino.h>

#define NumberOfStates 5

enum StateNumber {INIT, SENDING, RECEIVING, SLEEP, REMOVEDTOP};

class State;

class Statemachine
{
public:
    static Statemachine *instance()
    {
        if (_instance == 0)
        {
            _instance = new Statemachine();
        }

        return _instance;
    }

private:
    static Statemachine *_instance;

    StateNumber _currentState;
    State *states[NumberOfStates];

public:
    void on_init();
    void on_execute();
    void handle_event(Event e);

    void setState(StateNumber state);

    Statemachine();
    ~Statemachine();
};

#endif // STATEMACHINE_H