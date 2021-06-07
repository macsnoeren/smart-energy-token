#include "States/SleepState.h"
#include <avr/sleep.h>
#include "Settings.h"
#include "Statemachine.h"
#include <util/delay.h>

void SleepState::on_init(Statemachine *statemachine, RF24 *radio, bool isBase)
{
    _statemachine = statemachine;
    _radio = radio;
    _isBase = isBase;
}

void SleepState::on_start()
{
    // init all variables that need to be reset when the state enters
    //PORTA_OUT &= ~(1UL << 7);

    if (!_isBase)
    {
        RTC_PITCTRLA = RTC_PERIOD_CYC32768_gc | RTC_PITEN_bm;
        RTC_PITINTCTRL = RTC_PI_bm;

        CLOCKPIN_BOTTOM_PIN_OUTPUT_REG &= ~(1UL << CLOCKPIN_BOTTOM_OUTPUT); // clock to input
        //CLOCKPIN_BOTTOM_WRITE_REG &= 1UL << CLOCKPIN_BOTTOM_WRITE; //clockpin bottom high

        DATAPIN_BOTTOM_PIN_OUTPUT_REG |= 1UL << DATAPIN_BOTTOM_OUTPUT;
        DATAPIN_BOTTOM_WRITE_REG &= ~(1UL << DATAPIN_BOTTOM_WRITE); // datapin to low
    }

    DATAPIN_TOP_OUTPUT_REG &= ~(1UL << DATAPIN_TOP_OUTPUT); //SET Data TO INPUT;
    PORTA_DIR &= ~(1UL << 4);                               //SET CLOCK TO INPUT

    PORTA_PIN4CTRL |= PORT_PULLUPEN_bm; //enable pullup resitor

    //Enable interrupts
    CLOCKPIN_TOP_INTERRUPT_REG |= PORT_ISC_BOTHEDGES_gc; //|= 1UL << CLOCKPIN_TOP_INTERRUPT; //Enale intterrupt
    DATAPIN_TOP_INTERRUPT_REG |= PORT_ISC_BOTHEDGES_gc;  //|= 1UL << DATAPIN_TOP_INTERRUPT; //Enable intterrupt

    //PORTA_PIN5CTRL |= 1UL << 3; //enable pullup resitor

    sei();

    hasStarted = false;
    hasReceivedRemovedTop = false;
    hasReceivedDataStart = false;
}

//Main loop of the state
void SleepState::on_execute()
{
    PORTA_OUT |= 1UL << 7;

    set_sleep_mode(SLEEP_MODE_PWR_DOWN);

    sleep_mode();

    sleep_disable();

    PORTA_OUT &= ~(1UL << 7);
    _delay_ms(1);
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
    case EventName::ReceivedTopDataFallingInterrupt:
    case EventName::ReceivedTopClockRisingInterrupt:
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
    if (_isBase)
    {
        //Turn of Period timer interval
        RTC_PITINTCTRL = 0x00;
    }

    //disable interrupts
    CLOCKPIN_TOP_INTERRUPT_REG &= ~(1UL << CLOCKPIN_TOP_INTERRUPT); //Enale intterrupt
    DATAPIN_TOP_INTERRUPT_REG &= ~(1UL << DATAPIN_TOP_INTERRUPT); //Enable intterrupt

    PORTA_PIN5CTRL &= ~(1UL << 3); //disable pullup resitor
    PORTA_PIN4CTRL &= ~(1UL << 3); //diable pullup resitor

    cli();
}