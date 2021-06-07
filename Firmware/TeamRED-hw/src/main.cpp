#include <SPI.h>
#include <RF24.h>
#include "statemachine.h"
#include "Interrupt.h"
#include <util/delay.h>

Statemachine machine;
RF24 radio(4, 5); //radio variable

void setup()
{

  // Turn on the watchdog
  WDT_CTRLA |= 0x1;

  // Turn the light port to output
  PORTA_DIR |= 1UL << 7;

  // PORTA_OUT &= ~(1UL << 7);
  // _delay_ms(1000);

  // Set the light 
  PORTA_OUT |= 1UL << 7;
  Interrupt::setStatemachine(&machine);
  machine.on_init(&radio);
}

void loop()
{
  machine.on_execute();
}
