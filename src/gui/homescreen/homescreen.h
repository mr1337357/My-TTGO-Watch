#ifndef __HOMESCREEN_H__
#define __HOMESCREEN_H__

#include "gui/util/screen.h"
class homescreen : public screen
{
    public:
        homescreen(int w, int h);
        virtual int draw(framebuff *fb);
    private:
        widget *minute;
        widget *hour;
};

#endif //__HOMESCREEN_H__