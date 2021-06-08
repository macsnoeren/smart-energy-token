#include "Statemachine.h"
#include "States/InitState.h"
#include "States/ReceivingState.h"
#include "States/SleepState.h"
#include "States/SendingState.h"
#include "States/ErrorState.h"
#include <util/delay.h>
#include <avr/wdt.h>

void Statemachine::on_init(RF24 *radio)
{
    hasTopToken = !((PORTA_IN >> 5) & 1);

    PORTA_OUT &= ~(1UL << 7);
    _delay_ms(200);
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
        PORTA_OUT &= ~(1UL << 7);
        SPI.end();
        _delay_ms(400);
    }

    hasTopToken = false;
    currentState = StateNumber::INIT;

    _radio = radio;

    initState.on_init(this, radio, isBase);
    receivingState.on_init(this, radio, isBase);
    sleepState.on_init(this, radio, isBase);
    sendingState.on_init(this, radio, isBase);
    errorState.on_init(this, radio, isBase);

    PORTA_OUT |= 1UL << 7;

    initState.on_start();

    blinkTime = millis();
    resetStartTime = millis();
}

void Statemachine::on_execute()
{
    if (isBase)
    {
        wdt_reset();
    }
    if (!(currentState == StateNumber::Error || currentState == StateNumber::SLEEP))
    {
        //Check if the state is stuck
        long current = millis();
        if (current - resetStartTime >= 20000)
        {
            setState(StateNumber::Error);
            return;
        }
    }

    // long current = millis();
    // if (current - blinkTime >= 500 && currentState == StateNumber::SLEEP)
    // {
    //     PORTA_OUT ^= 1UL << 7; //toggle light
    //     blinkTime = current;
    // }
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
    resetStartTime = millis();

    // if (isBase)
    // {
    //     char test[20] = "";
    //     sprintf(test, "%i-%i", (int)currentState, (int)newState);
    //     bool isDone = false;
    //     _radio->write(test, strlen(test));
    // }

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

    currentState = newState;

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

    // if (isBase)
    // {
    //     char test[20] = "done move";
    //     _radio->write(test, strlen(test));
    // }
}

Statemachine::Statemachine()
{
}

Statemachine::~Statemachine()
{
}