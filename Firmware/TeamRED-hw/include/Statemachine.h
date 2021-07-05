#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "States/InitState.h"
#include "States/ReceivingState.h"
#include "States/SendingState.h"
#include "States/SleepState.h"
#include "States/ErrorState.h"

#include "Event.h"
#include <Arduino.h>
#include <RF24.h>

#define NumberOfStates 5

enum StateNumber
{
    INIT,
    SENDING,
    RECEIVING,
    SLEEP,
    Error
};

class State;

class Statemachine
{
private:
    static Statemachine *_instance;

    bool isBase;            // boolean if the program is running on a base or token
    RF24 *_radio;           // radio variable for sending data if it is an base otherwise null
    volatile StateNumber currentState; // currentState value

    long blinkTime;         // Time since last blink 
    long resetStartTime;    // Time since last state change

    //All states defined
    InitState initState;
    ReceivingState receivingState;
    SleepState sleepState;
    SendingState sendingState;
    ErrorState errorState;

public:
    void on_init(RF24 *radio);      // initalize the statemachine
    void on_execute();              // function that executes everytime a loop happends
    void handle_event(Event e);     // function that routes events to the current state

    void setState(StateNumber state);   // function that changes the state

    Statemachine();  
    ~Statemachine();

    volatile bool hasTopToken;      // bool that stores wheter an token is atop
};

#endif // STATEMACHINE_H