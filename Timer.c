#include <p18cxxx.h>
#include "Timer.h"
#include "oled.h"
#include "PushButton.h"
#include "isr.h"
#include "mtouch.h"

#define FOSC 12000
#define PRESCALE0 256
#define DELAY	10

static int x = 1;				// My PushButton flag
static int t = 0;
static int Ms = 0;
static int S = 0;
static int M = 0;
static int H = 0;

void Timer_init()				// timer initialize
{
	T0CONbits.T08BIT = 0;		// set timer0 to 16 bit
	T0CONbits.T0CS = 0;			// set internal clock source (FOSC/4)
	T0CONbits.PSA = 0;			// use prescalaer
	T0CONbits.T0PS = 7;			// set prescaler to 1:256
	
	INTCON2bits.TMR0IP = 1;		// set the priority of timer0 interrupt to high
	INTCONbits.TMR0IF = 0;		// clear the interrupt flag
	INTCONbits.TMR0IE = 1;		// enables iterrupt on timer0 overflow
}


void Timer_delay(int delay)
{
	int count = delay*(FOSC/(4*PRESCALE0));
	count = 0xFFFF-count+1;

	T0CONbits.TMR0ON = 0;		//deactivate timer
	TMR0H = count>>8;
	TMR0L = count%(1<<8);
	INTCONbits.TMR0IF = 0;  	// clear the interrupt flag
	T0CONbits.TMR0ON = 1;		// activate the timer0.
}

void Timer_stop()
{
	T0CONbits.TMR0ON = 0;		// stop the timer
}
