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
    hasStarted = false;
    topClockBitNumber = 0;
    amount1bits = 0;
    buffer = 0;
    receivedText = "";
    hasClockLineRised = false;
    _statemachine->hasTopToken = true;
    sendAck = false;

    // DDRB &= ~(1UL << DDRB2); //TUrn PB2 to input
    // DDRA &= ~(1UL << DDRA7); //TUrn PA7 to input

    GIMSK |= 1UL << PCIE0; //set interrup for pa7
    PCMSK0 |= 1UL << PCINT7;

    GIMSK |= 1UL << PCIE1; //set interrupt for pb2
    PCMSK1 |= 1UL << PCINT10;

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
    if (!_isBase)
    {
    }
    else
    {
        if (hasStarted)
        {
            //_radio->write(receivedText2, strlen(receivedText2));
        }
    }

    delay(1);
}

//Handels events when received
void ReceivingState::on_event(Event e)
{
    switch (e.name)
    {
    case EventName::ReceivedTopClockFallingInterrupt:
        hasClockLineRised = false;

        // if (!hasStarted)
        // {
        //     hasStarted = true;
        // }
        break;
    case EventName::ReceivedTopClockRisingInterrupt:
        hasClockLineRised = true;

        if (sendAck)
        {
            // String text = "Send ack";
            // _radio->write(text.c_str(), strlen(text.c_str()));

            // GIMSK |= 1UL << PCIE1; //set interrupt for pb2
            // PCMSK1 |= 1UL << PCINT10;

            // DDRB &= ~(1UL << DDRB2); //TUrn PB2 to input

            sendAck = false;
        }
        else
        {
            if (topClockBitNumber <= 6)
            {
                if ((PINB >> PINB2) & 1) // read PB2 (Datapint)
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
                bool parity = (PINB >> PINB2) & 1;
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
            //String text = "Send ack";
            //_radio->write(text.c_str(), strlen(text.c_str()));

            // DDRB |= 1UL << DDRB2; //TUrn PB2 to output

            // GIMSK &= ~(1UL << PCIE1); //disable interrupt for pb2
            // PCMSK1 &= ~(1UL << PCINT10);

            if (ackHigh)
            {
                PORTB |= 1UL << PORTB2; // set BB2 to High;
            }
            else
            {
                PORTB &= ~(1UL << PORTB2);
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
        hasStarted = true;
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
    hasStarted = false;
    topClockBitNumber = 0;
    amount1bits = 0;
    buffer = 0;
    receivedText = "";
    hasClockLineRised = false;
    sendAck = false;
}