#ifndef TIMER_H
#define TIMER_H
#include <p18cxxx.h>

void Timer_init();

void Timer_delay(int delay);

void Timer_stop();

void Main_ButtonPushed();

void Main_RunStopper ();


#endif