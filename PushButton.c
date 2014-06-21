#include <p18cxxx.h>
#include "PushButton.h"


void PushButton_Init() //initialize the pushbutton in the processor
{
	ANCON1bits.PCFG12 = 1;		// Sets pushbutton as digital
	TRISBbits.TRISB0 = 1;		// Set pushbutton as input
	INTCONbits.INT0IF = 0;		// Clears the interrupt flag
	INTCONbits.INT0IE = 1;		// Enables iterrupts
	INTCONbits.INT0IF = 0;
}
