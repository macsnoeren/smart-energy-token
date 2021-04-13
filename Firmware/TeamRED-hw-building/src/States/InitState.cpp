#include "States/InitState.h"
#include "Settings.h"
#include "Statemachine.h"

void InitState::on_init(Statemachine* statemachine,RF24* radio,bool isBase)
{
    _statemachine = statemachine;
    _radio = radio;
    _isBase = isBase;

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
    if (_isBase)
    {
        _statemachine->setState(StateNumber::SLEEP);
    }
    else
    {
        _statemachine->setState(StateNumber::SENDING);
        Event e{
            EventName::SendData,
            "tokentoken"
        };
        _statemachine->handle_event(e);
    }
}

//Main loop of the state
void InitState::on_execute()
{
    if (!_isBase)
    {
    }
    else
    {
        String text = "test";
        _radio->write(text.c_str(), strlen(text.c_str()));
    }
}

//Handels events when received
void InitState::on_event(Event e)
{
}

void InitState::on_exit()
{
}