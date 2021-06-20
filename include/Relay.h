#ifndef RELAY_H
#define RELAY_H

//#define SERIAL_DEBUG

#include <Arduino.h>
#include <DebugLog.h>
#include <RelayInterface.h>

class Relay : public RelayInterface
{
public:
    Relay(uint8_t p, bool invt = true);

    virtual void on() override;

    virtual void off() override;

    virtual bool isOn() override;

protected:
    uint8_t pin{};
    bool invert{};
};

#endif //RELAY_H
