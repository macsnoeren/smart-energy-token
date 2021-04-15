#include "Interrupt.h"
#include "Event.h"

volatile bool prevTopData = true;
volatile bool prevTopClock = true;

Statemachine *statemachine;

ISR(PCINT0_vect)
{
    bool isPA7 = (PINA >> PINA7) & 1;
    if (isPA7 && !prevTopClock)
    {
        String empty = "";
        Event e = {
            EventName::ReceivedTopClockRisingInterrupt,
            &empty[0]};

        statemachine->handle_event(e);
    }
    else if (!isPA7 && prevTopClock)
    {
        String empty = "";

        Event e = {
            EventName::ReceivedTopClockFallingInterrupt,
            &empty[0]};
        statemachine->handle_event(e);
    }
    prevTopClock = isPA7;
}

ISR(PCINT1_vect)
{

    bool isPB2 = (PINB >> PINB2) & 1;
    if (prevTopData && !isPB2) //detect topdata falling
    {
        String empty = "";

        Event e = {
            EventName::ReceivedTopDataFallingInterrupt,
            &empty[0]};
        statemachine->handle_event(e);
    }
    else if (!prevTopData && isPB2) // detect topdata rising
    {
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
