#include <p18cxxx.h>
#include "PushButton.h"


void PushButton_Init()
{
	ACON1bits.PCFG12 = 1;
	TRISbits.TRISB0 = 1;
}

EPushButton PushButton_Read()
{
	if (PORTbits.RB0)
		return 	EVPushButton_Realeased;
	else
		return 	EVPushButton_Pressed;
}