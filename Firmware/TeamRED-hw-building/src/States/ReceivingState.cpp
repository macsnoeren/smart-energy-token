#include "States/ReceivingState.h"
#include "Settings.h"
void ReceivingState::on_init(StateInitVariables stateInitVariables)
{
    State::on_init(stateInitVariables);
}

void ReceivingState::on_start()
{
    // init all variables that need to be reset when the state enters

    if (debug)
    {
        if (_isBase)
        {
            delay(100);

            String text = "Start Receiving";
            radio->write(text.c_str(), strlen(text.c_str()));

            delay(100);
        }
    }
}

//Main loop of the state
void ReceivingState::on_execute()
{
    if (!_isBase)
    {
        tokenprotocol *protocol = tokenprotocol::instance();
        protocol->send("ReceivingState");
    }
    else
    {
        String text = "ReceivingState";
        radio->write(text.c_str(), strlen(text.c_str()));
    }
}

//Handels events when received
void ReceivingState::on_event(Event e)
{
}

void ReceivingState::on_exit()
{
}