#include "line.h"
#include "utils/logger.h"

line::line(widget *parent, int x1, int y1, int x2, int y2, uint16_t color) : widget(parent)
{
    int top;
    int left;
    int bottom;
    int right;
    int temp;
    //sort it left to right
    if(x1 > x2)
    {
        temp = x1;
        x1 = x2;
        x2 = temp;

        temp = y1;
        y1 = y2; 
        y2 = temp;

    }
    top = y1 > y2 ? y1 : y2;
    left = x1;
    bottom = y1 < y2 ? y1 : y2;
    right = x2;

    this->topleft[0] = left;
    this->topleft[1] = top;
    this->size[0] = right - left + 1;
    this->size[1] = top - bottom + 1;
    this->h = y2 - y1;
    this->color = color;
}

void line::move(int x1, int y1, int x2, int y2)
{
    int top;
    int left;
    int bottom;
    int right;
    int temp;
    //sort it left to right
    if(x1 > x2)
    {
        temp = x1;
        x1 = x2;
        x2 = temp;

        temp = y1;
        y1 = y2; 
        y2 = temp;

    }
    top = y1 < y2 ? y1 : y2;
    left = x1;
    bottom = y1 > y2 ? y1 : y2;
    right = x2;

    this->topleft[0] = left;
    this->topleft[1] = top;
    this->size[0] = right - left + 1;
    this->size[1] = bottom - top + 1;
    this->h = y2 - y1;
}

int line::draw(framebuff *fb)
{
    int i;
    int count = this->size[0] * this->size[1];
    int x = 0;
    int y = h > 0? 0 : this->size[1] * this->size[0];
    for(i=0;i<count;i++)
    {
        x+=1;
        y+=h>0?1:-1;
        int px = x / this->size[1];
        int py = y / this->size[0];
        fb->set_pixel(px, py, this->color);
    }
    return 0;
}