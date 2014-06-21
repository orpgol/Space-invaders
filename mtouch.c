/********************************************************************
  File Information:
    FileName:     	mtouch.c
    Dependencies:   See INCLUDES section
    Processor:      PIC18F46J50
    Hardware:       PIC18F Starter Kit
    Complier:  	    Microchip C18 (for PIC18)
    Company:        Microchip Technology, Inc.
    
    Software License Agreement:
    
    The software supplied herewith by Microchip Technology Incorporated
    (the �Company�) for its PIC� Microcontroller is intended and
    supplied to you, the Company�s customer, for use solely and
    exclusively on Microchip PIC Microcontroller products. The
    software is owned by the Company and/or its supplier, and is
    protected under applicable copyright laws. All rights are reserved.
    Any use in violation of the foregoing restrictions may subject the
    user to criminal sanctions under applicable laws, as well as to
    civil liability for the breach of the terms and conditions of this
    license.
    
    THIS SOFTWARE IS PROVIDED IN AN �AS IS� CONDITION. NO WARRANTIES,
    WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
    TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
    PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
    IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
    CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.

  File Description:
    
    Change History:
     Rev   Date         Description
     1.0                Initial release

********************************************************************/

/******** Include files **********************/

#include "mtouch.h"
#include <p18cxxx.h>
#include "oled.h"
#include "isr.h"
/*********************************************/


/******** Configuration Options **************/
#define MTOUCH_CHANNELS	4
#define MIN_TRIM		0xE1	// -31
#define MAX_TRIM		0x1F	// 31
#define LOG_AVERAGE_TIMES    1
#define AVERAGE_TIMES        (1<<LOG_AVERAGE_TIMES)
/********************************************/


/*************** Variables ******************/
char g_mTouchCalibrationITRIM[MTOUCH_CHANNELS];
/********************************************/

void mTouch_Delay(void);

void InitADC(void)
{
	/**************************************************************************/
	//Setup AD converter;
	/**************************************************************************/
	TRISA |= 0x0F; //set channels 0-3 as an input

	// Configured ANx as an analog channel
	// ANCON0
	ANCON0 &= 0XF0;	// set AN0-3 as analog inputs

	// ADCON1
	ADCON1bits.ADFM=1; // Resulst format 1= Right justified
	ADCON1bits.ADCAL=0; // Normal A/D conversion operation
	ADCON1bits.ACQT=1; // Acquition time 7 = 20TAD 2 = 4TAD 1=2TAD
	ADCON1bits.ADCS=2; // Clock conversion bits 6= FOSC/64 2=FOSC/32
	ANCON1bits.VBGEN=1; // Turn on the Bandgap needed for Rev A0 parts
	// ADCON0
	ADCON0bits.VCFG0 =0; // Vref+ = AVdd
	ADCON0bits.VCFG1 =0; // Vref- = AVss
	ADCON0bits.ADON=1; // Turn on ADC
}

/**************************************************************************/
/*Setup CTMU *****************************************************************/
/**************************************************************************/
void InitCTMU(void)
{
	/**************************************************************************/
	//Setup CTMU;
	/**************************************************************************/
	CTMUICON=0x03;				// 100*Base Current (55uA)
	CTMUCONHbits.IDISSEN=0;		// current source is not grounded
	CTMUCONHbits.EDGEN=0;		// Edges are blocked
	CTMUCONLbits.EDG1POL=1;		// positive Edge1 response
	CTMUCONLbits.EDG2POL=1;		// positive Edge2 response
	CTMUCONLbits.EDG1STAT=0;	// Edge1 event has not occurred
	CTMUCONLbits.EDG2STAT=0;	// Edge2 event has not occurred
	PIR3bits.CTMUIF=0;			// clear the interrupt flag
	CTMUCONHbits.CTMUEN=1;		// enable the CTMU
}

void mTouch_Init(void)
{
	InitCTMU();
	InitADC();
	mTouch_Calibrate();
}

unsigned int mTouch_ReadButtonOnce(EmTouchButton buttonID)
{
	/* Storage for reading the voltage */
	unsigned int Vread; 

	/* Select ADC channel */
	ADCON0bits.CHS = buttonID; 

	/* Set the ITRIM value for the callibration of the channel */
	CTMUICONbits.ITRIM = g_mTouchCalibrationITRIM[buttonID];

	/* Enable the CTMU */
	CTMUCONHbits.CTMUEN = 1;

	/* Drain charge on the circuit */
	CTMUCONHbits.IDISSEN = 1; 

	mTouch_Delay();

	/* End drain of circuit */
	CTMUCONHbits.IDISSEN = 0;
 
	/* Begin charging the circuit using CTMU current source */
	CTMUCONLbits.EDG1STAT = 1; 

	mTouch_Delay();

	/* Stop charging circuit */
	CTMUCONLbits.EDG1STAT = 0;

	/* Make sure A/D interrupt is not set */
	PIR1bits.ADIF = 0; 
	
	/* Begin A/D conversion */
	ADCON0bits.GO=1; 
	//Wait for A/D convert complete
	while(!PIR1bits.ADIF);

	/* Get the value from the A/D */
	Vread = ADRES;

	return Vread;
}

unsigned int mTouch_ReadButton(EmTouchButton buttonID)
{
	int i;
	unsigned int Vread = 0; 
	
	for (i=0; i<AVERAGE_TIMES; i++)
		Vread += mTouch_ReadButtonOnce(buttonID);

	return Vread>>LOG_AVERAGE_TIMES;
}

void mTouch_Calibrate(void)
{
	unsigned int Vread;
	unsigned char i;

	for (i = 0; i < MTOUCH_CHANNELS; i++)
	{
		g_mTouchCalibrationITRIM[i] = 0;

		Vread =  mTouch_ReadButton(i);
		if (Vread < MTOUCH_READ_VALUE_RELEASED)
		{
			do
			{
				if (g_mTouchCalibrationITRIM[i] == MAX_TRIM)
				{
					/* Callibration failed */
					g_mTouchCalibrationITRIM[i] = 0;
					break;
				}
				g_mTouchCalibrationITRIM[i] ++;
				Vread = mTouch_ReadButton(i);
			}while (Vread < MTOUCH_READ_VALUE_RELEASED);	
		}
		else if(Vread > MTOUCH_READ_VALUE_RELEASED)
		{
			do
			{
				if (g_mTouchCalibrationITRIM[i] == MIN_TRIM)
				{
					/* Callibration failed */
					g_mTouchCalibrationITRIM[i] = 0;
					break;
				}
				g_mTouchCalibrationITRIM[i] --;
				Vread = mTouch_ReadButton(i);
			}while (Vread > MTOUCH_READ_VALUE_RELEASED);	
		}
	}
}

void mTouch_Delay(void)
{
//	The delay of calling this function is enough
}



EmTouchButton mTouch_GetPushedButton()	//this function returns the button that was touched
{
	unsigned int temp;
	int i = 0;

	mTouch_Init();
 	mTouch_Calibrate();
	
		for (i = 0; i < 4; i++)
			{
				temp = mTouch_ReadButton(i);			// check what button was touched
				if (temp < 650 )
				{
					return i;
				}
			}
		return EVmTouchButton_NumberOfPads;
}
