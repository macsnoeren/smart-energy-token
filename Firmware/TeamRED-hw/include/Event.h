#ifndef EVENT_H
#define EVENT_H

#include <WString.h>

enum EventName {
    ReceivedTopClockRisingInterrupt,
    ReceivedTopClockFallingInterrupt,
    ReceivedTopDataRisingInterrupt,
    ReceivedTopDataFallingInterrupt,
    SendData,  // event to send the received data to to be send
    ErrorInterrupt // event that gets thrown if something goes wrong with interrupt
};

struct Event
{
    EventName name;
    char * eventData;
};


#endif // EVENT_H