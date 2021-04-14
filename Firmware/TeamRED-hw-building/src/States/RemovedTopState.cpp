#include "States/RemovedTopState.h"
#include "Settings.h"
#include "Statemachine.h"


void RemovedTopState::on_init(Statemachine* statemachine,RF24* radio,bool isBase)
{
    _statemachine = statemachine;
    _radio = radio;
    _isBase = isBase;
}

void RemovedTopState::on_start()
{
    // init all variables that need to be reset when the state enters
    // if (debug)
    // {
    //     if (_isBase)
    //     {
    //         String text = "Start RemovedTopState";
    //         _radio->write(text.c_str(), strlen(text.c_str()));
    //     }
    // }

    _statemachine->setState(StateNumber::SENDING);

    _statemachine->hasTopToken = false;
}

//Main loop of the state
void RemovedTopState::on_execute()
{
    if (!_isBase)
    {
    }
    else
    {
        String text = "RemovedTopState";
        _radio->write(text.c_str(), strlen(text.c_str()));
    }
}

//Handels events when received
void RemovedTopState::on_event(Event e)
{

}

void RemovedTopState::on_exit()
{
    
}