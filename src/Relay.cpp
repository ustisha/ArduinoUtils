#include "../include/Relay.h"

Relay::Relay(uint8_t p, bool invt) : pin(p), invert(invt) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, invert ? HIGH : LOW);
    IF_SERIAL_DEBUG(printf_P(PSTR("[Relay::Relay] Pin: %i, Inversion: %d\n"), pin, (int) invert));
}

void Relay::on() {
    digitalWrite(pin, invert ? LOW : HIGH);
    IF_SERIAL_DEBUG(printf_P(PSTR("[Relay::on] Pin: %i\n"), pin));
}

void Relay::off() {
    digitalWrite(pin, invert ? HIGH : LOW);
    IF_SERIAL_DEBUG(printf_P(PSTR("[Relay::off] Pin: %i\n"), pin));
}

bool Relay::isOn() {
    return invert == !digitalRead(pin);
}