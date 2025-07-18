#include <FreeRTOS.h>

#include "config.h"
#include "delayed_call.h"
#include "utils/logger.h"
#include "gui/gui.h"

TTGOClass *watch;

uint32_t start_time;

SemaphoreHandle_t mtx;
RTC_Date now;

void draw_screen(void *arg);

void power_handler(void *arg)
{
    static uint32_t last_press = 0;
    static bool old_touch = false;
    bool new_touch = false;
    int16_t x;
    int16_t y;
    if(arg == 0)
    {
        bool isEvent = false;
        watch->power->readIRQ();
        if(watch->power->isPEKShortPressIRQ())
        {
            isEvent = true;
        }
        watch->power->clearIRQ();
        new_touch = watch->getTouch(x,y);
        if(new_touch & !old_touch)
        {
            gui.click(x,y);
            isEvent = true;
        }
        old_touch = new_touch;
        if(isEvent)
        {
            if(!watch->bl->isOn())
            {
                watch->openBL();
                watch->displayWakeup();
                watch->touchToMonitor();
                now = watch->rtc->getDateTime();
                start_time = FreeRTOS::getTimeSinceStart();
                delayed_call_add(draw_screen,0,1,false);
            }
            last_press = FreeRTOS::getTimeSinceStart();
            delayed_call_add(power_handler,(void *)&last_press,last_press+10001,false);
        }
        
    }
    else
    {
        if(last_press <=(FreeRTOS::getTimeSinceStart()-10000))
        {
            if(watch->bl->isOn())
            {
                watch->closeBL();
                watch->displaySleep();
                watch->touchToSleep();
            }
        }
    }
}

void add_second()
{
    now.second++;
    if(now.second >= 60)
    {
        now.second = 0;
        now.minute++;
        if(now.minute >= 60)
        {
            now.hour++;
            if(now.hour >= 24)
            {
                now.hour = 0;
            }
        }
    }
}

void draw_screen(void *arg)
{
    int i;
    int j;
    framebuff *fb;
    if(!watch->bl->isOn())
    {
        return;
    }
    gui.draw(0);
    fb = gui.get_fb();
    for(i=0;i<240;i++)
    {
        for(j=0;j<240;j++)
        {
            uint16_t pixel = fb->get_pixel(i,j);
            watch->tft->drawPixel(i,j,pixel);
        }
    }
    add_second();
    start_time += 1000;
    delayed_call_add(draw_screen,0,start_time + 1000,false);
}

void touchInterrupt()
{
    delayed_call_add(power_handler,0,1,true);
}

void buttonInterrupt()
{
    delayed_call_add(power_handler,0,1,true);
}

void setup()
{
    //delay(1000);
    Serial.begin(115200);
    Logger.begin(&Serial);
    Logger.printf("begin!\r\n");
    mtx = xSemaphoreCreateBinary();
    xSemaphoreGive(mtx);
    watch = TTGOClass::getWatch();
    watch->begin();
    watch->powerAttachInterrupt(buttonInterrupt);
    pinMode(TOUCH_INT, INPUT);
    attachInterrupt(TOUCH_INT, touchInterrupt, FALLING);
    watch->power->clearIRQ();
    watch->tft->setRotation(0);
    watch->tft->fillScreen(TFT_BLACK);
    watch->openBL();
    watch->bl->adjust(64);
    gui.begin(240,240);
    start_time = FreeRTOS::getTimeSinceStart();
    delayed_call_init();
    now = watch->rtc->getDateTime();
    power_handler(0);
    draw_screen(0);
}

int i = 0;

void loop()
{
    delayTask();
    //FreeRTOS::sleep(100);
}
