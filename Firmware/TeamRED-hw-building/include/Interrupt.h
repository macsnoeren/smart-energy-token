#ifndef INTERRUPT_H
#define INTERRUPT_H

#include "Statemachine.h"

class Interrupt
{
private:

public:
    static void setStatemachine(Statemachine *statemachine);
};

#endif