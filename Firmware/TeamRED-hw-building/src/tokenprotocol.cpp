#include "../include/tokenprotocol.h"
#include <Arduino.h>
#include <RF24.h>

#define SET_BIT(where, bit_number) ((where) |= 1 << (bit_number))
#define RESET_BIT(where, bit_number) ((where) &= ~(1 << (bit_number)))

// extern bool hasReceivedTopDataFalling;
// extern bool hasReceivedTopDataRising;
// extern bool hasReceivedTopClockRising;
// extern bool hasReceivedTopClockFalling;

bool prevTopData = true;
bool prevTopClock = true;

tokenprotocol *tokenprotocol::_instance = 0;

ISR(PCINT0_vect)
{
    bool isPA7 = (PINA >> PINA7) & 1;
    if (isPA7 && !prevTopClock)
    {
        //hasReceivedTopClockRising = true;
        tokenprotocol *protocol = tokenprotocol::instance();
        protocol->receivedTopClockRising();
    }
    else if (!isPA7 && prevTopClock)
    {
        //hasReceivedTopClockFalling = true;
        tokenprotocol *protocol = tokenprotocol::instance();
        protocol->receivedTopClockFalling();
    }
    prevTopClock = isPA7;
}

ISR(PCINT1_vect)
{
    bool isPB2 = (PINB >> PINB2) & 1;
    if (prevTopData && !isPB2) //detect topdata falling
    {
        //hasReceivedTopDataFalling = true;
        tokenprotocol *protocol = tokenprotocol::instance();
        protocol->receivedTopDataFalling();
    }
    else if (!prevTopData && isPB2) // detect topdata rising
    {
        //hasReceivedTopDataRising = true;
        tokenprotocol *protocol = tokenprotocol::instance();
        protocol->receivedTopDataRising();
    }
    prevTopData = isPB2;
}

void tokenprotocol::send(const char *text)
{

    uint8_t dataPin = bottomDataPin;
    uint8_t clockPin = bottomClockPin;

    digitalWrite(dataPin, LOW);

    for (uint8_t i = 0; i < strlen(text); i++)
    {
        char character = text[i];
        for (uint8_t j = 0; j < 8; j++)
        {
            digitalWrite(clockPin, 0);
            delay(tokenProtocolDelay);
            digitalWrite(dataPin, !!(character & (1 << (7 - j))));
            delay(tokenProtocolDelay);
            digitalWrite(clockPin, 1);
            delay(tokenProtocolDelay);
        }
    }
    digitalWrite(dataPin, 0);
    delay(tokenProtocolDelay);
    digitalWrite(dataPin, 1);
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
}

void tokenprotocol::receivedTopClockFalling()
{
    hasClockLineRised = false;
}

void tokenprotocol::receivedTopDataRising()
{
    if (hasClockLineRised)
    {
        end();
    }
}
void tokenprotocol::receivedTopClockRising()
{
    hasClockLineRised = true; //Set hasclock rised to true condition for stop
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

    if (!isBuilding) //Set the bottom ports to HIGH (Starting con) if the token is not an building
    {
        pinMode(PA4, OUTPUT);
        pinMode(PA5, OUTPUT);
        digitalWrite(PA5, HIGH);
        digitalWrite(PA4, HIGH);
    }

    PUEB |= 1UL << 2; //enable pullup resitor for PB2
    PUEA |= 1UL << 7; //enable pullup resitor for PA7

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
