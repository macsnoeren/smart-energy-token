#include "States/InitState.h"
#include "Settings.h"

void InitState::on_init(StateInitVariables stateInitVariables)
{
    State::on_init(stateInitVariables); //call general init of state

    //Init token protocol
    tokenprotocol *protocol = tokenprotocol::instance();                           //Setup token protocol
    _isBase ? protocol->setup(radio, _isBase) : protocol->setup(nullptr, _isBase); //setup the protocol

    // Disable not needed components

    //disable analog comparator 0 and 1
    ACSR0A |= _BV(ACD0);
    ACSR1A |= _BV(ACD1);

    //disable adc
    ADCSRA &= ~(1 << ADEN);
}

void InitState::on_start()
{
    // init all variables that need to be reset when the state enters

    if (debug)
    {
        if (_isBase)
        {
            String text = "Start InitState";
            radio->write(text.c_str(), strlen(text.c_str()));
            _statemachine->setState(StateNumber::SLEEP);
        }
        else
        {
            _statemachine->setState(StateNumber::SENDING);
        }
    }
}

//Main loop of the state
void InitState::on_execute()
{
    if (!_isBase)
    {
        tokenprotocol *protocol = tokenprotocol::instance();
        protocol->send("Test");
    }
    else
    {
        String text = "test";
        radio->write(text.c_str(), strlen(text.c_str()));
    }
}

//Handels events when received
void InitState::on_event(Event e)
{
}

void InitState::on_exit()
{
}