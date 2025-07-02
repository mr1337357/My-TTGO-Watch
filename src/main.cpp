#include <FreeRTOS.h>

#include "config.h"
#include "delayed_call.h"

TTGOClass *watch;

uint32_t start_time;

SemaphoreHandle_t mtx;
RTC_Date now;

void print_time(void *arg)
{
    now = watch->rtc->getDateTime();
    watch->tft->setCursor(80,110);
    watch->tft->printf("%02d:%02d:%02d\n",now.hour,now.minute,now.second);
    delayed_call_add(print_time,0,start_time+=1000,false);
}

void setup()
{
    mtx = xSemaphoreCreateBinary();
    xSemaphoreGive(mtx);
    watch = TTGOClass::getWatch();
    watch->begin();
    watch->tft->fillScreen(TFT_BLACK);
    watch->bl->adjust(64);
    start_time = FreeRTOS::getTimeSinceStart();
    now = watch->rtc->getDateTime();
    delayed_call_init();
    delayed_call_add(print_time,0,start_time + 1000,false);
}

int i = 0;

void loop()
{
    delayTask();
    //FreeRTOS::sleep(100);
}
