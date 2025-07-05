#include "utils/logger.h"
#include "gui.h"
#include "gui/homescreen/homescreen.h"

guiclass::guiclass()
{
    this->active = 0;
    this->screenstack = 0;
    this->screenstack_depth = 0;
}

void guiclass::begin(int w, int h)
{
    this->fb = new framebuff(w,h);
    this->active = new homescreen(w,h);
}

void guiclass::draw(void *arg)
{
    (void)arg;
    this->fb->clear();
    this->active->draw(this->fb);
}

framebuff *guiclass::get_fb()
{
    return this->fb;
}

guiclass gui;
