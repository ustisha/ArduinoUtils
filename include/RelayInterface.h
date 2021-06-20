#ifndef RELAYINTERFACE_H
#define RELAYINTERFACE_H

//#define SERIAL_DEBUG

#include <Arduino.h>
#include <DebugLog.h>

class RelayInterface
{
public:

    virtual void on() = 0;

    virtual void off() = 0;

    void change()
    {
        bool s = isOn();
        s ? off() : on();
        IF_SERIAL_DEBUG(printf_P(PSTR("[Relay::change] From: %d, To: %d\n"), (int) s, (int) isOn()));
    }

    virtual bool isOn() = 0;
};

#endif //RELAYINTERFACE_H
