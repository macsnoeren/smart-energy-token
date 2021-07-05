#ifndef SLEEPSTATE_H
#define SLEEPSTATE_H

#include "WString.h"
#include "Event.h"
#include <RF24.h>

class Statemachine;

class SleepState
{
private:
    Statemachine *_statemachine; // pointer that stores the hole statemachine
    RF24 *_radio; // radio variable for sending data if it is an base otherwise null
    bool _isBase; // boolean if the program is running on a base or token

public:
    void on_init(Statemachine *statemachine, RF24 *radio, bool isBase); // init method of the state
    void on_start();                                                    // method that gets called when the state starts
    void on_execute();                                                  // method that gets called every loop
    void on_event(Event e);                                             // method that gets called when an event has been received
    void on_exit();                                                     // method that gets called when the state switches and this state therefore ends
    SleepState()
    {
    }
};

#endif // SLEEPSTATE_H