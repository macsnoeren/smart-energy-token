#include "Interrupt.h"
#include "Event.h"
#include "Settings.h"
#include <avr/sleep.h>
#include <util/delay.h>

volatile bool prevTopData = true;
volatile bool prevTopClock = true;

Statemachine *statemachine;

ISR(RTC_PIT_vect)
{
    //reset rtc vect
    RTC_PITINTFLAGS = 0xFF;
}

ISR(PORTA_PORT_vect)
{
    //read both port values
    bool isTopClock = (PORTA_IN >> 5) & 1;
    bool isTopData = (PORTA_IN >> 4) & 1;

    PORTA_OUT |= 1UL << 7;
    if (isTopData && !prevTopClock)
    {
        prevTopClock = isTopData;
        Event e = {
            EventName::ReceivedTopClockRisingInterrupt,
            NULL};

        statemachine->handle_event(e);
    }
    else if (!isTopData && prevTopClock)
    {
        prevTopClock = isTopData;
        Event e = {
            EventName::ReceivedTopClockFallingInterrupt,
            NULL};
        statemachine->handle_event(e);
    }
    else if (prevTopData && !isTopClock) //detect topdata falling
    {
        prevTopData = isTopClock;
        PORTA_OUT &= ~(1UL << 7);

        Event e = {
            EventName::ReceivedTopDataFallingInterrupt,
            NULL};
        statemachine->handle_event(e);
    }
    else if (!prevTopData && isTopClock) // detect topdata rising
    {
        prevTopData = isTopClock;
        Event e = {
            EventName::ReceivedTopDataRisingInterrupt,
            NULL};
        statemachine->handle_event(e);
    }
    else
    {
        Event e = {
            EventName::ErrorInterrupt,
            NULL};
        statemachine->handle_event(e);
    }

    PORTA_INTFLAGS = 0xFF;
}

void Interrupt::setStatemachine(Statemachine *_statemachine)
{
    statemachine = _statemachine;
}
