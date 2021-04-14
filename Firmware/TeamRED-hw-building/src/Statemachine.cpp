#include "Statemachine.h"
#include "States/InitState.h"
#include "States/ReceivingState.h"
#include "States/SleepState.h"
#include "States/RemovedTopState.h"
#include "States/SendingState.h"

void Statemachine::on_init(RF24 radio)
{
    //Init radio before everything cause everystate needs the radio for debugging
    const byte address[6] = "test1";
    bool isBase = radio.begin(); //check if radio is connected
    if (isBase)
    {
        radio.openWritingPipe(address); //Set the radio writing addres
        radio.stopListening();          //Set the radio to send mode
        delay(4000);                    //Delay for the radio to proper initalize might not be needed
    }
    else
    {
        SPI.end();
    }

    hasTopToken = false;
    codes = "";
    currentState = StateNumber::INIT;

    _radio = &radio;

    initState.on_init(this, &radio, isBase);
    receivingState.on_init(this, &radio, isBase);
    sleepState.on_init(this, &radio, isBase);
    sendingState.on_init(this, &radio, isBase);
    removedTopState.on_init(this, &radio, isBase);

    initState.on_start();

    if (isBase)
    {
        delay(200);
        String text = "Starting 123";
        radio.write(text.c_str(), strlen(text.c_str()));

        delay(100);
    }
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