#ifndef __WIDGET_H__
#define __WIDGET_H__

#include "gui/framebuff.h"

class widget
{
    public:
        widget(widget *parent);
        widget(widget *parent, int x, int y, int w, int h);
        ~widget();
        void addChild(widget *child);


        widget *parent;
        widget **children;
        int numChildren;
        int topleft[2];
        int size[2];
        virtual int click(int, int);
        virtual int draw(framebuff *fb);
};

#endif //__WIDGET_H__