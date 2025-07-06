#ifndef __HOMESCREEN_H__
#define __HOMESCREEN_H__

#include "gui/util/screen.h"
#include "gui/util/widget.h"
#include "gui/util/rect.h"
#include "gui/util/circle.h"
#include "gui/util/line.h"

class homescreen : public screen
{
    public:
        homescreen(int w, int h);
        virtual int draw(framebuff *fb);
    private:
        line *minute;
        line *hour[2];
};

#endif //__HOMESCREEN_H__