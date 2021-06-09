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

    bool isBase;
    RF24 *_radio;
    volatile StateNumber currentState;

public:
    void on_init(RF24 *radio);
    void on_execute();
    void handle_event(Event e);

    void setState(StateNumber state);

    Statemachine();
    ~Statemachine();

    long blinkTime;
    long resetStartTime;

    InitState initState;
    ReceivingState receivingState;
    SleepState sleepState;
    SendingState sendingState;
    ErrorState errorState;

    volatile bool hasTopToken;
};

#endif // STATEMACHINE_H