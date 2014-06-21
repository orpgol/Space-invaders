#include "EEPROM.h"


#define ERASE_BLOCK_SIZE	1024
/* Locals macros definitaion */
//#define TBL_READP() asm("TBLRD*+")

#define	TBL_READ()	_asm TBLRD _endasm
#define	TBL_READINC()	_asm TBLRDPOSTINC _endasm
#define TBL_WRITE()	_asm TBLWT 	_endasm
#define TBL_WRITEINC()	_asm TBLWTPOSTINC _endasm

#define SET_TBLPTR(address)\
{\
	TBLPTRU = address>>16%0x100;	/* set the top address bits */\
	TBLPTRH = address>>8%0x100;		/* set the high address bits */\
	TBLPTRL = address%0x100;		/* set the low address bits */\
}

#define WRITE_SEQUENCE()\
{\
	EECON1bits.WREN = 1;			/* enable write*/\
	INTCONbits.GIE = 0;				/* disable interrupt*/\
	EECON2 = 0x55;					/* unlock code*/\
	EECON2 = 0xAA;					/*  "" */\
	EECON1bits.WR = 1;				/* start write sequence*/\
	EECON1bits.WREN = 0;			/* disable write*/\
	INTCONbits.GIE = 1;				/* enable interrrupt*/\
}


void RomRead(unsigned short int address, BYTE* data, int len)
{
	int i = 0;
	SET_TBLPTR(address);			// set address pointer

	for (i = 0; i<len; i++)
	{
		TBL_READINC();				// read one slot and move pointer one slot up
		data[i] = TABLAT;			// put the data in our array
	}	
		
}

void RomWrite(unsigned short int address, BYTE* data, int len)
{
	int i = 0;
	int j = 0;
	
	while(len > 0)								// while there are still bytes to write
	{
		if (len < 64)							// if we have less then 64 bytes left
		{
			EECON1bits.WPROG = 1;				// set write to 2 bytes
			
			for (i = 0; i<2; i++, j++)
			{
				SET_TBLPTR(address+j);			// set address pointer
				TABLAT = data[j];				// put data in TABLAT
				TBL_WRITE();					// write the data
			}
			WRITE_SEQUENCE();					
			len-=2;								// -2 bytes left...
		}

		if (len > 64)							// if we have more then 64 bytes left
		{
			EECON1bits.WPROG = 0;				// set write to 64 bytes
			
			for (i = 0; i<64; i++, j++)
			{
				SET_TBLPTR(address+j);
				TABLAT = data[j];
				TBL_WRITE();
			}
			len-=64;							// -64 bytes left
			WRITE_SEQUENCE();
		}	
	}

}

void RomDelete(unsigned short int address)		// delete the data
{
	SET_TBLPTR(address);						// set address pointer
	EECON1bits.FREE = 1;						// set delete one block (1024)
	WRITE_SEQUENCE();							// write sequence to delete
	EECON1bits.FREE = 0;						// disable delete
}


