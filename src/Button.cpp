#include "Arduino.h"
#include "../include/Button.h"

Button::Button(uint8_t btnPin, uint8_t max, bool invt) : arr(new Callback[max]{}),
                                                         maxArr(max),
                                                         i(0),
                                                         pin(btnPin),
                                                         start(0),
                                                         invert(invt)
#ifdef VIBRO_ENABLED
                                                         ,
                                                         vbr(nullptr),
                                                         vibrated(new uint8_t[max]{0})
#endif
{
    pinMode(pin, invert ? INPUT_PULLUP : INPUT);
    IF_SERIAL_DEBUG(printf_P(PSTR("[Button] Pin: %i, Inversion: %d, Max: %i\n"), pin, (int) invert, maxArr));
}

auto Button::sortByPress(const void *elem1, const void *elem2) -> int {
    return ((Callback *) elem1)->press < ((Callback *) elem2)->press ? 1 : -1;
}

auto Button::addHandler(HandlerInterface *handlerInterface, uint8_t t, uint16_t pressTime, uint8_t idx) -> int8_t {
    if (i >= maxArr) {
        IF_SERIAL_DEBUG(PSTR("[Button::addHandler] limit reached\n"));
        return -1;
    }
    arr[i].handlerInterface = handlerInterface;
    arr[i].type = t;
    arr[i].press = pressTime;
    arr[i].idx = idx;
    qsort(arr, maxArr, sizeof(Callback), Button::sortByPress);
    IF_SERIAL_DEBUG(printf_P(PSTR("[Button::addHandler] Idx: %i\n"), i));
    return i++;
}

#ifdef VIBRO_ENABLED
bool Button::isVibrated(uint8_t callbackType)
{
    for (uint8_t i = 0; i < maxArr; i++) {
        if (vibrated[i] == callbackType) {
            return true;
        }
    }
    return false;
}
#endif

#ifdef VIBRO_ENABLED
void Button::markVibrated(uint8_t callbackType)
{
    for (uint8_t i = 0; i < maxArr; i++) {
        if (!vibrated[i]) {
            vibrated[i] = callbackType;
            IF_SERIAL_DEBUG(printf_P(PSTR("[Button::markVibrated] Marked in: %i, Type: %i\n"), i, callbackType));
            return;
        }
    }
}
#endif

void Button::tick() {
    unsigned long m = millis();
#ifdef VIBRO_ENABLED
    if (vbr != nullptr) {
        vbr->tick();
    }
#endif
    if (start != 0 && start > m) {
        start = m;
    }
    if (isPressed() && start == 0) {
        IF_SERIAL_DEBUG(printf_P(PSTR("[Button::tick] Pressed\n")));
        start = m;
        return;
    }
#ifdef VIBRO_ENABLED
    if (vbr != nullptr && isPressed() && start != 0) {
        for (uint8_t i = 0; i < maxArr; i++) {
            if (arr[i].handlerInterface != nullptr && (m - start) >= arr[i].press) {
                if (!isVibrated(arr[i].type)) {
                    markVibrated(arr[i].type);
                    uint8_t cnt;
                    switch (arr[i].press) {
                        case PRESSTIME_1SEC:
                            cnt = 2;
                            break;
                        case PRESSTIME_2SEC:
                            cnt = 3;
                            break;
                        case PRESSTIME_4SEC:
                            cnt = 4;
                            break;
                        default:
                            cnt = 1;
                    }
                    IF_SERIAL_DEBUG(printf_P(PSTR("[Button::tick] Vibro called, count: %i\n"), cnt));
                    vbr->vibrate(cnt);
                }
                break;
            }
        }
    }
#endif
    if (!isPressed() && start != 0) {
        IF_SERIAL_DEBUG(printf_P(PSTR("[Button::tick] Released\n")));
#ifdef VIBRO_ENABLED
        if (vbr != nullptr) {
            vbr->reset();
            memset(vibrated, 0, maxArr);
        }
#endif
        for (uint8_t i = 0; i < maxArr; i++) {
            if (arr[i].handlerInterface != nullptr && (m - start) >= arr[i].press) {
                arr[i].handlerInterface->call(arr[i].type, arr[i].idx);
                IF_SERIAL_DEBUG(printf_P(PSTR("[Button::tick] Handler called: %i\n"), i));
                break;
            }
        }
        start = 0;
    }
}
