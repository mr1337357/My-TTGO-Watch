#include "utils/logger.h"
#include <stdlib.h>
#include <esp32-hal-psram.h>
#include "gui/util/widget.h"
#include "widget.h"

widget::widget(widget *parent)
{
    this->parent = parent;
    if(parent)
    {
        parent->addChild(this);
    }
    this->topleft[0] = 0;
    this->topleft[0] = 0;
    this->size[0] = 0;
    this->size[1] = 0;
    this->children = 0;
    this->numChildren = 0;
}

widget::widget(widget *parent, int x, int y, int w, int h)
{
    this->parent = parent;
    if(parent)
    {
        parent->addChild(this);
    }
    this->topleft[0] = x;
    this->topleft[1] = y;
    this->size[0] = w;
    this->size[1] = h;
    this->children = 0;
    this->numChildren = 0;
}

widget::~widget()
{
}

void widget::addChild(widget *child)
{
    int i;
    widget **newptr;
    newptr = (widget **)ps_malloc(sizeof(widget *) * (this->numChildren+1));
    if(newptr)
    {
        for(i=0;i<this->numChildren;i++)
        {
            newptr[i] = this->children[i];
        }
        if(this->children != 0)
        {
            free(this->children);
        }
        this->children = newptr;
        this->children[numChildren++] = child;
    }
}

int widget::click(int x, int y)
{
    int i;
    for(i=0;i<this->numChildren;i++)
    {
        widget *child = this->children[i];
        int lx = x - child->topleft[0];
        int ly = y - child->topleft[1];
        if(lx >= 0 && lx <= child->size[0])
        {
            if(ly >= 0 && ly <= child->size[1])
            {
                child->click(lx,ly);
            }
        }
    }
    return 0;
}
int widget::draw(framebuff *fb)
{
    int i;
    for(i=0;i<this->numChildren;i++)
    {
        widget *child = this->children[i];
        crop *c = new crop(fb,child->topleft[0],child->topleft[1],child->size[0],child->size[1]);
        child->draw((framebuff *)c);
        delete c;
    }
    return 0;
}