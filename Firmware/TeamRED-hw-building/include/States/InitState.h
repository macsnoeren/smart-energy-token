#ifndef INITSTATE_H
#define INITSTATE_H

#include "State.h"


class InitState : public State
{
private:
public:
    void on_init(StateInitVariables stateInitVariables);
    void on_start();
    void on_execute();
    void on_event(Event e);
    void on_exit();
};

#endif // INITSTATE_H