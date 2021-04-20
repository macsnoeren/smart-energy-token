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
    receivedText = "";
    hasClockLineRised = false;
    _statemachine->hasTopToken = true;
    sendAck = false;

    GIMSK |= 1UL << CLOCKPIN_TOP_INTERRUPT_GIMSK; //set interrup for pa7
    CLOCKPIN_TOP_INTERRUPT_REG |= 1UL << CLOCKPIN_TOP_INTERRUPT;

    GIMSK |= 1UL << DATAPIN_TOP_INTERRUPT_GIMSK; //set interrupt for pb2
    DATAPIN_TOP_INTERRUPT_REG |= 1UL << DATAPIN_TOP_INTERRUPT;

    PUEB |= 1UL << 2; //enable pullup resitor for PB2
    PUEA |= 1UL << 7; //enable pullup resitor for PA7

    sei();

    if (debug)
    {
        if (_isBase)
        {
            delay(100);

            String text = "Start Receiving";
            _radio->write(text.c_str(), strlen(text.c_str()));

            delay(100);
        }
    }
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
                    int len = strlen(receivedText2);
                    receivedText2[len] = buffer;
                    receivedText2[len + 1] = '\0';

                    receivedText += buffer;
                    ackHigh = true;
                }
                else
                {
                    ackHigh = false;
                    if (_isBase)
                    {
                        String text = "Wrong bit";
                        _radio->write(text.c_str(), strlen(text.c_str()));
                    }
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
    topClockBitNumber = 0;
    amount1bits = 0;
    buffer = 0;
    receivedText = "";
    hasClockLineRised = false;
    sendAck = false;
}