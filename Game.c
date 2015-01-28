/********************************************************************************/
/* FILE NAME:  	invaders for pic 18			                                    */
/* CREATED BY:  Orpaz Goldstein                                                 */
/* FILE CREATION DATE: 02/02/2014                                               */
/*==============================================================================*/
/*                          Copyright (c) Orpaz Goldstein.                      */
/*                                                                              */
/* This document contains confidential information which is protected by        */
/* copyright and is proprietary to Orpaz Goldstein. No part of this document    */
/* may be used, copied, disclosed, or conveyed to another party without prior   */
/* written consent of Orpaz Goldstein.                                          */
/********************************************************************************/
/* NOTES:																		*/
/*                                                                              */
/********************************************************************************/


#include "Game.h"

#define DELAY	10			// defines the timer delay
static int Ms = 0;			// Milisecond counter

void Main_Timer()
{
	Timer_delay(DELAY);
	Ms++;
}

typedef enum {easy = 20, medium = 22, medhard = 26,  hard = 30} level;	// levels!



void game()
{
	char A[] = {"F"};				// ship
	char S[] = {"H"};				// shot
	char E[] = {" "};				// erase
	char alien1a[] = {"A"}; 		// alien1 open
	char alien1b[] = {"B"}; 		// alien1 closed
	char alien2a[] = {"C"}; 		// alien2 open
	char alien2b[] = {"D"}; 		// alien2 closed
	char hit[] = {"G"};				// hit 
	int r = 7, c = 0;				// ship location
	int x = 0, y = -2;				// shot location
	int z = 0, w = 0;				// alien indexes
	int i = 0;						// index
	BOOL j = 1, g = 1;				// movement BOOLS
	int offset = 8;					// alien offset (on screen)
	int time_decay = 100;			// decides how fast the aliens are going
	int counter = 20;				// counts how many aliens we have left on screen
	unsigned short int score = 0;	// keeps the player's score
	level current_lvl = easy;		// level enum
	BOOL alien_row[2][10];			// 2d array of aliens
	BMA150_XYZ bma;					// struct of accelometer values

	Oled_Init();
	Timer_init();						 // initialize the timer
	PushButton_Init();					 // initialize the pushbutton
	pbPressedFlag = 1;					 // reset the pushbutton flag
	BMA150_Init(EVBMA150Range_2G);
	INTCONbits.GIEH = 1;	 			 // enable high-priority interrupt
	RCONbits.IPEN = 1;      		   	 // enable priority
	
	Timer_delay(DELAY);					 // start the timer!

	while(pbPressedFlag)
	{	
		Oled_Clear();

		SetMode(Aliens);					 		// set write mode to aliens
		Oled_PutString(A,r, c, 0);			 		// put the ship on screen

		for (i=0; i<10; i++)						// initialize array of aliens
		{											// {
			Oled_PutString(alien1a, 0, i*8, 0);
			alien_row[0][i] = 1;		
			Oled_DelayMs(25);	
		}
		for (i=0; i<10; i++)
		{
			Oled_PutString(alien2b, 1, i*8, 0);	
			alien_row[1][i] = 1;
			Oled_DelayMs(25);						// 
		}											

		z = 0; w = 0;								// alien indexes init
		counter = 20;								// counter init
		time_decay = 100;							// time_decay init
													// end initialize 
		
		if (score == 300)							// each round is a little faster...!
			current_lvl = medium;
		if (score == 600)
			current_lvl = medhard;
		if (score == 900)
			current_lvl = hard;

		while(pbPressedFlag)
		{
	
			BMA150_GetXYZ(&bma);
			
			if (bma.y > 100)								// control the ship x axis movement
			{												// {
				if (c != 123)
					{
						Oled_PutString(E, r, c, 0);			// Erase last location
						Oled_PutString(A, r, ++c, 0);		// New location
					}
			}
	
			if (bma.y < -100)
			{	
				if (c != 0)
					{
						Oled_PutString(E, r, c, 0);
						Oled_PutString(A, r, --c, 0);		
					}
			}												// } end ship x axis control
	
	
			if (y >= 0)										// if there is shot move shot one space up
			{
				Oled_PutString(E, y, x, 0);					// Erase last location
				Oled_PutString(S, --y, x, 0);				// New location
			}
			if (y == -1)	
				Oled_PutString(E, y, x, 0);					// if shot missed erase & end shoot
			
			
			if (mTouch_GetPushedButton() == 0 && y < 0)		// shoot button
			{	
				x = c;
				y = r-1;
				Oled_PutString(S, y, x, 0);
			}
	
			if (y == w || y == w+1)							// check for a hit, go in if shot is at same height as aliens
			{
				for (i = 0; i<10; i++)
				{
					if ((x+3) >= z+(i*offset) && (x+3) < z+((i+1)*offset) && alien_row[1][i] != 0)		// Begin hit loop	(low_row of aliens)
					{																						// {
						Oled_PutString(E, w+1, z+(i*offset), 0);											// 		add shot_x offset ( for oled accuracy)
						Oled_PutString(hit, w+1, z+(i*offset), 0);											//		then check witch alien is hit, 
						Oled_DelayMs(25);																	// 		if he is not dead allreay, start the loop.
						Oled_PutString(E, w+1, z+(i*offset), 0);
						alien_row[1][i] = 0;	
						Oled_PutString(E, y, x, 0);																// 
						y = -2;																				// 		kill the shot
						score += 10;																		//    	update score, 
						counter--;																			// 		lower counter
						break;																				//		end the loop.
					}																						// }
	
	
					else if ((x+3) >= z+(i*offset) && (x+3) < z+((i+1)*offset) && alien_row[0][i] != 0)			// same as above for high_row of aliens
					{
						Oled_PutString(E, w, z+(i*offset), 0);
						Oled_PutString(hit, w, z+(i*offset), 0);
						Oled_DelayMs(25);
						Oled_PutString(E, w, z+(i*offset), 0);
						alien_row[0][i] = 0;	
						Oled_PutString(E, y, x, 0);	
						y = -2;		
						score += 20;
						counter--;
						break;
					}
	
				}
			}
	
			if (Ms > time_decay)
			{	
				for (i=0; i<10; i++)														// erase aliens from old location
					if (alien_row[0][i] != 0)												// if alien is alive...
					{
						Oled_PutString(E, w, z+(offset*i), 0);
					}
				for (i=0; i<10; i++)
					if (alien_row[1][i] != 0)
					{									
						Oled_PutString(E, w+1, z+(offset*i), 0);
					}
			
				for (i=0; i<10; i++)														// decide how to move...{	
				{
					if (alien_row[0][i] != 0 && z+(offset*i) == 120 && w%2 == 0)			// if end of the line
					{ 
						w += 1;																// increase line 
						break;
					}
						
					else if (alien_row[1][i] != 0 && z+(offset*i) == 120 && w%2 == 0)		// same with 2nd row
					{		
						w += 1;
						break;
					}
			
					else if (alien_row[0][i] != 0 && z+(offset*i) == 0 && w != 0 && w%2 == 1)	// if start of the line 
					{
						w += 1;																	// increase line 
						break;
					}
	
					else if (alien_row[1][i] != 0 && z+(offset*i) == 0 && w != 0 && w%2 == 1)	// same with 2nd row
					{
						w += 1;
						break;
					}
	
					else if (i == 9 && w%2 == 0)												// if NOT special case on even line 
					{
						z += offset;															// Go forward
						break;
					}
	
					else if (i == 9)															// if NOT special case on odd line
					{
						z -= offset;															// Go back }
						break;
					}
				}
				
			
				for (i=0; i<10; i++)											// print first row of aliens
				{
					if (alien_row[0][i] != 0)									// if alien is alive...
					{
						if (j)													// printing either open leg aliens or closed leg aliens				
							Oled_PutString(alien1b, w, z+(offset*i), 0);
						else
							Oled_PutString(alien1a, w, z+(offset*i), 0);
					}
				}
	
				for (i=0; i<10; i++)											// print second row of aliens
				{
					if (alien_row[1][i] != 0)
					{
						if (j)
							Oled_PutString(alien2a, w+1, z+(offset*i), 0);
						else
							Oled_PutString(alien2b, w+1, z+(offset*i), 0);
					}
				}
				
				Ms = 0;
				j = !j;															// next round print the other set of aliens						
			}
			
			if (counter < current_lvl - 4)					// check if speed needs to be increased:
				time_decay = 60;							// (speed is a factor of 'current_lvl' + amount of aliens on screen)
			if (counter < current_lvl - 8)					// to increase speed we reduce the 'time_decay'
				time_decay = 40;							
			if (counter < current_lvl - 12)
				time_decay = 20;
			if (counter < current_lvl - 16)
				time_decay = 10;
			if (counter < current_lvl - 18)
				time_decay = 0;
	
			if (w >= 6)										// if aliens touched ground: THEY WIN
			{	
				if (w == 7)
				{
					Oled_DelayMs(100);
					game_over(score);
					return;	
				}

				for (i=0; i<10; i++)									
					if (alien_row[1][i] != 0)
					{
						Oled_DelayMs(100);
						game_over(score);
						return;
					}
			}
	
			if (counter == 0)								// if no more aliens on screen: YOU WIN
				break;

			ClrWdt();											// clear the watchdog
		}
	}

}




