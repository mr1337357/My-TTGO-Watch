#include "utils/logger.h"
#include "gui/homescreen/homescreen.h"

#include <drive/rtc/pcf8563.h>
#include "homescreen.h"

extern RTC_Date now;


int8_t costable[] = 
{
    100, 86, 50, 0, -50, -86, -100, -86, -50, 0, 50, 86,
};

int8_t sintable[] = 
{
    0, 50, 86, 100, 86, 50, 0, -50, -86, -100, -86, -50,
};

homescreen::homescreen(int w, int h) : screen(0,w,h)
{
    int i;
    (void)new circle(this,0,0,240,240,COLOR(16, 16, 16));
    (void)new rect(this,118,1,4,10,COLOR(192,192,192)); //top
    for(i = 1; i < 12; i++)
    {
        (void)new rect(this,118 + sintable[i],118 - costable[i],4,4,COLOR(32,32,128));
    }
    //this->minute = (widget *)new rect(this, 0, 0, 4, 4, 0xFFFF);
    this->hour[0] = new line(this,100,100,120,110,COLOR(192,192,192));
    this->hour[1] = new line(this,100,100,120,110,COLOR(192,192,192));

    this->minute = new line(this,100,100,120,110,COLOR(255,255,255));

    (void)new circle(this,115,115,10,10,COLOR(128,128,128)); //center
}

int homescreen::draw(framebuff *fb)
{
    int16_t x;
    int16_t y;
    
    y = 120 - costable[now.minute/5] - 2;
    x = 120 + sintable[now.minute/5] - 2;
    this->minute->move(x,y,120,120);

    y = costable[now.hour%12];
    x = sintable[now.hour%12];
    y = (y*85)>>7; //cause C++ removed multiplying an int by .8
    x = (x*85)>>7;
    y = 120 - y;
    x += 120;
    this->hour[0]->move(x,y,120,120);
    this->hour[1]->move(x+1,y+1,121,121);
    widget::draw(fb);
    return 0;
}