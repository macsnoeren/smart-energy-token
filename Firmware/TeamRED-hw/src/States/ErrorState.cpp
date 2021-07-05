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

    blinkTime = millis(); //set blinkTime
    startTime = millis(); //set startTime
}

//Main loop of the state
void ErrorState::on_execute()
{
    long current = millis();
    //check if 1 sec has elapsed
    if(current - blinkTime >= 1000)
    {
        PORTA_OUT ^= 1UL << 7; //toggle light
        blinkTime = current;
    }
    
    // check if 4 sec elapsed after reset
    if(current - startTime >= 4000)
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