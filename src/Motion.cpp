#include "../include/Motion.h"

void Motion::tick() {
    if (millis() < detectDelay) {
        return;
    }
    Switch::tick();
    if (currentState != isPressed()) {
        currentState = isPressed();
        sendCommand(CMD_MOTION);
    }
}
