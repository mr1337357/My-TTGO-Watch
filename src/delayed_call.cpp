#include "delayed_call.h"
#include <FreeRTOS.h>
#include <esp32-hal-psram.h>
#include "utils/minheap.h"
#include "utils/logger.h"

static minheap mh;

static SemaphoreHandle_t delay_sem;

typedef struct
{
    void (*cb)(void *);
    void *arg;
} delayed_call;

void delayTask(void *arg);

void delayed_call_init()
{
    minheap_init(&mh,128);
    delay_sem = xSemaphoreCreateBinary();
}

void delayed_call_add(void (*fxn)(void *), void *arg, int calltime, bool isIsr)
{
    BaseType_t taskWoken;
    delayed_call *call = (delayed_call *)ps_malloc(sizeof(delayed_call));
    call->cb = fxn;
    call->arg = arg;
    if(calltime == 0)
    {
        calltime = 1;
    }
    minheap_push(&mh, calltime, (void *)call);
    if(isIsr)
    {
        xSemaphoreGiveFromISR(delay_sem,&taskWoken);
    }
    else
    {
        xSemaphoreGive(delay_sem);
    }
}

void delayTask()
{
    delayed_call *call;
    uint64_t now;
    uint64_t prio;

    now = FreeRTOS::getTimeSinceStart();
    prio = minheap_peek_prio(&mh);
    if(prio != 0 && prio <= now)
    {
        call = (delayed_call *)minheap_pop(&mh);
        if(call)
        {
            call->cb(call->arg);
            free((void *)call);
        }
    }
    if(prio == 0)
    {
        xSemaphoreTake(delay_sem,1000 * portTICK_PERIOD_MS);
        return;
    }
    if(prio<now)
    {
        return;
    }
    uint64_t wait_time = prio - now;
    //delay_debug();
    xSemaphoreTake(delay_sem,(wait_time)*portTICK_PERIOD_MS);
}

void delay_debug()
{
    int i;
    for(i=0;i<minheap_count(&mh);i++)
    {
        int prio;
        delayed_call *dc;
        prio = minheap_debug_Read(&mh,i,(void **)&dc);
        Logger.printf("%d %d %p, ", i, prio, dc);
    }
    Logger.printf("\r\n");
}