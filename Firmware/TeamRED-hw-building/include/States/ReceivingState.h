#ifndef RECEIVINGSTATE_H
#define RECEIVINGSTATE_H

#include "State.h"
#include "StateInitVariables.h"
#include "Event.h"

class ReceivingState : public State
{
private:

public:
    void on_init(StateInitVariables stateInitVariables);
    void on_start();
    void on_execute();
    void on_event(Event e);
    void on_exit();
};

#endif // RECEIVINGSTATE_H