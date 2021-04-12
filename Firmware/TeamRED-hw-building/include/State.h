
#ifndef STATE_H
#define STATE_H

#include "Statemachine.h"
#include "StateInitVariables.h"
#include "Event.h"
#include <RF24.h>

class Statemachine;


class State
{
protected:
    Statemachine *_statemachine;
    RF24 *radio;
    bool _isBase;

public:
    void on_init(StateInitVariables stateInitVariables)
    {
        this->_statemachine = stateInitVariables.statemachine;
        this->_isBase = stateInitVariables.isBase;
        this->radio = stateInitVariables.radio;
    }
    virtual void on_start();
    virtual void on_execute();
    virtual void on_event(Event e);
    virtual void on_exit();

    State()
    {
    }

    ~State()
    {
    }
};

#endif //
