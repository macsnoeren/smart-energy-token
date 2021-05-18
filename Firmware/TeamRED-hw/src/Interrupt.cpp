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
    if (isPA4 && !prevTopClock)
    {
        PORTA_INTFLAGS |= 1UL << 4;
        String empty = "";
        Event e = {
            EventName::ReceivedTopClockRisingInterrupt,
            &empty[0]};

        statemachine->handle_event(e);
    }
    else if (!isPA4 && prevTopClock)
    {
        PORTA_INTFLAGS |= 1UL << 4;
        String empty = "";

        Event e = {
            EventName::ReceivedTopClockFallingInterrupt,
            &empty[0]};
        statemachine->handle_event(e);
    }
    prevTopClock = isPA4;

    bool isPB2 = (PORTA_IN >> 5) & 1;
    if (prevTopData && !isPB2) //detect topdata falling
    {
        PORTA_INTFLAGS |= 1UL << 5; //reset interrupt flag
        String empty = "";
        PORTA_OUT &= ~(1UL << 7);

        Event e = {
            EventName::ReceivedTopDataFallingInterrupt,
            &empty[0]};
        statemachine->handle_event(e);
    }
    else if (!prevTopData && isPB2) // detect topdata rising
    {
        PORTA_INTFLAGS |= 1UL << 5;

        String empty = "";

        Event e = {
            EventName::ReceivedTopDataRisingInterrupt,
            &empty[0]};
        statemachine->handle_event(e);
    }

    prevTopData = isPB2;
}

void Interrupt::setStatemachine(Statemachine *_statemachine)
{
    statemachine = _statemachine;
}
