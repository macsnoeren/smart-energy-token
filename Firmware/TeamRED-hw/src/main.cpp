#include <SPI.h>
#include <RF24.h>
#include "statemachine.h"
#include "Interrupt.h"

Statemachine machine;
RF24 radio(4, 5); //radio variable

void setup()
{
  PORTA_DIR |= 1UL << 7;
  PORTA_OUT |= 1UL << 7;
  Interrupt::setStatemachine(&machine);
  machine.on_init(&radio);
}

void loop()
{
  machine.on_execute();
}
