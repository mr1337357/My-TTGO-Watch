#ifndef __FRAMEBUFF_H__
#define __FRAMEBUFF_H__

#include <stdint.h>

class framebuff
{
    public:
        framebuff(int w, int h);
        framebuff(int w, int h, uint16_t *p);

        virtual ~framebuff();

        void virtual set_pixel(int x, int y, uint16_t c);
        void clear();
        uint16_t virtual get_pixel(int x, int y);

        uint16_t *pixels;
        int w;
        int h;
};

class crop : framebuff
{
    public:
        crop(framebuff *parent, int x, int y, int w, int h);
        framebuff *parent;
        void set_pixel(int x, int y, uint16_t c);
        int x;
        int y;
};

#endif //__FRAMEBUFF_H__