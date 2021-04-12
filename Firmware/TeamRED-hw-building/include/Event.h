#ifndef EVENT_H
#define EVENT_H

#include <WString.h>

enum EventName {
    ReceivedTopClockRisingInterrupt,
    ReceivedTopClockFallingInterrupt,
    ReceivedTopDataRisingInterrupt,
    ReceivedTopDataFallingInterrupt,
};

struct Event
{
    EventName name;
    String __eventData;
};


#endif // EVENT_H