#ifdef IF_SERIAL_DEBUG
#undef IF_SERIAL_DEBUG
#endif

#ifdef SERIAL_DEBUG
#define IF_SERIAL_DEBUG(x) ({x;})
#else
#define IF_SERIAL_DEBUG(x)
#endif
