
#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define SET_BIT(where, bit_number) ((where) |= 1 << (bit_number))
#define RESET_BIT(where, bit_number) ((where) &= ~(1 << (bit_number)))

#include "tokenprotocol.h"

#define CE_PIN 3
#define CSN_PIN 0

bool isBuilding = true;
bool isReceiver = false;

RF24 radio(PA3, PA2);

const byte address[6] = "buil1";

void setup()
{
  pinMode(PA1, INPUT);  //otherwise crash
  pinMode(PA2, OUTPUT); //otherwise crash
  pinMode(PA7, OUTPUT);
  digitalWrite(PA7, LOW);
  pinMode(PA7, INPUT);

  isBuilding = radio.begin();
  if (isBuilding)
  {
    isBuilding = radio.begin();

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

  if (isBuilding)
  {
    tokenprotocol *protocol = tokenprotocol::instance();
    protocol->setup(&radio, isBuilding);
  }
  else
  {
    tokenprotocol *protocol = tokenprotocol::instance();
    protocol->setup(nullptr, isBuilding);

    delay(300);
    
    String text = "code:7HiP1qyKJr";
    protocol->send(text.c_str());
  }
}

// volatile bool hasReceivedTopDataFalling = false;
// volatile bool hasReceivedTopDataRising = false;
// volatile bool hasReceivedTopClockRising = false;
// volatile bool hasReceivedTopClockFalling = false;

void loop()
{
  if (!isBuilding)
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