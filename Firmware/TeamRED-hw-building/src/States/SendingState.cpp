#include "States/SendingState.h"
#include <avr/sleep.h>
#include "Settings.h"
#include <util/delay.h>
#include "Statemachine.h"
#include "WString.h"

void SendingState::on_init(Statemachine *statemachine, RF24 *radio, bool isBase)
{
    _statemachine = statemachine;
    _radio = radio;
    _isBase = isBase;

    toSend = "";
}

void SendingState::on_start()
{
    // init all variables that need to be reset when the state enters
    // if (debug)
    // {
    //     if (_isBase)
    //     {
    //         String text = "Sending state";
    //         _radio->write(text.c_str(), strlen(text.c_str()));
    //     }
    // }
    waitingForAck = false;
    timeSinceSendForAck = 0;
    currentChar = 0;

    if (!_isBase)
    {
        delay(500);

        DDRA |= 1UL << DDRA5; //TUrn PA5 to output
        DDRA |= 1UL << DDRA4; //Turn PA4 to output

        PORTA |= 1UL << PORTA5; //Set PA5 to high

        _delay_ms(tokenProtocolDelay);

        PORTA &= ~(1UL << PORTA5); //Set PA5 to LOW Start bit

        delay(500);

        // PORTA |= 1UL << PORTA4; //Set PA4 to high

        // _delay_ms(tokenProtocolDelay);

        // PORTA &= ~(1UL << PORTA4); //Set PA4 to LOW
    }
}

//Main loop of the state
void SendingState::on_execute()
{
    if (_isBase)
    {
        //_radio->write(toSend, strlen(toSend));

        char buildingcode[] = "building12,";
        strcat(buildingcode, toSend);
        
        _delay_ms(tokenProtocolDelay);
        _radio->write(buildingcode, strlen(buildingcode));
        _delay_ms(tokenProtocolDelay);
        _statemachine->setState(StateNumber::SLEEP);
        toSend[0] = '\0';
    }
    else
    {

        char tokencode[] = "token1234,";
        strcat(tokencode, toSend);

        char character = tokencode[currentChar];
        uint8_t amount1bits = 0;
        for (uint8_t j = 0; j < 7; j++)
        {
            PORTA &= ~(1UL << PORTA5); //clock to LOW
            _delay_ms(tokenProtocolDelay);

            if (!!(character & (1 << (6 - j)))) //Set datapin to bit value
            {
                PORTA |= 1UL << PORT4; //SET DATAPIN TO HIGH
                amount1bits++;
            }
            else
            {
                PORTA &= ~(1UL << PORTA4); //SET DATAPIN TO LOW
            }
            _delay_ms(tokenProtocolDelay);

            PORTA |= 1UL << PORTA5; //SET CLOCKPIN TO HIGH
            _delay_ms(tokenProtocolDelay);
            PORTA &= ~(1UL << PORTA4); //SET DATAPIN TO LOW
            _delay_ms(tokenProtocolDelay);
        }

        //Parity bit evenparity
        PORTA &= ~(1UL << PORTA5); //clock to LOW
        _delay_ms(tokenProtocolDelay);

        if (amount1bits % 2 == 0)
        {
            PORTA |= 1UL << PORT4; //SET DATAPIN TO HIGH
        }
        else
        {
            PORTA &= ~(1UL << PORTA4); //SET DATAPIN TO LOW
        }
        _delay_ms(tokenProtocolDelay);

        PORTA |= 1UL << PORTA5; //SET CLOCKPIN TO HIGH
        _delay_ms(tokenProtocolDelay);

        //ACK
        PORTA &= ~(1UL << PORTA5); //clock to LOW
        _delay_ms(tokenProtocolDelay);

        PORTA |= 1UL << PORTA4; // Set DATA HIgh
        _delay_ms(tokenProtocolDelay);

        PORTA &= ~(1UL << PORTA4); // Set data to LOW
        _delay_ms(tokenProtocolDelay);

        DDRA &= ~(1UL << DDRA4);   //Turn PA4 to input data to input
        _delay_ms(tokenProtocolDelay);

        //Set the datapint to input
        if ((PINA >> PINA4) & 1) //Read DATA PIN
        {
            currentChar++;
        }
        _delay_ms(tokenProtocolDelay);

        PORTA |= 1UL << PORTA5; //SET CLOCKPIN TO HIGH
        _delay_ms(tokenProtocolDelay);

        //Set data to output
        DDRA |= 1UL << DDRA4; //Turn PA4 to output

        PORTA &= ~(1UL << PORTA4); //Set PA4 to LOW
        _delay_ms(tokenProtocolDelay);

        if (currentChar >= strlen(tokencode))
        {
            //currentChar = 0;
            //End bit
            _delay_ms(40);
            PORTA |= 1UL << PORTA4; //SET PA4 to high
            _delay_ms(20);
            PORTA &= ~(1UL << PORTA4); //Set PA4 to LOW
            _delay_ms(20);

            //If last character has been send
            _statemachine->setState(StateNumber::SLEEP);
        }
    }
}

//Handels events when received
void SendingState::on_event(Event e)
{
    hasEvent = true;

    switch (e.name)
    {
    case EventName::SendData:
        toSend = e.eventData;
        break;

    default:
        break;
    }
}

void SendingState::on_exit()
{
    //pinMode(PORTA4,INPUT);
    //pinMode(PORTA5,INPUT);
    // DDRA &= ~(1UL << DDRA4); //Turn PA4 to input
    // DDRA &= ~(1UL << DDRA5); //Turn PA5 to input
}