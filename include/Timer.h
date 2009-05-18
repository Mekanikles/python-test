#ifndef _TIMER_H
#define _TIMER_H

#include "Globals.h"

int Timer_init();
void Timer_destroy();

void Timer_addCallback(void (*func)(void* data, Time t), void* data, Time interval);
void Timer_callFunctions(Time currentTime);






#endif
