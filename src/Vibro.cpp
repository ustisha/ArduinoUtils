#include "Vibro.h"
#include "DebugLog.h"

void Vibro::tick()
{
    unsigned long m = millis();
    if (vibroCount) {
        if (vibroStart == 0 && spaceStart == 0) {
            vibroCount--;
            vibroStart = m;
            digitalWrite(vibroPin, HIGH);
            IF_SERIAL_DEBUG(printf_P(PSTR("[Vibro::tick] Vibrate start\n")));
        }
        if (spaceStart != 0 && m > (spaceStart + VIBRO_SPACE)) {
            spaceStart = 0;
        }
    }
    if (vibroStart != 0 && m > (vibroStart + VIBRO_WIDTH)) {
        reset();
        spaceStart = m;
    }
}

void Vibro::reset()
{
    spaceStart = 0;
    vibroStart = 0;
    digitalWrite(vibroPin, LOW);
    IF_SERIAL_DEBUG(printf_P(PSTR("[Vibro::reset] Vibrate end\n")));
}
