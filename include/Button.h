#ifndef BUTTON_H
#define BUTTON_H

//#define SERIAL_DEBUG
#include <Arduino.h>
#include <DebugLog.h>
#include <Config.h>
#include <Vibro.h>
#include <HandlerInterface.h>
#ifndef RADIO_ENABLED
#include <NetInterface.h>
#endif

#ifndef RADIO_ENABLED
class Button : public NetInterface {
#else
class Button {
#endif
protected:

    struct Callback {
        HandlerInterface *handlerInterface = nullptr;
        uint8_t type = 0;
        uint16_t press = 0;
        uint8_t idx = 0;
    };

    Callback *arr;
    uint8_t maxArr;
    uint8_t i;
    uint8_t pin;
    unsigned long start;
    bool invert;
#ifdef VIBRO_ENABLED
    Vibro *vbr;
    uint8_t *vibrated;
#endif

    static auto sortByPress(const void *elem1, const void *elem2) -> int;

public:
    static const uint16_t PRESSTIME_DEFAULT = 50;
    static const uint16_t PRESSTIME_1SEC = 1000;
    static const uint16_t PRESSTIME_2SEC = 2000;
    static const uint16_t PRESSTIME_4SEC = 4000;

    explicit Button(uint8_t btnPin, uint8_t max = 1, bool invt = true);

    auto isPressed() -> bool
    {
        return (!invert && digitalRead(pin) == LOW) || (invert && digitalRead(pin) == HIGH);
    }

    auto addHandler(HandlerInterface *handlerInterface, uint8_t t = 0, uint16_t pressTime = PRESSTIME_DEFAULT, uint8_t i = 0) -> int8_t;

#ifdef VIBRO_ENABLED
    bool isVibrated(uint8_t callbackType);

    void markVibrated(uint8_t callbackType);

    void addVibro(Vibro *vibro)
    {
        vbr = vibro;
    }
#endif
    virtual void tick();
};


#endif //BUTTON_H
