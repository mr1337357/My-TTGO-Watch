#ifndef __DELAYED_CALL_H__
#define __DELAYED_CALL_H__

void delayed_call_init();
void delayed_call_add(void (*fxn)(void *), void *arg, int calltime, bool isIsr);
void delayTask();
void delay_debug();

#endif