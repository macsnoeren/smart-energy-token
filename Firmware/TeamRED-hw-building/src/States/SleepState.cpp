#include "States/SleepState.h"
#include <avr/sleep.h>
#include "Settings.h"

void SleepState::on_init(StateInitVariables stateInitVariables)
{
    State::on_init(stateInitVariables); //call general init of state
}

void SleepState::on_start()
{
    // init all variables that need to be reset when the state enters

    //Enable interrupts
    GIMSK |= 1UL << PCIE0; //set interrup for pa7
    PCMSK0 |= 1UL << PCINT7;

    GIMSK |= 1UL << PCIE1; //set interrupt for pb2
    PCMSK1 |= 1UL << PCINT10;

    PUEB |= 1UL << 2; //enable pullup resitor for PB2

    sei();

    hasReceivedEvent = false;

    if (debug)
    {
        if (_isBase)
        {
            delay(100);

            String text = "Start Sleep";
            radio->write(text.c_str(), strlen(text.c_str()));

            delay(100);
        }
    }
    delay(100);

    set_sleep_mode(SLEEP_MODE_PWR_DOWN);

    sleep_mode();
}

//Main loop of the state
void SleepState::on_execute()
{
    if (!_isBase && hasReceivedEvent)
    {
        tokenprotocol *protocol = tokenprotocol::instance();
        protocol->send("Sleep state");
    }
    else
    {
        String text = "Sleep state";
        radio->write(text.c_str(), strlen(text.c_str()));
    }
}

//Handels events when received
void SleepState::on_event(Event e)
{
    hasReceivedEvent = true;
    // String text = "Received event";
    // radio->write(text.c_str(), strlen(text.c_str()));
    switch (e.name)
    {
    case EventName::ReceivedTopDataRisingInterrupt:
        _statemachine->setState(StateNumber::REMOVEDTOP);
        break;
    case EventName::ReceivedTopClockFallingInterrupt:
        _statemachine->setState(StateNumber::RECEIVING);
    default:
        break;
    }
}

void SleepState::on_exit()
{
    sleep_disable();

    //disable interrupts
    GIMSK &= ~(1UL << PCIE0);
    PCMSK0 &= ~(1UL << PCINT7);

    GIMSK &= ~(1UL << PCIE1);
    PCMSK1 &= ~(1UL << PCINT10);

    PUEB &= ~(1UL << 2); //disable pullup resitor pb2

    cli();
}