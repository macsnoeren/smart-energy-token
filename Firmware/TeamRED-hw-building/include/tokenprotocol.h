#ifndef TOKENPROTOCOL_H
#define TOKENPROTOCOL_H

#include <RF24.h>

#define topDataPin PB2;
#define topClockPin PA7;
#define bottomDataPin PA4;
#define bottomClockPin PA5;
#define tokenProtocolDelay 5

class tokenprotocol
{
public:
    static tokenprotocol *instance()
    {
        if (_instance == 0)
        {
            _instance = new tokenprotocol();
        }

        return _instance;
    }

protected:
    tokenprotocol();

private:
    static tokenprotocol *_instance;
private:
    volatile bool hasClockLineRised;
    bool hasReceivedSomething;

    uint8_t topClockBitNumber;
    char toWrite;
    String text;

    bool isBuilding;
    RF24 *radio;

    void end();
public:
    tokenprotocol(tokenprotocol const &) = delete;
    void operator=(tokenprotocol const &) = delete;

    ~tokenprotocol();
    void send(const char *text);
    void init();
    void setup(RF24 *_radio, bool _isBuilding);

    void receivedTopDataFalling();
    void receivedTopClockFalling();

    void receivedTopClockRising();
    void receivedTopDataRising();
};

#endif