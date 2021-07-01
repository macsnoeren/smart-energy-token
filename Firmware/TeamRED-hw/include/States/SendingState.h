#ifndef SENDINGSTATE_H
#define SENDINGSTATE_H

#include "WString.h"
#include "Event.h"
#include <RF24.h>

class Statemachine;

class SendingState
{
private:
    Statemachine *_statemachine; // pointer that stores the hole statemachine
    RF24 *_radio;                // radio variable for sending data if it is an base otherwise null
    bool _isBase;                // boolean if the program is running on a base or token

    char toSend[128];        // char array stores received text from top token empty if none
    char buildingcode[128];  // char array that stores top text and own serial number
    const char *dot = ".";   // stop charcter for sending to gateway
    const char *delim = ","; // delimeter character for sending to building
    uint8_t currentChar;     // current char number that is beeing send
    uint8_t tries;           // amount of tries sending char

public:
    void on_init(Statemachine *statemachine, RF24 *radio, bool isBase); // init method of the state
    void on_start();                                                    // method that gets called when the state starts
    void on_execute();                                                  // method that gets called every loop
    void on_event(Event e);                                             // method that gets called when an event has been received
    void on_exit();                                                     // method that gets called when the state switches and this state therefore ends
    SendingState()
    {
    }
};

#endif // INITSTATE_H