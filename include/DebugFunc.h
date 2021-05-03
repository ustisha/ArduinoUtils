#ifdef SERIAL_DEBUG

#ifndef SERIAL_DEBUG_F
#define SERIAL_DEBUG_F

int serial_putc(char c, FILE *)
{
    Serial.write(c);
    Serial.flush();
    return c;
}

void printf_begin(void)
{
#if defined(ARDUINO_ARCH_AVR)
    fdevopen(&serial_putc, 0);

#elif defined(__ARDUINO_X86__)
    // JESUS - For reddirect stdout to /dev/ttyGS0 (Serial Monitor port)
    stdout = freopen("/dev/ttyGS0", "w", stdout);
    delay(500);
    printf("Redirecting to Serial...");
#endif // defined(__ARDUINO_X86__)
}

#endif

#ifndef DEBUG_FREE_RAM
#define DEBUG_FREE_RAM

uint32_t freeRAM()
{
#if defined(ESP8266) || defined(ESP32)
    return system_get_free_heap_size();
#elif  defined (ARDUINO) && !defined (ESP_PLATFORM)
    extern int __heap_start, *__brkval;
    int v;
    return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
#endif
}

#endif

#endif
