#include "States/SleepState.h"
#include <avr/sleep.h>
#include "Settings.h"
#include "Statemachine.h"
#include <util/delay.h>
#include <avr/wdt.h>
#include <avr/power.h>

void SleepState::on_init(Statemachine *statemachine, RF24 *radio, bool isBase)
{
    _statemachine = statemachine;
    _radio = radio;
    _isBase = isBase;
}

void SleepState::on_start()
{
    // init all variables that need to be reset when the state enters
    if (!_isBase)
    {
        //Turn on the PIT for checking if the power is on.
        RTC_PITCTRLA = RTC_PERIOD_CYC32768_gc | RTC_PITEN_bm;
        RTC_PITINTCTRL = RTC_PI_bm;

        //CLock bottom to input
        CLOCKPIN_BOTTOM_PIN_OUTPUT_REG &= ~(1UL << CLOCKPIN_BOTTOM_OUTPUT); // clock to input

        //Dota bottom to low for detecting detatching
        DATAPIN_BOTTOM_PIN_OUTPUT_REG |= 1UL << DATAPIN_BOTTOM_OUTPUT;
        DATAPIN_BOTTOM_WRITE_REG &= ~(1UL << DATAPIN_BOTTOM_WRITE); // datapin to low
    }

    //Turn both top pins to input
    DATAPIN_TOP_OUTPUT_REG &= ~(1UL << DATAPIN_TOP_OUTPUT); //SET Data TO INPUT;
    PORTA_DIR &= ~(1UL << 4);                               //SET CLOCK TO INPUT

    //Enable the pullup resistor for the clockline.
    PORTA_PIN4CTRL |= PORT_PULLUPEN_bm; 

    //Enable interrupts
    CLOCKPIN_TOP_INTERRUPT_REG |= PORT_ISC_BOTHEDGES_gc; 
    DATAPIN_TOP_INTERRUPT_REG |= PORT_ISC_BOTHEDGES_gc; 

    sei();

    hasReceivedRemovedTop = false;
    hasReceivedDataStart = false;

    power_all_disable();
}

//Main loop of the state
void SleepState::on_execute()
{
    //Turn of the light
    PORTA_OUT |= 1UL << 7;

    //If base disable the Watchdog and powerdown the RF24
    if (_isBase)
    {
        wdt_disable();
        _radio->powerDown();
    }

    //Set sleep mode to power down
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);

    //Enter sleep mode
    sleep_mode();

    //if base power the rf24 up and enable watchdog
    if (_isBase)
    {
        _radio->powerUp();
        wdt_enable(WDTO_2S);
    }
}

//Handels events when received
void SleepState::on_event(Event e)
{
    // char test[10];
    // sprintf(test, "%i", (int)e.name);

    // if (_isBase)
    // {
    //     bool isDone = false;
    //     uint8_t count = 0;
    //     // while (!isDone)
    //     // {
    //     isDone = _radio->write(test, strlen(test));
    //     //     if(count > 5)
    //     //     {
    //     //         isDone= true;
    //     //     }
    //     //     count++;
    //     // }
    // }
    switch (e.name)
    {
    case EventName::ReceivedTopDataRisingInterrupt:
    case EventName::ErrorInterrupt:
        if (_statemachine->hasTopToken)
        {
            _statemachine->hasTopToken = false;
            _statemachine->setState(StateNumber::SENDING);
        }
        break;
    case EventName::ReceivedTopClockFallingInterrupt:
        _statemachine->setState(StateNumber::RECEIVING);
        break;
    default:
        break;
    }
}

void SleepState::on_exit()
{
    power_all_enable();

    if (!_isBase)
    {
        //Turn of Period timer interval
        RTC_PITINTCTRL = 0x00;
    }

    //disable interrupts
    CLOCKPIN_TOP_INTERRUPT_REG &= ~(1UL << CLOCKPIN_TOP_INTERRUPT);
    DATAPIN_TOP_INTERRUPT_REG &= ~(1UL << DATAPIN_TOP_INTERRUPT);

    cli();
}