void game_over(int score)						// game over!!! too bad.
{
	unsigned short int address = 0xAAAA;		// adress in the EEPROM
	int len = 6;								// 3 double length (16 bit) high scores
	static BYTE data[6];
	char over[] = {"Game-Over"};
	char alien1a[] = {"A"}; 					// alien1 open
	char alien2a[] = {"C"}; 					// alien2 open
	char buff[20];								
	unsigned short int temp = 0;
	int i = 0;
	
	Oled_Init();								// initialize screen
 	Oled_Clear();								// clear screen
	mTouch_Init();								// touchpad initialize
 	mTouch_Calibrate();							

	
	SetMode(Words);								// set to print words
	Oled_PutString(over, 1, 40, 0);
	SetMode(Aliens);							// set to print aliens
	Oled_PutString(alien1a, 0, 15, 0);
	Oled_PutString(alien2a, 0, 20, 0);

	RomRead(address, data, len);				// read EEPROM for high scores
	
	for (i=0; i<len; i+=2)
	{
		if  (score > ((data[i]*256) + (data[i+1])))		// check if current score is higher then high scores
			{
				temp = ((data[i]*256) + (data[i+1]));	// if score is higher, put it in place in the High-Score board
				data[i] = (score>>8) & 0xFF;
				data[i+1] = score & 0xFF;	
				score = temp;
			}
	}
	
	for (i=0; i<len; i+=2)								// print out the High-Score board
	{	
		temp = (data[i]*256) + (data[i+1]);				//**note for calculation** 8 bit MSB*256 + 8 bit LSB == 16 bit word
		SetMode(Words);
		sprintf(buff,"High-score %d", temp); 
		Oled_PutString(buff, 3+i, 40, 0);
	}

	RomDelete(address);									// delete old High-Scores
	RomWrite(address, data, len);						// Write new High-Scores
	
	Oled_DelayMs(100);									// delay to prevent jumping to main menu
	while (mTouch_GetPushedButton() == EVmTouchButton_NumberOfPads)		// Press any touch key to continue...
		ClrWdt();														// clear the watchdog
}


