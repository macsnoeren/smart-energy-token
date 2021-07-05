#include "States/ReceivingState.h"
#include "Settings.h"
#include "Statemachine.h"
#include <util/delay.h>


void ReceivingState::on_init(Statemachine *statemachine, RF24 *radio, bool isBase)
{
    _statemachine = statemachine;
    _radio = radio;
    _isBase = isBase;
}

void ReceivingState::on_start()
{
    PORTA_OUT &= ~(1UL << 7);

    // init all variables that need to be reset when the state enters
    topClockBitNumber = 0;
    amount1bits = 0;
    buffer = 0;
    hasClockLineRised = false;
    _statemachine->hasTopToken = true;
    sendAck = false;
    receivedText[0] = '\0';

    if(!_isBase)
    {
        //CLock bottom to input
        CLOCKPIN_BOTTOM_PIN_OUTPUT_REG &= ~(1UL << CLOCKPIN_BOTTOM_OUTPUT); // clock to input

        //Dota bottom to low for detecting detatching
        DATAPIN_BOTTOM_PIN_OUTPUT_REG |= 1UL << DATAPIN_BOTTOM_OUTPUT;
        DATAPIN_BOTTOM_WRITE_REG &= ~(1UL << DATAPIN_BOTTOM_WRITE); // datapin to low
    }

    _delay_ms(1 * tokenProtocolDelay);

    CLOCKPIN_TOP_INTERRUPT_REG |= PORT_ISC_BOTHEDGES_gc; //|= 1UL << CLOCKPIN_TOP_INTERRUPT; //Enale intterrupt
    DATAPIN_TOP_INTERRUPT_REG |= PORT_ISC_BOTHEDGES_gc;  //|= 1UL << DATAPIN_TOP_INTERRUPT; //Enable intterrupt

    PORTA_PIN5CTRL |= 1UL << 3; //enable pullup resitor for PB2
    PORTA_PIN4CTRL |= 1UL << 3; //enable pullup resitor for PA4

    //Send ack back;
    DATAPIN_TOP_OUTPUT_REG |= 1UL << DATAPIN_TOP_OUTPUT; //Set DATA to OUTPUT
    DATAPIN_TOP_WRITE_REG |= 1UL << DATAPIN_TOP_WRITE;   // set BB2 to High;
    _delay_ms(2 * tokenProtocolDelay);

    DATAPIN_TOP_OUTPUT_REG &= ~(1UL << DATAPIN_TOP_OUTPUT); //SET DATA to INput
    _delay_ms(2 * tokenProtocolDelay);

    sei();
    
}

//Main loop of the state
void ReceivingState::on_execute()
{
}

//Handels events when received
void ReceivingState::on_event(Event e)
{
    switch (e.name)
    {
    case EventName::ReceivedTopClockFallingInterrupt:
        hasClockLineRised = false;
        break;
    case EventName::ReceivedTopClockRisingInterrupt:
        hasClockLineRised = true;

        if (sendAck)
        {
            sendAck = false;
            DATAPIN_TOP_OUTPUT_REG &= ~(1UL << DATAPIN_TOP_OUTPUT);
        }
        else
        {
            PORTA_OUT |= 1UL << 7;

            if (topClockBitNumber <= 6)
            {
                if ((DATAPIN_TOP_READ_REG >> DATAPIN_TOP_READ) & 1) // read PB2 (Datapint)
                {
                    buffer |= 1UL << (6 - topClockBitNumber); //Write 1
                    amount1bits++;
                }
                else
                {
                    buffer &= ~(1UL << (6 - topClockBitNumber)); //Write 0
                }
                topClockBitNumber++;
            }
            else if (topClockBitNumber == 7)
            {
                //parity bit
                bool parity = (DATAPIN_TOP_READ_REG >> DATAPIN_TOP_READ) & 1;
                if (parity == (amount1bits % 2 == 0))
                {
                    int len = strlen(receivedText);
                    receivedText[len] = buffer;
                    receivedText[len + 1] = '\0';

                    ackHigh = true;
                    PORTA_OUT &= ~(1UL << 7);
                }
                else
                {
                    ackHigh = false;
                }
            }
        }

        break;

    case EventName::ReceivedTopDataFallingInterrupt:
        if (!hasClockLineRised)
        {
            DATAPIN_TOP_OUTPUT_REG |= 1UL << DATAPIN_TOP_OUTPUT;
            if (ackHigh)
            {
                DATAPIN_TOP_WRITE_REG |= 1UL << DATAPIN_TOP_WRITE; // set BB2 to High;
            }
            else
            {
                DATAPIN_TOP_WRITE_REG &= ~(1UL << DATAPIN_TOP_WRITE);
            }

            topClockBitNumber = 0;
            amount1bits = 0;
            buffer = 0b00000000;
            amount1bits = 0;

            sendAck = true;
            ackHigh = false;
        }
        break;

    case EventName::ReceivedTopDataRisingInterrupt:
        if (hasClockLineRised && topClockBitNumber == 0 && strlen(receivedText) > 9)
        {
            PORTA_OUT |= 1UL << 7;

            Event e{
                EventName::SendData,
                receivedText};

            _statemachine->setState(StateNumber::SENDING);

            _statemachine->handle_event(e);
        }
    default:
        break;
    }
}

void ReceivingState::on_exit()
{

    CLOCKPIN_TOP_INTERRUPT_REG &= ~(1UL << CLOCKPIN_TOP_INTERRUPT); //Enale intterrupt

    DATAPIN_TOP_INTERRUPT_REG &= ~(1UL << DATAPIN_TOP_INTERRUPT); //Enable intterrupt

    PORTA_PIN5CTRL &= ~(1UL << 3); //enable pullup resitor
    PORTA_PIN4CTRL &= ~(1UL << 3); //enable pullup resitor

    PORTA_OUT |= 1UL << 7;

    // topClockBitNumber = 0;
    // amount1bits = 0;
    // buffer = 0;
    // hasClockLineRised = false;
    // sendAck = false;
}