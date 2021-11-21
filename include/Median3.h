#ifndef MEDIAN3_H
#define MEDIAN3_H

//#define SERIAL_DEBUG

template<typename TYPE>
class Median3
{
public:
    TYPE filtered(TYPE value)
    {
        buf[counter] = value;
        if (++counter > 2) {
            counter = 0;
            ready = true;
        }
        if (!ready) {
            IF_SERIAL_DEBUG(printf_P(PSTR("[Median3::filtered] Not ready use raw\n")));
            return value;
        }
        IF_SERIAL_DEBUG(printf_P(PSTR("[Median3::filtered] Ready use filtered\n")));
        return (max(buf[0], buf[1]) == max(buf[1], buf[2]))
               ? max(buf[0], buf[2])
               : max(buf[1], min(buf[0], buf[2]));
    }

private:
    TYPE buf[3] = {0, 0, 0};
    uint8_t counter = 0;
    bool ready = false;
};

#endif //MEDIAN3_H
