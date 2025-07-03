#ifndef __FRAMEBUFF_H__
#define __FRAMEBUFF_H__

#include <stdint.h>
class framebuff
{
    public:
        framebuff(int w, int h);

        void set_pixel(int x, int y, uint16_t c);

    private:
        uint16_t *pixels;
        int w;
        int h;
};

#endif //__FRAMEBUFF_H__