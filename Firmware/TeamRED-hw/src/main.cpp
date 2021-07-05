#include <SPI.h>
#include <RF24.h>
#include "statemachine.h"
#include "Interrupt.h"
#include <util/delay.h>
#include "Settings.h"

Statemachine machine; // variable for statemachine
RF24 radio(4, 5);     //radio variable

void setup()
{
  DATAPIN_BOTTOM_PIN_OUTPUT_REG |= 1UL << DATAPIN_BOTTOM_OUTPUT;
  DATAPIN_BOTTOM_WRITE_REG &= ~(1UL << DATAPIN_BOTTOM_WRITE); // datapin to low
  _delay_ms(400);                                             // wait for connection to settle

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
