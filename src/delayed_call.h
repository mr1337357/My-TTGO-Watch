void delayed_call_init();
void delayed_call_add(void (*fxn)(void *), void *arg, int calltime, bool isIsr);
void delayTask();