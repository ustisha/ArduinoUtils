#include "../include/TksM8.h"

TksM8::TksM8(uint8_t pinK1, uint8_t pinK2, uint8_t pinSw1, uint8_t pinSw2, uint8_t timeout)
{
    k1 = new Relay(pinK1);
    k2 = new Relay(pinK2);
    sw1 = new Relay(pinSw1);
    sw2 = new Relay(pinSw2);
    isOpened = false;
    swTimeout = timeout * 1000;
    offSw1Time = offSw2Time = 0;
}

void TksM8::on()
{
    IF_SERIAL_DEBUG(printf_P(PSTR("[TksM8::on] SW1 off, K1 on\n")));
    sw2->off();
    k2->off();

    sw1->off();
    k1->on();
    offSw1Time = millis() + swTimeout;
    isOpened = true;
}

void TksM8::off()
{
    IF_SERIAL_DEBUG(printf_P(PSTR("[TksM8::on] SW2 off, K2 on\n")));
    sw1->off();
    k1->off();

    sw2->off();
    k2->on();
    offSw2Time = millis() + swTimeout;
    isOpened = false;
}

bool TksM8::isOn()
{
    return isOpened;
}

void TksM8::tick()
{
    unsigned long m = millis();
    if (offSw1Time != 0 && m > offSw1Time) {
        IF_SERIAL_DEBUG(printf_P(PSTR("[TksM8::tick] SW1 off by timeout\n")));
        sw1->on();
        offSw1Time = 0;
    }
    if (offSw2Time != 0 && m > offSw2Time) {
        IF_SERIAL_DEBUG(printf_P(PSTR("[TksM8::tick] SW2 off by timeout\n")));
        sw2->on();
        offSw2Time = 0;
    }
}
