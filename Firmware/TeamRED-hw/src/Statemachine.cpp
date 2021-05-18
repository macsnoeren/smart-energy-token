#include "Statemachine.h"
#include "States/InitState.h"
#include "States/ReceivingState.h"
#include "States/SleepState.h"
#include "States/RemovedTopState.h"
#include "States/SendingState.h"
#include "States/ErrorState.h"

void Statemachine::on_init(RF24 *radio)
{
    //Init radio before everything cause everystate needs the radio for debugging
    const byte address[6] = "test1";
    isBase = radio->begin(); //check if radio is connected
    if (isBase)
    {
        radio->openWritingPipe(address); //Set the radio writing addres
        radio->stopListening();          //Set the radio to send mode
    }
    else
    {
        SPI.end();
    }

    hasTopToken = false;
    currentState = StateNumber::INIT;

    _radio = radio;

    initState.on_init(this, radio, isBase);
    receivingState.on_init(this, radio, isBase);
    sleepState.on_init(this, radio, isBase);
    sendingState.on_init(this, radio, isBase);
    removedTopState.on_init(this, radio, isBase);
    errorState.on_init(this,radio,isBase);

    PORTA_OUT |= 1UL << 7;

    initState.on_start();
}

void Statemachine::on_execute()
{
    switch (currentState)
    {
    case StateNumber::INIT:
        initState.on_execute();
        break;
    case StateNumber::REMOVEDTOP:
        removedTopState.on_execute();
        break;
    case StateNumber::RECEIVING:
        receivingState.on_execute();
        break;
    case StateNumber::SENDING:
        sendingState.on_execute();
        break;
    case StateNumber::SLEEP:
        sleepState.on_execute();
        break;
    case StateNumber::Error:
        errorState.on_execute();
        break;
    }

    if (isBase)
    {
        SPI.end();
        const byte address[6] = "test1";
        _radio->begin(); //check if radio is connected
        _radio->openWritingPipe(address);
        _radio->stopListening();
    }
}

void Statemachine::handle_event(Event e)
{
    switch (currentState)
    {
    case StateNumber::INIT:
        initState.on_event(e);
        break;
    case StateNumber::REMOVEDTOP:
        removedTopState.on_event(e);
        break;
    case StateNumber::RECEIVING:
        receivingState.on_event(e);
        break;
    case StateNumber::SENDING:
        sendingState.on_event(e);
        break;
    case StateNumber::SLEEP:
        sleepState.on_event(e);
        break;
    case StateNumber::Error:
        errorState.on_event(e);
        break;
    default:
        break;
    }
}

void Statemachine::setState(StateNumber newState)
{
    switch (currentState)
    {
    case StateNumber::INIT:
        initState.on_exit();
        break;
    case StateNumber::REMOVEDTOP:
        removedTopState.on_exit();
        break;
    case StateNumber::RECEIVING:
        receivingState.on_exit();
        break;
    case StateNumber::SENDING:
        sendingState.on_exit();
        break;
    case StateNumber::SLEEP:
        sleepState.on_exit();
        break;
    case StateNumber::Error:
        errorState.on_exit();
        break;

    default:
        break;
    }

    currentState = newState;

    switch (currentState)
    {
    case StateNumber::INIT:
        initState.on_start();
        break;
    case StateNumber::REMOVEDTOP:
        removedTopState.on_start();
        break;
    case StateNumber::RECEIVING:
        receivingState.on_start();
        break;
    case StateNumber::SENDING:
        sendingState.on_start();
        break;
    case StateNumber::SLEEP:
        sleepState.on_start();
        break;
    case StateNumber::Error:
        errorState.on_start();
        break;

    default:
        break;
    }
}

Statemachine::Statemachine()
{
}

Statemachine::~Statemachine()
{
}