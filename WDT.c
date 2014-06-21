#include "WDT.h"
#include <p18cxxx.h>
#include "oled.h"
#include "PushButton.h"
#include "isr.h"

static int x = 1;				// PushButton_flag 	

//#pragma config WDTEN = OFF	// software control the watchdog
#pragma config WDTPS = 512  // 1:512 postscalar, gives 2sec delay

void WDT_init()				//initialize the watchdog
{
	WDTCONbits.SWDTEN = 1;	// enable watchdog
}


void Main_RunWDT ()
{

char BP[5];
int counter = 0;
PushButton_Init();		 // initialize pushbutton for interrupts

 Oled_Init();
 Oled_Clear();
 WDT_init();

	while (1)
	{
	  while (pbPressedFlag)						// while Pushbutton_Flag is true
		{
		 counter ++;
		 sprintf(BP,"%d",counter);		// convert the variables into a string
		 Oled_PutString(BP,10, 12, 0);						// print the time to the screen
		  
		 ClrWdt();											// clear the watchdog
		}
	  while (pbPressedFlag)												// when pushbutton_flag = false
		{
		
		}
 
	}


}

