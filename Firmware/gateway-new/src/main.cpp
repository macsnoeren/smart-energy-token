#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


const byte address[6] = "test1";

RF24 radio(9, 10);

bool test = false;


void setup()
{
  Serial.begin(9600);
  radio.begin();
  test = radio.isChipConnected();
  radio.setPALevel(RF24_PA_MIN);
  radio.openReadingPipe(0, address);
  radio.startListening();
}

void loop()
{
  if (radio.available())
  {
    char text[128] = "";
    radio.read(&text, sizeof(text));
    Serial.println(text);
  }
}