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
    //PORTA_OUT &= ~(1UL << 7);

    PORTA_INTFLAGS = 0xff;

    //Enable interrupts
    CLOCKPIN_TOP_INTERRUPT_REG |= PORT_ISC_BOTHEDGES_gc; //|= 1UL << CLOCKPIN_TOP_INTERRUPT; //Enale intterrupt

    DATAPIN_TOP_INTERRUPT_REG |= PORT_ISC_BOTHEDGES_gc; //|= 1UL << DATAPIN_TOP_INTERRUPT; //Enable intterrupt

    PORTA_PIN5CTRL |= 1UL << 3; //enable pullup resitor 
    PORTA_PIN4CTRL |= 1UL << 3; //enable pullup resitor 

    sei();

    hasStarted = false;
    hasReceivedRemovedTop = false;
    hasReceivedDataStart = false;

    if (!_isBase)
    {
        delay(2000);
    }

    startTimeBlink = millis();
}

//Main loop of the state
void SleepState::on_execute()
{
    PORTA_OUT |= 1UL << 7;

    long current = millis();
    if(current - startTimeBlink >= 1000)
    {
        PORTA_OUT ^= 1UL << 7;
        startTimeBlink = current;
    }

    if (hasReceivedRemovedTop)
    {
        hasReceivedRemovedTop = false;
        _statemachine->setState(StateNumber::REMOVEDTOP);
    }else if (hasReceivedDataStart)
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
            PORTA_OUT &= ~(1UL << 7);

            hasReceivedRemovedTop = true;
        }
        break;
    case EventName::ReceivedTopClockRisingInterrupt:
        if (_statemachine->hasTopToken)
        {
            PORTA_OUT &= ~(1UL << 7);

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
    //sleep_disable();

    //disable interrupts
    CLOCKPIN_TOP_INTERRUPT_REG &= ~(1UL << CLOCKPIN_TOP_INTERRUPT); //Enale intterrupt

    DATAPIN_TOP_INTERRUPT_REG &= ~(1UL << DATAPIN_TOP_INTERRUPT); //Enable intterrupt

    
    PORTA_PIN5CTRL &= ~(1UL << 3); //enable pullup resitor 
    PORTA_PIN4CTRL &= ~(1UL << 3); //enable pullup resitor 

    //cli();
}