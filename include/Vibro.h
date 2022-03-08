#ifndef VIBRO_H
#define VIBRO_H

//#define SERIAL_DEBUG

#include "Arduino.h"

class Vibro
{
protected:

    const uint8_t VIBRO_WIDTH = 80;
    const uint8_t VIBRO_SPACE = 180;

    uint8_t vibroPin;
    uint8_t vibroCount = 0;
    unsigned long vibroStart = 0;
    unsigned long spaceStart = 0;

public:

    explicit Vibro(uint8_t pin) : vibroPin(pin)
    {
        pinMode(vibroPin, OUTPUT);
        digitalWrite(vibroPin, LOW);
    }

    void reset();

    void vibrate(uint8_t count)
    {
        vibroCount = count;
    }

    virtual void tick();
};

#endif //VIBRO_H
