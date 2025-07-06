#include "utils/logger.h"
#include "circle.h"

circle::circle(widget *parent, int x, int y, int w, int h, uint16_t color) : widget(parent,x,y,w,h)
{
    this->color = color;
}

int circle::draw(framebuff *fb)
{
    int x;
    int y;

    for(x=0;x<this->size[0];x++)
    {
        for(y=0;y<this->size[1];y++)
        {
            int i = x - this->size[0]/2;
            int j = y - this->size[1]/2;
            if((i * i + j * j) <= this->size[0] * this->size[0] / 4)
            {
                fb->set_pixel(x,y,this->color);
            }
        }
    }
    return 0;
}
