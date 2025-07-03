#include <FreeRTOS.h>

#include "config.h"
#include "delayed_call.h"
#include "utils/logger.h"

TTGOClass *watch;

uint32_t start_time;

SemaphoreHandle_t mtx;
RTC_Date now;

void power_handler(void *arg)
{
    static uint32_t last_press = 0;
    if(arg == 0)
    {
        if(!watch->bl->isOn())
        {
            watch->openBL();
        }
        last_press = FreeRTOS::getTimeSinceStart();
        watch->power->clearIRQ();
        delayed_call_add(power_handler,(void *)&last_press,last_press+15000,false);
    }
    else
    {
        if(last_press <=(FreeRTOS::getTimeSinceStart()-15000))
        {
            if(watch->bl->isOn())
            {
                watch->closeBL();
            }
        }
    }
}

void buttonInterrupt()
{
    delayed_call_add(power_handler,0,1,true);
}

void print_time(void *arg)
{
    now = watch->rtc->getDateTime();
    watch->tft->setCursor(80,110);
    watch->tft->printf("%02d:%02d:%02d\n",now.hour,now.minute,now.second);
    Logger.printf("%02d:%02d:%02d\r\n",now.hour,now.minute,now.second);
    delayed_call_add(print_time,0,start_time+=1000,false);
}

void setup()
{
    delay(1000);
    Serial.begin(115200);
    Logger.begin(&Serial);
    Logger.printf("begin!\r\n");
    mtx = xSemaphoreCreateBinary();
    xSemaphoreGive(mtx);
    watch = TTGOClass::getWatch();
    watch->begin();
    watch->powerAttachInterrupt(buttonInterrupt);
    watch->power->clearIRQ();
    watch->tft->setRotation(0);
    watch->tft->fillScreen(TFT_BLACK);
    watch->openBL();
    watch->bl->adjust(64);
    start_time = FreeRTOS::getTimeSinceStart();
    now = watch->rtc->getDateTime();
    Logger.printf("delayed_call_init\r\n");
    delayed_call_init();
    delayed_call_add(print_time,0,start_time + 1000,false);
    power_handler(0);
}

int i = 0;

void loop()
{
    delayTask();
    //FreeRTOS::sleep(100);
}
