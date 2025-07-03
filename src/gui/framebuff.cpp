#include <stdlib.h>

#include "gui/framebuff.h"
#include "framebuff.h"

framebuff::framebuff(int w, int h)
{
    this->w = w;
    this->h = h;
    this->pixels = (uint16_t *)malloc(w * h * sizeof(uint16_t));
}

void framebuff::set_pixel(int x, int y, uint16_t c)
{
    if(x < 0 || x > this->w)
    {
        return;
    }
    if(y < 0 || y > this->h)
    {
        return;
    }
    this->pixels[y * w + x] = c;
}
