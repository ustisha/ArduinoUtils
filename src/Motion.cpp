#include "../include/Motion.h"

void Motion::tick() {
    if (millis() < detectDelay) {
        return;
    }
    Switch::tick();
    if (currentState != isPressed()) {
        setState(isPressed());
    }
}
