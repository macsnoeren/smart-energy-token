#include "Interrupt.h"
#include "Event.h"

bool prevTopData = true;
bool prevTopClock = true;

Statemachine *statemachine;

ISR(PCINT0_vect)
{
    bool isPA7 = (PINA >> PINA7) & 1;
    if (isPA7 && !prevTopClock)
    {
        Event e = {
            EventName::ReceivedTopClockRisingInterrupt,
            ""};

        statemachine->handle_event(e);
    }
    else if (!isPA7 && prevTopClock)
    {
        Event e = {
            EventName::ReceivedTopClockFallingInterrupt,
            ""};
        statemachine->handle_event(e);
    }
    prevTopClock = isPA7;
}

ISR(PCINT1_vect)
{

    bool isPB2 = (PINB >> PINB2) & 1;
    if (prevTopData && !isPB2) //detect topdata falling
    {
        Event e = {
            EventName::ReceivedTopDataFallingInterrupt,
            ""};
        statemachine->handle_event(e);
    }
    else if (!prevTopData && isPB2) // detect topdata rising
    {
        Event e = {
            EventName::ReceivedTopDataRisingInterrupt,
            ""};
        statemachine->handle_event(e);
    }
    prevTopData = isPB2;
}

void Interrupt::setStatemachine(Statemachine *_statemachine)
{
    statemachine = _statemachine;
}
