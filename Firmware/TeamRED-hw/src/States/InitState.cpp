#include "States/InitState.h"
#include "Settings.h"
#include "Statemachine.h"

void InitState::on_init(Statemachine *statemachine, RF24 *radio, bool isBase)
{
    _statemachine = statemachine;
    _radio = radio;
    _isBase = isBase;
}

void InitState::on_start()
{
    //Turn pullups on not needed pins
    PORTB_PIN0CTRL |= PORT_PULLUPEN_bm;
    PORTA_PIN6CTRL |= PORT_PULLUPEN_bm;
    PORTA_PIN0CTRL |= PORT_PULLUPEN_bm;

    PORTA_OUT &= ~(1UL << 7);
    // init all variables that need to be reset when the state enters
    if (_isBase)
    {
        _statemachine->setState(StateNumber::SLEEP);
    }
    else
    {
        PORTB_PIN1CTRL |= PORT_PULLUPEN_bm;
        PORTB_PIN2CTRL |= PORT_PULLUPEN_bm;
        PORTB_PIN3CTRL |= PORT_PULLUPEN_bm;
        PORTA_PIN3CTRL |= PORT_PULLUPEN_bm;
        _statemachine->setState(StateNumber::SENDING);
    }
}

//Main loop of the state
void InitState::on_execute()
{
}

//Handels events when received
void InitState::on_event(Event e)
{
}

void InitState::on_exit()
{
    PORTA_OUT |= 1UL << 7;
}