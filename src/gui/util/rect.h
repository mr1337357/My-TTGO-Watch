#ifndef __RECT_H__
#define __RECT_H__
#include <gui/util/widget.h>

class rect : widget
{
    public:
        rect(widget *parent, int x, int y, int w, int h, uint16_t color);
        int draw(framebuff *fb);
        uint16_t color;
};
#endif //__RECT_H__