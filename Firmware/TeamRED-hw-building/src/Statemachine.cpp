#include "Statemachine.h"
#include "States/InitState.h"
#include "States/ReceivingState.h"
#include "States/SleepState.h"
#include "States/RemovedTopState.h"

void Statemachine::on_init()
{
    //Init radio before everything cause everystate needs the radio for debugging
    RF24 radio(PA3, PA2);            //radio variable
    const byte address[6] = "buil1"; //Addres of the radio
    bool isBase = radio.begin();     //check if radio is connected
    if (isBase)
    {
        radio.openWritingPipe(address); //Set the radio writing addres
        radio.setPALevel(RF24_PA_MIN);  //Set the PA level
        radio.stopListening();          //Set the radio to send mode
        delay(4000);                    //Delay for the radio to proper initalize might not be needed
    }
    else
    {
        SPI.end();
    }

    //Init state variables that they all need
    StateInitVariables initVar = {
        this,
        isBase,
        &radio};

    _currentState = StateNumber::INIT; //Set the currentstate to the startState

    // TODO init states
    states[StateNumber::INIT] = new InitState();
    states[StateNumber::RECEIVING] = new ReceivingState();
    states[StateNumber::REMOVEDTOP] = new RemovedTopState();
    states[StateNumber::SENDING] = new InitState();
    states[StateNumber::SLEEP] = new SleepState();

    for (size_t i = 0; i < NumberOfStates; i++)
    {
        states[i]->on_init(initVar);
    }

    states[_currentState]->on_start();
}

void Statemachine::on_execute()
{
    states[_currentState]->on_execute();
}

void Statemachine::handle_event(Event e)
{
    states[_currentState]->on_event(e);
}

void Statemachine::setState(StateNumber newState)
{
    states[_currentState]->on_exit();

    _currentState = newState;

    states[_currentState]->on_start();
}

Statemachine::Statemachine()
{
}

Statemachine::~Statemachine()
{
}