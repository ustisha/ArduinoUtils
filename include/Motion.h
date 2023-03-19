#ifndef PIR_H
#define PIR_H

//#define SERIAL_DEBUG

#include <Arduino.h>
#include <DebugLog.h>
#include <Button.h>

class Motion : public Button {

public:
    explicit Motion(uint8_t btnPin, uint16_t detectDelay = 30, uint8_t max = 1, bool invt = true) :
            Button(btnPin, max, invt),
            detectDelay(detectDelay * 1000) {
        currentState = isPressed();
    }

    void tick() override;

    virtual void setState(bool state)
    {
        currentState = state;
    }

protected:
    uint16_t detectDelay;
    bool currentState;
};


#endif //PIR_H
