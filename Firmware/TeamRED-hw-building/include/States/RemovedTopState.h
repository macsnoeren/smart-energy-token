#ifndef REMOVEDTOPSTATE_H
#define REMOVEDTOPSTATE_H

#include "State.h"


class RemovedTopState : public State
{
private:
public:
    void on_init(StateInitVariables stateInitVariables);
    void on_start();
    void on_execute();
    void on_event(Event e);
    void on_exit();
};

#endif // REMOVEDTOPSTATE_H