void about()
{
	char line1[] = {"  M     M  "};									// This is art!
	char line2[] = {"   M   M   "};
	char line3[] = {"  MMMMMMM  "};
	char line4[] = {" MM MMM MM "};
	char line5[] = {"MMMMMMMMMMM"};
	char line6[] = {"M MMMMMMM M"};
	char line7[] = {"M M     M M"};
	char line8[] = {"   MM MM   "};
	char made1[] = {"Orpaz"};
    char made2[] = {"Goldstein};

	Oled_Clear();
	SetMode(Aliens);					 								// set write mode to aliens
	Oled_PutString(line1, 0, 0, 0);			 							// put the picture on screen
	Oled_PutString(line2, 1, 0, 0);
	Oled_PutString(line3, 2, 0, 0);
	Oled_PutString(line4, 3, 0, 0);
	Oled_PutString(line5, 4, 0, 0);
	Oled_PutString(line6, 5, 0, 0);
	Oled_PutString(line7, 6, 0, 0);
	Oled_PutString(line8, 7, 0, 0);
	SetMode(Words);
	Oled_PutString(made1, 4, 80, 0);
	Oled_PutString(made2, 5, 80, 0);
	Oled_DelayMs(100);

	while (mTouch_GetPushedButton() == EVmTouchButton_NumberOfPads)		// Press any touch key to continue...
		ClrWdt();														// clear the watchdog
}