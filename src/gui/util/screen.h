#ifndef __SCREEN_H__
#define __SCREEN_H__

#include "widget.h"

class screen : public widget
{
    public:
        screen(widget *parent,int w, int h);

    private:
        widget **widgets;
        int numwidgets;
};

#endif