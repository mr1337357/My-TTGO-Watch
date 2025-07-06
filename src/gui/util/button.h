#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "widget.h"

class button : public widget
{
    public:
        button(widget *parent, int x, int y, int w, int h, void (*callback)(void *));
        int click(int x, int y);
    private:
        void (*callback)(void *);
};

#endif