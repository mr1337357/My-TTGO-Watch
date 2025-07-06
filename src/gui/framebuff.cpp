#include <stdlib.h>
#include <string.h>

#include "utils/logger.h"
#include "gui/framebuff.h"
#include "framebuff.h"

framebuff::framebuff(int w, int h)
{
    this->w = w;
    this->h = h;
    this->pixels = (uint16_t *)malloc(w * h * sizeof(uint16_t));
}

framebuff::framebuff(int w, int h, uint16_t *p)
{
    this->w = w;
    this->h = h;
    this->pixels = p;
}

framebuff::~framebuff()
{
    
}

void framebuff::set_pixel(int x, int y, uint16_t c)
{
    if(x < 0 || x >= this->w)
    {
        return;
    }
    if(y < 0 || y >= this->h)
    {
        return;
    }
    this->pixels[y * w + x] = c;
}

void framebuff::clear()
{
    memset(this->pixels,0,sizeof(uint16_t)*w*h);
}

uint16_t framebuff::get_pixel(int x, int y)
{
    if(x < 0 || x >= this->w)
    {
        return 0;
    }
    if(y < 0 || y >= this->h)
    {
        return 0;
    }
    return this->pixels[y * w + x];
}

crop::crop(framebuff *parent, int x, int y, int w, int h) : framebuff(w, h, parent->pixels)
{
    this->parent = parent;
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

void crop::set_pixel(int x, int y, uint16_t c)
{
    if(x < 0 || x >= w)
    {
        return;
    }
    if(y < 0 || y >= h)
    {
        return;
    }
    x+=this->x;
    y+=this->y;
    parent->set_pixel(x,y,c);
}
