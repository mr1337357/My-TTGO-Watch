#include "gui/util/screen.h"
#include "screen.h"

screen::screen(widget *parent, int w, int h) : widget(parent)
{
    this->topleft[0] = 0;
    this->topleft[1] = 0;
    this->size[0] = w;
    this->size[1] = h;
}