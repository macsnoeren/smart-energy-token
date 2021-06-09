#ifndef SLEEPSTATE_H
#define SLEEPSTATE_H

#include "WString.h"
#include "Event.h"
#include <RF24.h>

class Statemachine;

class SleepState
{
private:
    Statemachine *_statemachine;
    RF24 *_radio;
    bool _isBase;

    volatile bool hasReceivedRemovedTop;
    volatile bool hasReceivedDataStart;
public:
    void on_init(Statemachine* statemachine,RF24* radio,bool isBase);
    void on_start();
    void on_execute();
    void on_event(Event e);
    void on_exit();
    SleepState()
    {
    }
};

#endif // SLEEPSTATE_H