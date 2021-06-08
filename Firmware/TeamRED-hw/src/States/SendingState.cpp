#include "States/SendingState.h"
#include <avr/sleep.h>
#include "Settings.h"
#include <util/delay.h>
#include "Statemachine.h"
#include "WString.h"
#include "Serialnumber.h"

void SendingState::on_init(Statemachine *statemachine, RF24 *radio, bool isBase)
{
    _statemachine = statemachine;
    _radio = radio;
    _isBase = isBase;

    toSend[0] = '\0';
}

void SendingState::on_start()
{
    // init all variables that need to be reset when the state enters
    waitingForAck = false;
    currentChar = 0;
    tries = 0;

    if (!_isBase)
    {
        CLOCKPIN_BOTTOM_PIN_OUTPUT_REG |= 1UL << CLOCKPIN_BOTTOM_OUTPUT; //TUrn PA5 to output

        CLOCKPIN_BOTTOM_WRITE_REG |= 1UL << CLOCKPIN_BOTTOM_WRITE; //Set clock to high
        // DATAPIN_BOTTOM_WRITE_REG |= 1UL << DATAPIN_BOTTOM_WRITE;   //Set data to high

        _delay_ms(tokenProtocolDelay);

        CLOCKPIN_BOTTOM_WRITE_REG &= ~(1UL << CLOCKPIN_BOTTOM_WRITE); //Set PA5 to LOW Start bit

        _delay_ms(40);

        DATAPIN_BOTTOM_PIN_OUTPUT_REG |= 1UL << DATAPIN_BOTTOM_OUTPUT; //Turn PA4 to output
    }
}

