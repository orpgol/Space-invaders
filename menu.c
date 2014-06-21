

/*------------------------------------------------------------------------------*/
/* INCLUDE FILES                                                                */
/*------------------------------------------------------------------------------*/
// standard headers
#include <p18cxxx.h>

// user headers
#include "Menu.h"
#include "oled.h"

#include "mtouch.h"

#include "BMA150.h"

#include "Timer.h"

#include "WDT.h"
#include "Game.h"

/*------------------------------------------------------------------------------*/
/* LOCAL CONSTATS DEFINITION                                                    */
/*------------------------------------------------------------------------------*/

#define MENU_ENTRIES_SHIFT	20

#define ENTRY_NAME_MAX_LEN	20
#define MENU_MAX_ENRIES		4

/*------------------------------------------------------------------------------*/
/* LOCAL MACROS DEFINITION                                                      */
/*------------------------------------------------------------------------------*/
#ifndef NULL
#define NULL	0
#endif

/*------------------------------------------------------------------------------*/
/* TYPES DEFINITION                                                             */
/*------------------------------------------------------------------------------*/

typedef enum {
	EVMenuIndex_Main = 0,
	EVMenuIndex_Timers,
	EVMenuIndex_Len
} EMenuIndex;

typedef struct {
	char	entryName[ENTRY_NAME_MAX_LEN];
	char	nextMenu;
	PFMenuHandler	pfHandler;
} SMenuEntry;

typedef struct {
	char	menuTitle[ENTRY_NAME_MAX_LEN];
	int		len;
	char	prevMenu;
	SMenuEntry	entries[MENU_MAX_ENRIES];
} SMenu;

/*------------------------------------------------------------------------------*/
/* LOCAL FUNCTIONS DECLERATION                                                  */
/*------------------------------------------------------------------------------*/

static void Menu_Show(SMenu *menu, int select);


/*------------------------------------------------------------------------------*/
/* LOCAL VARIABLES                                                              */
/*------------------------------------------------------------------------------*/

static SMenu	sMenu[] = {
	{"Main", 2, -1, {
		{"Game", -1, game},
		{"About", -1, about},
		}
	}
};


/*------------------------------------------------------------------------------*/
/* EXPORT FUNCTIONS DEFINITIONS                                                 */
/*------------------------------------------------------------------------------*/

/********************************************************************************
*                                                                               *
*  DATE: 15/01/2012                                                             *
*                                                                               *
*  DESCRIPTION:																	*
*                                                                               *
*  RETURN VALUE:																*
*                                                                               *
*  AUTHOR: Oren Kapah															*
*                                                                               *
********************************************************************************/
void Menu_Run(void)
{
	EMenuIndex	menuIndex = EVMenuIndex_Main;
	int curSel = 0;
	BOOL	refresh = TRUE;

	Static_menu();									// my addition, show the static menu

	while (1)
	{
		// show the menu
		if (refresh)
		{
			Menu_Show(&sMenu[menuIndex], curSel);
			refresh = FALSE;
			while (mTouch_GetPushedButton() != EVmTouchButton_NumberOfPads);	// wait for the finger to be removed
		}

		// check which button was touched
		switch (mTouch_GetPushedButton())
		{
		case EVmTouchButton_Right:	// select
			// check if we should change the current menu
			if (sMenu[menuIndex].entries[curSel].nextMenu != (-1))
			{
				menuIndex = sMenu[menuIndex].entries[curSel].nextMenu;
				curSel = 0;
				refresh = TRUE;
			}
			// check if we should run a handler function
			else if (sMenu[menuIndex].entries[curSel].pfHandler != NULL)
			{
				(*sMenu[menuIndex].entries[curSel].pfHandler)();
				refresh = TRUE;

				Static_menu();									// my addition, show the static menu
			}
			break;
		case EVmTouchButton_Up:		// move one entry up
			if (curSel > 0)
				curSel--;
			refresh = TRUE;
			break;
		case EVmTouchButton_Down:	// move one entry up
			if (curSel < (sMenu[menuIndex].len-1))
				curSel++;
			refresh = TRUE;
			break;
		case EVmTouchButton_Left:	// cancel
			// check if we have a previous menu
			if (sMenu[menuIndex].prevMenu != (-1))
			{
				menuIndex = sMenu[menuIndex].prevMenu;
				curSel = 0;
				refresh = TRUE;
			}
			break;
		}



		ClrWdt();											// clear the watchdog
	}
} // End of Menu_Run




static void Menu_Show(SMenu *menu, int select)
{
	int i;	


	for (i=0; i<menu->len; i++)
		Oled_PutString(menu->entries[i].entryName, i+6, MENU_ENTRIES_SHIFT, i==select);

} // End of Menu_Show




void Static_menu()

{

	char score[]  = {"hi-score"};

	char buff[4];

	char play[]	  = {"PLAY"};

	char space[]  = {"SPACE INVADERS"};

	char press[]  = {"Press R button"};

	char alien1[] = {"C = 10 pts"};

	char alien2[] = {"A = 20 pts"};

	unsigned short int address = 0xAAAA;		// adress in the EEPROM

	int temp, len = 2;							// 1 high score (8 bit MSB and 8 bit LSB)

	static BYTE data[2];



	Oled_Init();

 	Oled_Clear();

	mTouch_Init();

 	mTouch_Calibrate();

	

	SetMode(Aliens);

	Oled_PutString(alien1, 4, 30, 0);

	Oled_PutString(alien2, 5, 30, 0);



	SetMode(Words);

	Oled_PutString(score, 0, 15, 0);

	Oled_PutString(play, 2, 50, 0);

	Oled_PutString(space, 3, 20, 0);



	RomRead(address, data, len);				// get the high score.

	temp = (data[0]*256) + (data[1]);			//**note for calculation** 8 bit MSB*256 + 8 bit LSB == 16 bit word

	SetMode(Words);

	sprintf(buff,"%d", temp); 

	Oled_PutString(buff, 0, 85, 0);

}