#ifndef SENDINGSTATE_H
#define SENDINGSTATE_H

#include "WString.h"
#include "Event.h"
#include <RF24.h>

class Statemachine;

class SendingState
{
private:
    Statemachine *_statemachine;
    RF24 *_radio;
    bool _isBase;

    char toSend[128];
    uint8_t currentChar;
    bool waitingForAck;
    uint8_t tries;
public:
    void on_init(Statemachine* statemachine,RF24* radio,bool isBase);
    void on_start();
    void on_execute();
    void on_event(Event e);
    void on_exit();
    SendingState()
    {
    }
};

#endif // INITSTATE_H