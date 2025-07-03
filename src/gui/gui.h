#ifndef __GUI_H__
#define __GUI_H__

#include "gui/util/screen.h"
#include "gui/framebuff.h"

class guiclass
{
    public:
        guiclass();
        void begin();
        void disable_display(void *);
        void click(void *);
        void add_screen(screen *);
        void push_screen(screen *);

    private:
        screen **screenstack;
        int screenstack_depth;
        screen **screens;
        int numscreens;
        framebuff *fb;
        int last_input = 0;
};

extern guiclass gui;

#endif //__GUI_H__