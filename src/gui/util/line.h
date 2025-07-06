#ifndef __LINE_H__
#define __LINE_H__
#include <gui/util/widget.h>

class line : widget
{
    public:
        line(widget *parent, int x1, int y1, int x2, int y2, uint16_t color);
        void move(int x1, int y1, int x2, int y2);
        int draw(framebuff *fb);
        uint16_t color;
        int h;
};
#endif //__line_H__