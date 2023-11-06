#ifndef PIR_H
#define PIR_H

//#define SERIAL_DEBUG

#include <Arduino.h>
#include <DebugLog.h>
#include <Button.h>

class Motion : public Button {

public:
    explicit Motion(uint8_t btnPin, uint8_t max = 1, bool invt = true) :
            Button(btnPin, max, invt) {
        currentState = isPressed();
    }

    void tick() override;

    virtual void setState(bool state)
    {
        currentState = state;
    }

protected:
    bool currentState;
};


#endif //PIR_H
