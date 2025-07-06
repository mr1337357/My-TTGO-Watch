#include "utils/logger.h"
#include "gui/util/button.h"
#include "button.h"

button::button(widget *parent, int x, int y, int w, int h, void(*callback)(void *)) : widget(parent,x,y,w,h)
{
    this->callback = callback;
}

int button::click(int x, int y)
{
    if(this->callback)
    {
        this->callback(0);
    }
}