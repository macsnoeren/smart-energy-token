#ifndef STATEINITVARIABLES_H
#define STATEINITVARIABLES_H

#include "Statemachine.h"
#include <RF24.h>

class Statemachine;

struct StateInitVariables
{
    Statemachine *statemachine;
    bool isBase;
    RF24 *radio;
};

#endif
