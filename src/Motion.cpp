#include "../include/Motion.h"

void Motion::tick()
{
    unsigned long m = millis();
    if (isPressed()) {
        if (start == 0) {
            start = m;
            IF_SERIAL_DEBUG(printf_P(PSTR("[Motion::tick] Start\n")));
            return;
        }
        for (uint8_t h = 0; h < maxArr; h++) {
            if (arr[h].handlerInterface != nullptr && (m - start) >= arr[h].press && !currentState) {
                arr[h].handlerInterface->call(arr[h].type, arr[h].idx);
                setState(isPressed());
                IF_SERIAL_DEBUG(printf_P(PSTR("[Motion::tick] Handler called: %i\n"), h));
                break;
            }
        }
    }
    if (!isPressed() && start != 0) {
        IF_SERIAL_DEBUG(printf_P(PSTR("[Motion::tick] Released\n")));
        setState(isPressed());
        start = 0;
    }
}
