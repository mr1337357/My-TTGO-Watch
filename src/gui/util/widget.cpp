#include <stdlib.h>
#include "gui/util/widget.h"

widget::widget(widget *parent)
{
    this->parent = parent;
    if(parent)
    {
        parent->addChild(this);
    }
    this->children = 0;
    this->numChildren = 0;
}

void widget::addChild(widget *child)
{
    this->numChildren++;
    this->children = (widget **)realloc(this->children,this->numChildren);
    this->children[numChildren-1] = child;
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