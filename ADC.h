#ifndef ADC_H
#define ADC_H
#include <p18cxxx.h>

void ADC_init();				//initialize the potentiometer

int ADC_Read(int Channel);

void Main_TestADC ();

#endif