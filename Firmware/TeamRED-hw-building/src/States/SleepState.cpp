#include "States/SleepState.h"
#include <avr/sleep.h>
#include "Settings.h"
#include "Statemachine.h"

void SleepState::on_init(Statemachine *statemachine, RF24 *radio, bool isBase)
{
    _statemachine = statemachine;
    _radio = radio;
    _isBase = isBase;
}

void SleepState::on_start()
{
    // init all variables that need to be reset when the state enters   

    //Enable interrupts
    GIMSK |= 1UL << PCIE0; //set interrup for pa7
    PCMSK0 |= 1UL << PCINT7;

    GIMSK |= 1UL << PCIE1; //set interrupt for pb2
    PCMSK1 |= 1UL << PCINT10;

    PUEB |= 1UL << 2; //enable pullup resitor for PB2
    PUEA |= 1UL << 7; //enable pullup resitor for PB2

    sei();

    hasStarted = false;
    hasReceivedRemovedTop = false;
    hasReceivedDataStart = false;

    if (!_isBase)
    {
        delay(2000);
    }
}

//Main loop of the state
void SleepState::on_execute()
{
    if (!hasStarted && _isBase)
    {
        set_sleep_mode(SLEEP_MODE_PWR_DOWN);

        sleep_mode();
        hasStarted = true;
    }

    if (hasReceivedRemovedTop)
    {
        hasReceivedRemovedTop = false;
        _statemachine->setState(StateNumber::REMOVEDTOP);
    }

    if (hasReceivedDataStart)
    {
        hasReceivedDataStart = false;
        _statemachine->setState(StateNumber::RECEIVING);
    }
}

//Handels events when received
void SleepState::on_event(Event e)
{
    switch (e.name)
    {
    case EventName::ReceivedTopDataRisingInterrupt:
        if (_statemachine->hasTopToken)
        {
            hasReceivedRemovedTop = true;
        }
        break;
    case EventName::ReceivedTopClockFallingInterrupt:
        hasReceivedDataStart = true;
    default:
        break;
    }
}

void SleepState::on_exit()
{
    sleep_disable();

    //disable interrupts
    GIMSK &= ~(1UL << PCIE0);
    PCMSK0 &= ~(1UL << PCINT7);

    GIMSK &= ~(1UL << PCIE1);
    PCMSK1 &= ~(1UL << PCINT10);

    PUEB &= ~(1UL << 2); //disable pullup resitor pb2
    PUEA &= ~(1UL << 7); //disable pullup resistor PA7

    cli();
}