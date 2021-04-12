
#include <SPI.h>
#include <RF24.h>
#include <avr/sleep.h>
#include "statemachine.h"
#include "Interrupt.h"


#define SET_BIT(where, bit_number) ((where) |= 1 << (bit_number))
#define RESET_BIT(where, bit_number) ((where) &= ~(1 << (bit_number)))

#include "tokenprotocol.h"
#include "Statemachine.h"

Statemachine *machine;


void setup()
{
    machine = new Statemachine(); //Create the statemachine

    RESET_BIT(DDRA, DDRA1); //SET PA1 to output otherwise crash
    SET_BIT(DDRA, DDRA2);   //SET PA2 to output otherwise crash

    Interrupt::setStatemachine(machine);

    machine->on_init();
}

void loop()
{
    machine->on_execute();
}