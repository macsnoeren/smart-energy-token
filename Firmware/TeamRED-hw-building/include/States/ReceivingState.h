#ifndef RECEIVINGSTATE_H
#define RECEIVINGSTATE_H

#include "WString.h"
#include "Event.h"
#include <RF24.h>

class Statemachine;

class ReceivingState
{
private:
    Statemachine *_statemachine;
    RF24 *_radio;
    bool _isBase;

    uint8_t topClockBitNumber;

    volatile bool hasClockLineRised;

    char buffer;
    uint8_t amount1bits;
    char receivedText2[32];

    bool sendAck;
    bool ackHigh;

public:
    void on_init(Statemachine* statemachine,RF24* radio,bool isBase);
    void on_start();
    void on_execute();
    void on_event(Event e);
    void on_exit();

    ReceivingState()
    {
    }
};

#endif // RECEIVINGSTATE_H