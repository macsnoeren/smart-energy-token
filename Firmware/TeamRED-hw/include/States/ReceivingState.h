#ifndef RECEIVINGSTATE_H
#define RECEIVINGSTATE_H

#include "WString.h"
#include "Event.h"
#include <RF24.h>

class Statemachine;

class ReceivingState
{
private:
    Statemachine *_statemachine; // pointer that stores the hole statemachine
    RF24 *_radio;                // radio variable for sending data if it is an base otherwise null
    bool _isBase;                // boolean if the program is running on a base or token

    char buffer;               // buffer that stores the current receiving byte
    uint8_t topClockBitNumber; // number that stores the current position of the received bit in the buffer
    uint8_t amount1bits;       // number of 1 bits that are send for parity bit
    char receivedText[128];    // array that stores current received text

    volatile bool hasClockLineRised; // boolean that stores wheter the clock is high or low (used for end bit)

    bool sendAck; // boolean that stores wheter ack is being send
    bool ackHigh; // ack value

public:
    void on_init(Statemachine *statemachine, RF24 *radio, bool isBase); // init method of the state
    void on_start();                                                    // method that gets called when the state starts
    void on_execute();                                                  // method that gets called every loop
    void on_event(Event e);                                             // method that gets called when an event has been received
    void on_exit();                                                     // method that gets called when the state switches and this state therefore ends

    ReceivingState()
    {
    }
};

#endif // RECEIVINGSTATE_H