//Main loop of the state
void SendingState::on_execute()
{
    if (_isBase)
    {
        buildingcode[0] = '\0';
        strcat(buildingcode, getSerialNumber());
        strcat(buildingcode, toSend);

        char *ptr = strtok(buildingcode, delim);

        while (ptr != NULL)
        {
            bool doneWriting = false;
            uint8_t loop = 0;
            while (!doneWriting)
            {
                doneWriting = _radio->write(ptr, strlen(ptr));
                loop++;
                if (loop >= FAILEDAMOUNT)
                {
                    doneWriting = true;
                }
            }
            ptr = strtok(NULL, delim);
        }

        bool doneWriting = false;
        uint8_t loop = 0;
        while (!doneWriting)
        {
            doneWriting = _radio->write(dot, strlen(dot));
            loop++;
            if (loop >= FAILEDAMOUNT)
            {
                doneWriting = true;
            }
        }

        _statemachine->setState(StateNumber::SLEEP);
        toSend[0] = '\0';
    }
    else
    {
        buildingcode[0] = '\0';

        strcat(buildingcode, getSerialNumber());
        strcat(buildingcode, toSend);
        _delay_ms(tokenProtocolDelay);
        char character = buildingcode[currentChar];
        uint8_t amount1bits = 0;
        for (uint8_t j = 0; j < 7; j++)
        {
            CLOCKPIN_BOTTOM_WRITE_REG &= ~(1UL << CLOCKPIN_BOTTOM_WRITE); //clock to LOW
            _delay_ms(tokenProtocolDelay);

            if (!!(character & (1 << (6 - j)))) //Set datapin to bit value
            {
                DATAPIN_BOTTOM_WRITE_REG |= 1UL << DATAPIN_BOTTOM_WRITE; //SET DATAPIN TO HIGH

                amount1bits++;
            }
            else
            {
                DATAPIN_BOTTOM_WRITE_REG &= ~(1UL << DATAPIN_BOTTOM_WRITE); //SET DATAPIN TO LOW
                PORTA_OUT &= ~(1UL << 7);
            }
            _delay_ms(tokenProtocolDelay);
            PORTA_OUT |= 1UL << 7;

            CLOCKPIN_BOTTOM_WRITE_REG |= 1UL << CLOCKPIN_BOTTOM_WRITE; //SET CLOCKPIN TO HIGH
            _delay_ms(tokenProtocolDelay);
            DATAPIN_BOTTOM_WRITE_REG &= ~(1UL << DATAPIN_BOTTOM_WRITE); //SET DATAPIN TO LOW
            _delay_ms(tokenProtocolDelay);
        }

        //Parity bit evenparity
        CLOCKPIN_BOTTOM_WRITE_REG &= ~(1UL << CLOCKPIN_BOTTOM_WRITE); //clock to LOW
        _delay_ms(tokenProtocolDelay);

        if (amount1bits % 2 == 0)
        {
            DATAPIN_BOTTOM_WRITE_REG |= 1UL << DATAPIN_BOTTOM_WRITE; //SET DATAPIN TO HIGH
        }
        else
        {
            DATAPIN_BOTTOM_WRITE_REG &= ~(1UL << DATAPIN_BOTTOM_WRITE); //SET DATAPIN TO LOW
        }
        _delay_ms(tokenProtocolDelay);

        CLOCKPIN_BOTTOM_WRITE_REG |= 1UL << CLOCKPIN_BOTTOM_WRITE; //SET CLOCKPIN TO HIGH
        _delay_ms(tokenProtocolDelay);

        //ACK
        CLOCKPIN_BOTTOM_WRITE_REG &= ~(1UL << CLOCKPIN_BOTTOM_WRITE); //clock to LOW
        _delay_ms(tokenProtocolDelay);

        DATAPIN_BOTTOM_WRITE_REG |= 1UL << DATAPIN_BOTTOM_WRITE; // Set DATA HIgh
        _delay_ms(tokenProtocolDelay);

        DATAPIN_BOTTOM_WRITE_REG &= ~(1UL << DATAPIN_BOTTOM_WRITE); // Set data to LOW
        _delay_ms(tokenProtocolDelay);

        DATAPIN_BOTTOM_PIN_OUTPUT_REG &= ~(1UL << DATAPIN_BOTTOM_OUTPUT); //Turn PA4 to input data to input
        _delay_ms(4 * tokenProtocolDelay);

        //Set the datapint to input
        if ((DATAPIN_BOTTOM_READ_REG >> DATAPIN_BOTTOM_READ) & 1) //Read DATA PIN
        {
            currentChar++;
            tries = 0;
        }
        else
        {
            tries++;
            if (tries > FAILEDAMOUNT)
            {
                _statemachine->setState(StateNumber::Error);
                return;
            }
        }
        _delay_ms(tokenProtocolDelay);

        CLOCKPIN_BOTTOM_WRITE_REG |= 1UL << CLOCKPIN_BOTTOM_WRITE; //SET CLOCKPIN TO HIGH
        _delay_ms(tokenProtocolDelay);

        //Set data to output
        DATAPIN_BOTTOM_PIN_OUTPUT_REG |= 1UL << DATAPIN_BOTTOM_OUTPUT; //Turn PA4 to output

        DATAPIN_BOTTOM_WRITE_REG &= ~(1UL << DATAPIN_BOTTOM_WRITE); //Set PA4 to LOW
        _delay_ms(tokenProtocolDelay);

        if (currentChar >= strlen(buildingcode))
        {
            //End bit
            _delay_ms(tokenProtocolDelay);
            DATAPIN_BOTTOM_WRITE_REG |= 1UL << DATAPIN_BOTTOM_WRITE; //SET PA4 to high
            _delay_ms(tokenProtocolDelay);
            DATAPIN_BOTTOM_WRITE_REG &= ~(1UL << DATAPIN_BOTTOM_WRITE); //Set PA4 to LOW
            _delay_ms(tokenProtocolDelay);

            //If last character has been send
            toSend[0] = '\0';

            _statemachine->setState(StateNumber::SLEEP);
        }
    }
}

//Handels events when received
void SendingState::on_event(Event e)
{
    switch (e.name)
    {
    case EventName::SendData:
        strcpy(toSend, e.eventData);
        size_t sz = strlen(toSend);
        break;

    default:
        break;
    }
}

void SendingState::on_exit()
{
    toSend[0] = '\0';

    if (!_isBase)
    {
        //DATAPIN_BOTTOM_PIN_OUTPUT_REG &= ~(1UL << DATAPIN_BOTTOM_OUTPUT);   //Turn PA4 to output
        DATAPIN_BOTTOM_WRITE_REG &= ~(1UL << DATAPIN_BOTTOM_WRITE);         // Set DATA HIgh
        CLOCKPIN_BOTTOM_PIN_OUTPUT_REG &= ~(1UL << CLOCKPIN_BOTTOM_OUTPUT); //TUrn PA5 to output
    }
    PORTA_OUT |= 1UL << 7;
}