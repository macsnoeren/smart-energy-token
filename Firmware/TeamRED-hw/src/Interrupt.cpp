#include "Interrupt.h"
#include "Event.h"
#include "Settings.h"

volatile bool prevTopData = true;
volatile bool prevTopClock = true;

Statemachine *statemachine;

ISR(PORTA_PORT_vect)
{
    PORTA_OUT |= 1UL << 7;

    bool isPA4 = (PORTA_IN >> 4) & 1;
    bool isPB2 = (PORTA_IN >> 5) & 1;
    if (isPA4 && !prevTopClock)
    {
        prevTopClock = isPA4;
        Event e = {
            EventName::ReceivedTopClockRisingInterrupt,
            NULL};

        statemachine->handle_event(e);
        PORTA_INTFLAGS |= 1UL << 4;
        return;
    }
    else if (!isPA4 && prevTopClock)
    {
        prevTopClock = isPA4;
        PORTA_INTFLAGS |= 1UL << 4;
        Event e = {
            EventName::ReceivedTopClockFallingInterrupt,
            NULL};
        statemachine->handle_event(e);
        return;
    }
    else if (prevTopData && !isPB2) //detect topdata falling
    {
        prevTopData = isPB2;
        PORTA_OUT &= ~(1UL << 7);

        Event e = {
            EventName::ReceivedTopDataFallingInterrupt,
            NULL};
        statemachine->handle_event(e);
        PORTA_INTFLAGS |= 1UL << 5; //reset interrupt flag
        return;
    }
    else if (!prevTopData && isPB2) // detect topdata rising
    {
        prevTopData = isPB2;
        Event e = {
            EventName::ReceivedTopDataRisingInterrupt,
            NULL};
        statemachine->handle_event(e);
        PORTA_INTFLAGS |= 1UL << 5;
        return;
    }
}

void Interrupt::setStatemachine(Statemachine *_statemachine)
{
    statemachine = _statemachine;
}
