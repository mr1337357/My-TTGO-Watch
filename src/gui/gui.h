#ifndef __GUI_H__
#define __GUI_H__

#include "gui/util/screen.h"
#include "gui/framebuff.h"

class guiclass
{
    public:
        guiclass();
        void begin(int w, int h);
        void disable_display(void *);
        void click(uint16_t x, uint16_t y);
        void draw(void *);
        void push_screen(screen *);
        void pop_screen();
        framebuff *get_fb();

    private:
        screen **screenstack;
        int screenstack_depth;
        screen *active;
        framebuff *fb;
        int last_input = 0;
};

extern guiclass gui;

#endif //__GUI_H__