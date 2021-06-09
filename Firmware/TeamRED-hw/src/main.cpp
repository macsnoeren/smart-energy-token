#include <SPI.h>
#include <RF24.h>
#include "statemachine.h"
#include "Interrupt.h"
#include <util/delay.h>

Statemachine machine;
RF24 radio(4, 5); //radio variable

void setup()
{
  // Turn the light port to output
  PORTA_DIR |= 1UL << 7;

  // Set the light 
  PORTA_OUT |= 1UL << 7;

  // Set the statemachine pointer for the interrupts to use
  Interrupt::setStatemachine(&machine);

  // Init the statemachine
  machine.on_init(&radio);
}

void loop()
{
  //Exechute the loop function of the states
  machine.on_execute();
}
