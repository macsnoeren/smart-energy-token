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
    RTC_PITINTFLAGS = RTC_PI_bm;
    // PORTA_OUT &= ~(1UL << 7);
    // _delay_ms(1000);
}

ISR(PORTA_PORT_vect)
{
    PORTA_OUT &= ~(1UL << 7);

    bool isPB2 = (PORTA_IN >> 5) & 1;
    bool isPA4 = (PORTA_IN >> 4) & 1;

    // if (statemachine->currentState == StateNumber::SLEEP)
    // {
    //     char test[10] = "testing";
    //     statemachine->_radio->write(test, strlen(test));
    // }

    PORTA_OUT |= 1UL << 7;
    if (isPA4 && !prevTopClock)
    {
        prevTopClock = isPA4;
        Event e = {
            EventName::ReceivedTopClockRisingInterrupt,
            NULL};

        statemachine->handle_event(e);
    }
    else if (!isPA4 && prevTopClock)
    {
        prevTopClock = isPA4;
        Event e = {
            EventName::ReceivedTopClockFallingInterrupt,
            NULL};
        statemachine->handle_event(e);
    }
    else if (prevTopData && !isPB2) //detect topdata falling
    {
        prevTopData = isPB2;
        PORTA_OUT &= ~(1UL << 7);

        Event e = {
            EventName::ReceivedTopDataFallingInterrupt,
            NULL};
        statemachine->handle_event(e);
    }
    else if (!prevTopData && isPB2) // detect topdata rising
    {
        prevTopData = isPB2;
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
