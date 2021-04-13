#ifndef REMOVEDTOPSTATE_H
#define REMOVEDTOPSTATE_H

#include "WString.h"
#include "Event.h"
#include <RF24.h>

class Statemachine;

class RemovedTopState
{
private:
    Statemachine *_statemachine;
    RF24 *_radio;
    bool _isBase;

public:
    void on_init(Statemachine* statemachine,RF24* radio,bool isBase);
    void on_start();
    void on_execute();
    void on_event(Event e);
    void on_exit();
    RemovedTopState()
    {
    }
};

#endif // REMOVEDTOPSTATE_H