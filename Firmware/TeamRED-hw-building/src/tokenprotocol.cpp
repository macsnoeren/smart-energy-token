#include "../include/tokenprotocol.h"
#include <RF24.h>
#include <avr/sleep.h>

#define SET_BIT(where, bit_number) ((where) |= 1 << (bit_number))
#define RESET_BIT(where, bit_number) ((where) &= ~(1 << (bit_number)))

// extern bool hasReceivedTopDataFalling;
// extern bool hasReceivedTopDataRising;
// extern bool hasReceivedTopClockRising;
// extern bool hasReceivedTopClockFalling;

// bool prevTopData = true;
// bool prevTopClock = true;

tokenprotocol *tokenprotocol::_instance = 0;

// ISR(PCINT0_vect)
// {

//     bool isPA7 = (PINA >> PINA7) & 1;
//     if (isPA7 && !prevTopClock)
//     {
//         //hasReceivedTopClockRising = true;
//         tokenprotocol *protocol = tokenprotocol::instance();
//         protocol->receivedTopClockRising();
//     }
//     else if (!isPA7 && prevTopClock)
//     {
//         //hasReceivedTopClockFalling = true;
//         tokenprotocol *protocol = tokenprotocol::instance();
//         protocol->receivedTopClockFalling();
//     }
//     prevTopClock = isPA7;
// }

// ISR(PCINT1_vect)
// {

//     bool isPB2 = (PINB >> PINB2) & 1;
//     if (prevTopData && !isPB2) //detect topdata falling
//     {
//         //hasReceivedTopDataFalling = true;
//         tokenprotocol *protocol = tokenprotocol::instance();
//         protocol->receivedTopDataFalling();
//     }
//     else if (!prevTopData && isPB2) // detect topdata rising
//     {
//         //hasReceivedTopDataRising = true;
//         tokenprotocol *protocol = tokenprotocol::instance();
//         protocol->receivedTopDataRising();
//     }
//     prevTopData = isPB2;
// }

void tokenprotocol::send(const char *text)
{
    SET_BIT(PORTA, PORTA4); //SET PA4 to high
    SET_BIT(PORTA, PORTA5); //SET PA5 to high

    RESET_BIT(PORTA, PORTA4); //set datapin to low

    for (uint8_t i = 0; i < strlen(text); i++)
    {
        char character = text[i];
        for (uint8_t j = 0; j < 8; j++)
        {
            RESET_BIT(PORTA, PORTA5); //Set Clock pin to 0
            delay(tokenProtocolDelay);

            if (!!(character & (1 << (7 - j)))) //Set datapin to bit value
            {
                SET_BIT(PORTA, PORTA4); // SET DATAPIN TO 1
            }
            else
            {
                RESET_BIT(PORTA, PORTA4); // SET DATAPIN TO 0
            }
            delay(tokenProtocolDelay);

            SET_BIT(PORTA, PORTA5); //SET Clock pin to 1
            delay(tokenProtocolDelay);
        }
    }

    RESET_BIT(PORTA, PORTA4); //set datapin to low

    delay(tokenProtocolDelay);
    SET_BIT(PORTA, PORTA4); //set datapin to high
    delay(tokenProtocolDelay);

    RESET_BIT(PORTA, PORTA4); //set datapin to low
}

void tokenprotocol::end()
{
    PCMSK0 &= ~(1UL << PCINT7);  //Clear the pa7 interrupt
    PCMSK1 &= ~(1UL << PCINT10); //Clear the pb2 interrupt

    String result = text; //copy the text; otherwise it won't send the text;

    if (text != "")
    {
        radio->write(result.c_str(), strlen(result.c_str())); //send the text throug the receiver;

        // if (isBuilding)
        // {
        //     radio->write(result.c_str(), strlen(result.c_str())); //send the text throug the receiver;
        // }else
        // {
        //     send(result.c_str());
        // }
    }
    init();
    hasReceivedSomething = true;
}

void tokenprotocol::receivedTopClockFalling()
{
    hasClockLineRised = false;
}

void tokenprotocol::receivedTopDataRising()
{
    if (hasReceivedSomething)
    {
        String text = "removed token";
        radio->write(text.c_str(), strlen(text.c_str())); //send the text throug the receiver;
        hasReceivedSomething = false;
    }
    else if (hasClockLineRised)
    {
        end();
    }
}
void tokenprotocol::receivedTopClockRising()
{
    hasClockLineRised = true;  //Set hasclock rised to true condition for stop
    if (topClockBitNumber < 8) //if the bitnumber is les then 8
    {
        bool bit = (PINB >> PINB2) & 1; // read PB2
        if (bit)
        {
            SET_BIT(toWrite, 7 - topClockBitNumber);
        }
        else
        {
            RESET_BIT(toWrite, 7 - topClockBitNumber);
        }
        topClockBitNumber++;
    }
    if (topClockBitNumber == 8) //when the 8th bit has been added write the buffer to the final
    {
        topClockBitNumber = 0;
        text += toWrite;
        toWrite = 0;
    }
}
void tokenprotocol::receivedTopDataFalling()
{
}

void tokenprotocol::init()
{
    // init values for reading data
    text = "";
    //readyToWriteToRadio = false;
    toWrite = 0;
    topClockBitNumber = 0;
    hasClockLineRised = false;

    hasReceivedSomething = false;

    if (!isBuilding) //Set the bottom ports to HIGH (Starting con) if the token is not an building
    {
        SET_BIT(DDRA, DDRA4); //SET PA4 to output
        SET_BIT(DDRA, DDRA5); //SET PA5 to output

        SET_BIT(PORTA, PORTA4); //SET PA4 to high
        SET_BIT(PORTA, PORTA5); // SET PA5 to high
    }

    PUEB |= 1UL << 2; //enable pullup resitor for PB2
    //PUEA |= 1UL << 7; //enable pullup resitor for PA7

    GIMSK |= 1UL << PCIE0; //set interrup for pa7
    PCMSK0 |= 1UL << PCINT7;

    GIMSK |= 1UL << PCIE1; //set interrupt for pb2
    PCMSK1 |= 1UL << PCINT10;

    sei();
}

void tokenprotocol::setup(RF24 *_radio, bool _isBuilding)
{
    isBuilding = _isBuilding;
    radio = _radio;
    init();
}

tokenprotocol::tokenprotocol()
{
}

tokenprotocol::~tokenprotocol()
{
}
