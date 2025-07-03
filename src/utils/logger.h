#include "HardwareSerial.h"

#define LOG(...) Logger.logf(__FILE__,__LINE__, __VA_ARGS__ )

class logger
{
    public:
        logger(int size);
        void begin(HardwareSerial *dev);
        int logf(char *file, int line, char *fmt, ...);
        int printf(char *fmt, ...);

    private:
        HardwareSerial *s;
        char *buffer;
        int buffsz;
};

extern logger Logger;