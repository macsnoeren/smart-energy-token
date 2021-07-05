#include "Statemachine.h"
#include "States/InitState.h"
#include "States/ReceivingState.h"
#include "States/SleepState.h"
#include "States/SendingState.h"
#include "States/ErrorState.h"
#include <util/delay.h>
#include <avr/wdt.h>
#include "Settings.h"

void Statemachine::on_init(RF24 *radio)
{
    // check wheter an top token is connected
    hasTopToken = !((PORTA_IN >> 5) & 1);

    //Init radio before everything cause everystate needs the radio for debugging
    const byte address[6] = "test1";
    isBase = radio->begin(); //check if radio is connected
    isBase = radio->isChipConnected();
    if (isBase)
    {
        radio->openWritingPipe(address); //Set the radio writing addres
        radio->stopListening();          //Set the radio to send mode
    }
    else
    {
        //end spi otherwise the application doesn't work
        SPI.end();
        _delay_ms(200); //wait a while
    }

    currentState = StateNumber::INIT; // set current state to init

    _radio = radio; // set radio variable

    //init all the states
    initState.on_init(this, radio, isBase);
    receivingState.on_init(this, radio, isBase);
    sleepState.on_init(this, radio, isBase);
    sendingState.on_init(this, radio, isBase);
    errorState.on_init(this, radio, isBase);

    // turn of the light
    PORTA_OUT |= 1UL << 7;

    //start the init state
    initState.on_start();

    //init the timer variables
    //blinkTime = millis();
    resetStartTime = millis();
}

void Statemachine::on_execute()
{
    // reset the watchdog if it is an building
    if (isBase)
    {
        wdt_reset();
    }

    // if not error or sleep and the amount of time in the state set the state to the error state
    if (!(currentState == StateNumber::Error || currentState == StateNumber::SLEEP))
    {
        //Check if the state is stuck
        long current = millis();
        if (current - resetStartTime >= 5000)
        {
            setState(StateNumber::Error);
            return;
        }
    }

    //test code for seeing if the state is sleep when disabling sleep
    // long current = millis();
    // if (current - blinkTime >= 500 && currentState == StateNumber::SLEEP)
    // {
    //     PORTA_OUT ^= 1UL << 7; //toggle light
    //     blinkTime = current;
    // }

    //switch case for selecting the right execute of the currentstate
    switch (currentState)
    {
    case StateNumber::INIT:
        initState.on_execute();
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

    //not needed code for reseting the RF sender (if the building doenst send umcomment (last resort))
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
    // switch case for right on_event method
    switch (currentState)
    {
    case StateNumber::INIT:
        initState.on_event(e);
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
    //reset last state switch time
    resetStartTime = millis();

    // test code for logging the state switches
    // if (isBase)
    // {
    //     char test[20] = "";
    //     sprintf(test, "%i-%i", (int)currentState, (int)newState);
    //     bool isDone = false;
    //     _radio->write(test, strlen(test));
    // }

    // switch case for correct exit method
    switch (currentState)
    {
    case StateNumber::INIT:
        initState.on_exit();
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

    //set new currentstate
    currentState = newState;

    // switch state for start method of new currentstate
    switch (currentState)
    {
    case StateNumber::INIT:
        initState.on_start();
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