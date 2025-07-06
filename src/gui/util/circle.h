#ifndef __CIRCLE_H__
#define __CIRCLE_H__
#include <gui/util/widget.h>

class circle : widget
{
    public:
        circle(widget *parent, int x, int y, int w, int h, uint16_t color);
        int draw(framebuff *fb);
        uint16_t color;
};
#endif //__CIRCLE_H__