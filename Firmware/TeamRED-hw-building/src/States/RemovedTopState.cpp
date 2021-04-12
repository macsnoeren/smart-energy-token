#include "States/RemovedTopState.h"
#include <avr/sleep.h>
#include "Settings.h"

void RemovedTopState::on_init(StateInitVariables stateInitVariables)
{
    State::on_init(stateInitVariables); //call general init of state
}

void RemovedTopState::on_start()
{
    // init all variables that need to be reset when the state enters
    if (debug)
    {
        if (_isBase)
        {
            String text = "Start RemovedTopState";
            radio->write(text.c_str(), strlen(text.c_str()));
        }
    }
}

//Main loop of the state
void RemovedTopState::on_execute()
{
    if (!_isBase)
    {
        tokenprotocol *protocol = tokenprotocol::instance();
        protocol->send("RemovedTopState");
    }
    else
    {
        String text = "RemovedTopState";
        radio->write(text.c_str(), strlen(text.c_str()));
    }
}

//Handels events when received
void RemovedTopState::on_event(Event e)
{

}

void RemovedTopState::on_exit()
{
    
}