
#include <SPI.h>
#include <RF24.h>
#include <avr/sleep.h>

#define SET_BIT(where, bit_number) ((where) |= 1 << (bit_number))
#define RESET_BIT(where, bit_number) ((where) &= ~(1 << (bit_number)))

#include "tokenprotocol.h"

#define CE_PIN 3
#define CSN_PIN 0

bool isBase = true;

RF24 radio(PA3, PA2);

const byte address[6] = "buil1";

void setup()
{
    RESET_BIT(DDRA, DDRA1); //SET PA1 to output otherwise crash
    SET_BIT(DDRA, DDRA2);   //SET PA2 to output otherwise crash

    isBase = radio.begin();
    if (isBase)
    {
        isBase = radio.begin();

        radio.openWritingPipe(address);
        radio.setPALevel(RF24_PA_MIN);
        radio.stopListening();
        delay(4000);
        String text = "Starting";
        radio.write(text.c_str(), strlen(text.c_str()));
    }
    else
    {
        SPI.end();
    }

    if (isBase)
    {
        tokenprotocol *protocol = tokenprotocol::instance();
        protocol->setup(&radio, isBase);

        // disable analog comparator 0 and 1
        ACSR0A |= _BV(ACD0);
        ACSR1A |= _BV(ACD1);

        //disable adc
        ADCSRA &= ~(1 << ADEN);

        set_sleep_mode(SLEEP_MODE_IDLE);

        sleep_enable();
        sleep_mode();
    }
    else
    {
        tokenprotocol *protocol = tokenprotocol::instance();
        protocol->setup(nullptr, isBase);

        // delay(300);

        // String text = "Starting...";
        // protocol->send(text.c_str());

        delay(1000);

        String text = "code:7HiP1qyKJr";
        protocol->send(text.c_str());
    }
}

volatile bool hasReceivedTopDataFalling = false;
volatile bool hasReceivedTopDataRising = false;
volatile bool hasReceivedTopClockRising = false;
volatile bool hasReceivedTopClockFalling = false;

void loop()
{
    if (isBase)
    {
        String text = "loop...";
        radio.write(text.c_str(), strlen(text.c_str()));

        delay(100);

        set_sleep_mode(SLEEP_MODE_PWR_DOWN);

        sleep_mode();
    }

    if (!isBase)
    {
        // tokenprotocol *protocol = tokenprotocol::instance();

        // String text = "hello from the token";
        // protocol->send(text.c_str());
        // delay(1000);
    }
    else
    {
        //tokenprotocol *protocol = tokenprotocol::instance();

        // if (hasReceivedTopDataFalling)
        // {
        //   hasReceivedTopDataFalling = false;
        //   String text = "data falling";
        //   radio.write(text.c_str(), strlen(text.c_str()));
        // }
        // else if (hasReceivedTopDataRising)
        // {
        //   hasReceivedTopDataRising = false;
        //   String text = "data rising";
        //   radio.write(text.c_str(), strlen(text.c_str()));
        // }
        // if (hasReceivedTopClockRising)
        // {
        //   hasReceivedTopClockRising = false;
        //   String text = "clock rising";
        //   radio.write(text.c_str(), strlen(text.c_str()));
        // }
        // else if (hasReceivedTopClockFalling)
        // {
        //   hasReceivedTopClockFalling = false;
        //   String text = "clock falling";
        //   radio.write(text.c_str(), strlen(text.c_str()));
        // }
    }

    delay(1);
}