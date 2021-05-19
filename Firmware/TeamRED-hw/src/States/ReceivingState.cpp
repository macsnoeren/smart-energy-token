#include "States/ReceivingState.h"
#include "Settings.h"
#include "Statemachine.h"

void ReceivingState::on_init(Statemachine *statemachine, RF24 *radio, bool isBase)
{
    _statemachine = statemachine;
    _radio = radio;
    _isBase = isBase;
}

void ReceivingState::on_start()
{
    // init all variables that need to be reset when the state enters
    topClockBitNumber = 0;
    amount1bits = 0;
    buffer = 0;
    hasClockLineRised = false;
    _statemachine->hasTopToken = true;
    sendAck = false;
    receivedText2[0] = '\0';

    PORTA_OUT &= ~(1UL << 7);

    CLOCKPIN_TOP_INTERRUPT_REG |= 1UL << CLOCKPIN_TOP_INTERRUPT; //Enale intterrupt

    DATAPIN_TOP_INTERRUPT_REG |= 1UL << DATAPIN_TOP_INTERRUPT; //Enable intterrupt

    //PORTA_PIN5CTRL |= 1UL << 3; //enable pullup resitor for PB2
    PORTA_PIN4CTRL |= 1UL << 3; //enable pullup resitor for PA4

    // //Send ack back;
    // DATAPIN_TOP_OUTPUT_REG |= 1UL << DATAPIN_TOP_OUTPUT; //Set DATA to OUTPUT
    // delay(tokenProtocolDelay);
    // DATAPIN_TOP_WRITE_REG |= 1UL << DATAPIN_TOP_WRITE; // set BB2 to High;
    // delay(2 * tokenProtocolDelay);

    // DATAPIN_TOP_OUTPUT_REG &= ~(1UL << DATAPIN_TOP_OUTPUT); //SET DATA to INput
    // delay(2* tokenProtocolDelay);

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
                    binary[topClockBitNumber] = '1';
                    amount1bits++;
                }
                else
                {
                    buffer &= ~(1UL << (6 - topClockBitNumber)); //Write 0
                    binary[topClockBitNumber] = '0';
                }
                topClockBitNumber++;
            }
            else if (topClockBitNumber == 7)
            {
                //parity bit
                bool parity = (DATAPIN_TOP_READ_REG >> DATAPIN_TOP_READ) & 1;
                if (parity == (amount1bits % 2 == 0))
                {
                    int len = strlen(receivedText2);
                    receivedText2[len] = buffer;
                    receivedText2[len + 1] = '\0';

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
        if (hasClockLineRised && topClockBitNumber == 0 && strlen(receivedText2) > 9)
        {

            Event e{
                EventName::SendData,
                receivedText2};

            _statemachine->setState(StateNumber::SENDING);
            _statemachine->handle_event(e);
        }
    default:
        break;
    }
}

void ReceivingState::on_exit()
{
    PORTA_OUT |= 1UL << 7;

    topClockBitNumber = 0;
    amount1bits = 0;
    buffer = 0;
    hasClockLineRised = false;
    sendAck = false;
}