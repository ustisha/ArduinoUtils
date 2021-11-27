#include "../include/Motion.h"

void Motion::tick() {
    if (millis() < detectDelay) {
        return;
    }
    Switch::tick();
    if (currentState != isPressed()) {
        currentState = isPressed();
#ifdef NETINTERFACE_H
        sendCommand(CMD_MOTION);
#endif
    }
}
