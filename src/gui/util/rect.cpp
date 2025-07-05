#include "utils/logger.h"
#include "rect.h"

rect::rect(widget *parent, int x, int y, int w, int h, uint16_t color) : widget(parent,x,y,w,h)
{
    this->color = color;
}

int rect::draw(framebuff *fb)
{
    int x;
    int y;
    for(x=0;x<this->size[0];x++)
    {
        for(y=0;y<this->size[1];y++)
        {
            fb->set_pixel(x,y,this->color);
        }
    }
    return 0;
}
