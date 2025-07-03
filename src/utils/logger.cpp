#include <stdlib.h>
#include "utils/logger.h"

logger::logger(int size)
{
    this->s = 0;
    this->buffsz = size;
    buffer = (char *)malloc(buffsz * sizeof(char));
}

void logger::begin(HardwareSerial *dev)
{
    this->s = dev;
}

int logger::logf(char *file, int line, char *fmt, ...)
{
    va_list args;
    int offset = 0;
    va_start(args, fmt);
    offset = sprintf(this->buffer, "%s(%d): ",file,line) - 1;
    offset = vsprintf(this->buffer + offset, fmt, args) - 1;
    this->buffer[offset++] = '\r';
    this->buffer[offset++] = 0;

    if (this->s)
    {
        this->s->write(this->buffer, offset);
    }
    return offset;
}

int logger::printf(char *fmt, ...)
{
    va_list args;
    int offset=0;
    va_start(args, fmt);
    offset = vsprintf(this->buffer, fmt, args);
    if(this->s)
    {
        this->s->write(this->buffer, offset);
    }
    return offset;
}

logger Logger(1024);