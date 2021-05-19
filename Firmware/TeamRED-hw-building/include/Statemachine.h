#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "States/InitState.h"
#include "States/ReceivingState.h"
#include "States/RemovedTopState.h"
#include "States/SendingState.h"
#include "States/SleepState.h"

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
    REMOVEDTOP
};

class State;

class Statemachine
{
private:
    static Statemachine *_instance;
    RF24 *_radio;

    StateNumber currentState;
    bool isBase;

public:
    void on_init(RF24 *radio);
    void on_execute();
    void handle_event(Event e);

    void setState(StateNumber state);

    Statemachine();
    ~Statemachine();

    InitState initState;
    ReceivingState receivingState;
    SleepState sleepState;
    RemovedTopState removedTopState;
    SendingState sendingState;

    bool hasTopToken;
    String codes;
};

#endif // STATEMACHINE_H