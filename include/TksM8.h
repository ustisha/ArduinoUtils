#ifndef TKSM8_H
#define TKSM8_H

//#define SERIAL_DEBUG

#include <Arduino.h>
#include <DebugLog.h>
#include <Relay.h>
#include <RelayInterface.h>

class TksM8 : public RelayInterface
{
public:
    TksM8(uint8_t pinK1, uint8_t pinK2, uint8_t pinSw1, uint8_t pinSw2, uint8_t timeout);

    void on() override;

    void off() override;

    bool isOn() override;

    void tick();

protected:
    Relay *k1, *k2, *sw1, *sw2;
    bool isOpened = false;
    unsigned long swTimeout, offSw1Time, offSw2Time;

};

#endif //TKSM8_H
