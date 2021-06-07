#ifndef EVENT_H
#define EVENT_H

#include <WString.h>

enum EventName {
    ReceivedTopClockRisingInterrupt,
    ReceivedTopClockFallingInterrupt,
    ReceivedTopDataRisingInterrupt,
    ReceivedTopDataFallingInterrupt,
    SendData,
    ErrorInterrupt
};

struct Event
{
    EventName name;
    char * eventData;
};


#endif // EVENT_H