#include "utils/logger.h"
#include "gui/homescreen/homescreen.h"

#include "gui/util/widget.h"
#include "gui/util/rect.h"
#include <drive/rtc/pcf8563.h>
#include "homescreen.h"

extern RTC_Date now;

int8_t costable[] = 
{
    100, 86, 50, 0, -50, -86, -100, -86, -50, 0, 50, 86, 100, 86, 50, 0
};

homescreen::homescreen(int w, int h) : screen(0,w,h)
{
    Logger.printf(__FILE__"(%d)\r\n",__LINE__);
    this->minute = (widget *)new rect(this, 0, 0, 4, 4, 0xFFFF);
    Logger.printf(__FILE__"(%d)\r\n",__LINE__);
    this->hour = (widget *)new rect(this, 0, 0, 6, 6, 0xFFFF);
    Logger.printf(__FILE__"(%d)\r\n",__LINE__);
    (void)new rect(this,115,115,10,10,0xF800);
    Logger.printf(__FILE__"(%d)\r\n",__LINE__);
}

int homescreen::draw(framebuff *fb)
{
    int16_t x;
    int16_t y;
    y = 120 - costable[now.minute/5];
    x = 120 + costable[now.minute/5 + 3];
    this->minute->topleft[0] = x;
    this->minute->topleft[1] = y;
    y = costable[now.hour%12];
    x = costable[(now.hour%12) + 3];
    y = (y*104)>>7; //cause C++ removed multiplying an int by .8
    x = (x*104)>>7;
    y += 120;
    x += 120;
    this->hour->topleft[0] = x;
    this->hour->topleft[1] = y;
    //this->children[0]->topleft[0] = now.minute * 5;
    widget::draw(fb);
    return 0;
}