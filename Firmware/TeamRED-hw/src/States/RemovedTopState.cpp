#include "States/RemovedTopState.h"
#include "Settings.h"
#include "Statemachine.h"

void RemovedTopState::on_init(Statemachine *statemachine, RF24 *radio, bool isBase)
{
    _statemachine = statemachine;
    _radio = radio;
    _isBase = isBase;
}

void RemovedTopState::on_start()
{
    _statemachine->hasTopToken = false;
}

//Main loop of the state
void RemovedTopState::on_execute()
{
    _statemachine->setState(StateNumber::SENDING);
}

//Handels events when received
void RemovedTopState::on_event(Event e)
{
}

void RemovedTopState::on_exit()
{
}