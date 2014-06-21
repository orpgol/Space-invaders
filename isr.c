#include "WDT.h"
#include <p18cxxx.h>
#include "isr.h"

int pbPressedFlag = 1;

#pragma interrupt HighPriorityIsr  	 // enables high priority interrupts
void HighPriorityIsr(void)
{
	if (INTCONbits.INT0IF)
	{
		pbPressedFlag = !pbPressedFlag;		 //Sets the flag for main
		INTCONbits.INT0IF = 0; 		 //clear the INT0 interrupt flag	
	}
	
	else if (INTCONbits.TMR0IF)
	{
		Main_Timer();				// sets the flag for timer in main
		INTCONbits.TMR0IF = 0;		// clear the flag
	}
}

#pragma interruplow LowPriorityIsr   // enables low priority iterrupts
void LowPriorityIsr()
{
}

#pragma code HIGH_INTERRUPT_VECTOR = 0x08	
void High_ISR(void)
{
	_asm goto HighPriorityIsr _endasm		// sends back to HighPriorityIsr function
}

#pragma code LOW_INTERRUPT_VECTOR = 0x18
void Low_ISR(void)
{
	_asm goto LowPriorityIsr _endasm 
}
#pragma code

