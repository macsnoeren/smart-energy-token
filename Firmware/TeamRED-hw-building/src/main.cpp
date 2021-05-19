
#include <SPI.h>
#include <RF24.h>
#include <avr/sleep.h>
#include "statemachine.h"
#include "Interrupt.h"

#define SET_BIT(where, bit_number) ((where) |= 1 << (bit_number))
#define RESET_BIT(where, bit_number) ((where) &= ~(1 << (bit_number)))


Statemachine machine;
RF24 radio(PA3, PA2); //radio variable

void setup()
{
    RESET_BIT(DDRA, DDRA1); //SET PA1 to output otherwise crash
    SET_BIT(DDRA, DDRA2);   //SET PA2 to output otherwise crash

    Interrupt::setStatemachine(&machine);


    machine.on_init(&radio);

}

void loop()
{
    machine.on_execute();
}