#ifndef SLEEPSTATE_H
#define SLEEPSTATE_H

#include "State.h"


class SleepState : public State
{
private:
    bool hasReceivedEvent;
public:
    void on_init(StateInitVariables stateInitVariables);
    void on_start();
    void on_execute();
    void on_event(Event e);
    void on_exit();
};

#endif // SLEEPSTATE_H