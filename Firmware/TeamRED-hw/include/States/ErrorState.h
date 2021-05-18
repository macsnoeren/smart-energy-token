#ifndef ERRORSTATE_H
#define ERRORSTATE_H

#include "WString.h"
#include "Event.h"
#include <RF24.h>

class Statemachine;

class ErrorState
{
private:
    Statemachine *_statemachine;
    RF24 *_radio;
    bool _isBase;

    long blinkTime;

public:
    void on_init(Statemachine* statemachine,RF24* radio,bool isBase);
    void on_start();
    void on_execute();
    void on_event(Event e);
    void on_exit();
    ErrorState()
    {
    }
};

#endif // REMOVEDTOPSTATE_H