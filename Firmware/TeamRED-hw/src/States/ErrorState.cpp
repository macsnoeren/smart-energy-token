#include "States/ErrorState.h"
#include "Settings.h"
#include "Statemachine.h"

void ErrorState::on_init(Statemachine *statemachine, RF24 *radio, bool isBase)
{
    _statemachine = statemachine;
    _radio = radio;
    _isBase = isBase;
}

void ErrorState::on_start()
{
    _statemachine->hasTopToken = false;

    blinkTime = millis();    
    startTime = millis();
}

//Main loop of the state
void ErrorState::on_execute()
{
    long current = millis();
    if(current - blinkTime >= 1000)
    {
        PORTA_OUT ^= 1UL << 7; //toggle light
        blinkTime = current;
    }

    if(current - startTime >= 20000)
    {
        _statemachine->setState(StateNumber::INIT);
    }
}

//Handels events when received
void ErrorState::on_event(Event e)
{
}

void ErrorState::on_exit()
{
}