#include "BMA150.h"
#include <p18cxxx.h>
#include "oled.h"
#include "isr.h"

// Registers for the SPI module you want to use
#define SPICON1             SSP2CON1
#define SPISTAT             SSP2STAT
#define SPIBUF              SSP2BUF
#define SPISTAT_RBF         SSP2STATbits.BF
#define SPICON1bits         SSP2CON1bits
#define SPISTATbits         SSP2STATbits

#define SPI_INTERRUPT_FLAG  PIR3bits.SSP2IF

// Defines for the PIC18 Starter kit
#define SPICLOCK            TRISCbits.TRISC2
#define SPIIN               TRISDbits.TRISD6
#define SPIOUT              TRISBbits.TRISB3

// Latch pins for SCK/SDI/SDO lines
#define SPICLOCKLAT         LATCbits.LATC2
#define SPIINLAT            LATDbits.LATD6
#define SPIOUTLAT           LATBbits.LATB3

// Port pins for SCK/SDI/SDO lines
#define SPICLOCKPORT        PORTCbits.RC2
#define SPIINPORT           PORTDbits.RD6
#define SPIOUTPORT          PORTBbits.RB3

#define SPIENABLE           SSP2CON1bits.SSPEN

#define BMA150_CS           LATCbits.LATC7
#define BMA150_CS_TRIS      TRISCbits.TRISC7


//**** Private Prototypes ****//
static void SpiPinRemap(void);
static void BMA150_Delay(void);


void BMA150_Init(EBMA150Range range)
{
	WORD i;
	BMA150_REG reg;
	SpiPinRemap();				// set pins functionalities
    SPISTAT = 0x0000;           // power on state
    SPICON1 = 0x82;				// write colision detection(WCOL=1)
								// SPI Master mode, Clock = FOSC/64 (SSPM=2)
    SPISTATbits.CKE = 0;		// Transmit occurs on transition from Idle to active clock state

	// tris setting
    SPICLOCK = 0;				// define the clock as output
    SPIOUT = 0;           		// define SDO1 as output (master or slave)
    SPIIN = 1;              	// define SDI1 as input (master or slave)
    BMA150_CS_TRIS = 0;			// define the CS as output

    SPICON1bits.CKP = 1;		// set clock idle as high
    SPIENABLE = 1;           	// enable synchronous serial port

	reg.val = BMA150_ReadByte(BMA150_CHIP_ID);
    Nop();	

    if(reg.chip_id != 0x2)
    {
        Nop();
    }
	
	/* 
	Bits 5, 6 and 7 of register addresses 14h and 34h do contain critical sensor individual 
	calibration data which must not be changed or deleted by any means. 
 
	In order to properly modify addresses 14h and/or 34h for range and/or bandwidth selection 
	using bits 0, 1, 2, 3 and 4, it is highly recommended to read-out the complete byte, perform bit-
	slicing and write back the complete byte with unchanged bits 5, 6 and 7.  */ 
 
	reg.val = BMA150_ReadByte(BMA150_ADDR14);
    reg.range = range;
	reg.bandwidth = EVBMA150BW_50;
    BMA150_WriteByte(BMA150_ADDR14,reg.val);

	 i = BMA150_ReadByte(BMA150_VERSION);
    Nop();

    i = BMA150_ReadByte(BMA150_ADDR11);
    Nop();

    BMA150_WriteByte(BMA150_ADDR11, 0x00);
    Nop();

    i = BMA150_ReadByte(BMA150_ADDR11);
    Nop();

	
}

void SpiPinRemap(void)
{
	//  UnLock Registers
		EECON2 = 0x55;
		EECON2 = 0xAA;
		PPSCONbits.IOLOCK = 0;
	//  Unlock ends
		
	//  Pin Remapping
		RPOR6 = 9;   // RP6 as SDO2 (o/p)  
		RPOR13 = 10; // RP13 as SCK2 (o/p)
		RPINR21 = 23; // RP23 as SDI2 (i/P)
	//  Pin Remapping ends
	
	// 	Lock Registers
		EECON2 = 0x55;
		EECON2 = 0xAA;
		PPSCONbits.IOLOCK = 1;
	//  Lock Registers ends
}

void BMA150_WriteByte(BYTE address, BYTE data)
{
    BYTE storage;

    //See Important Notes section on page 10 note 1 of the v1.5 datasheet
    storage = 0x00;
    if(address == 0x14 || address == 0x34)
    {
        storage = BMA150_ReadByte(0x14) & 0xE0;	// upper bits should not be changed
    }

    BMA150_CS = 0;	// select the BMA150

	// transmit the address
    SPI_INTERRUPT_FLAG = 0;
    SPIBUF = address;
    while (!SPI_INTERRUPT_FLAG);

	BMA150_Delay();

	// transmit the data
    SPI_INTERRUPT_FLAG = 0;

    //See Important Notes section on page 10 note 2 of the v1.5 datasheet
    if(address == 0x0A)
    {
        SPIBUF = data & 0x7F;	// in address 0x10 bit 7 should be 0.
    }
    else
    {
        SPIBUF = data | storage;	// old values for addresses 0x14 & 0x34
    }

    while (!SPI_INTERRUPT_FLAG);

    BMA150_CS = 1;	// unselect the BMA150
}


BYTE BMA150_ReadByte(BYTE address)
{
    BMA150_CS = 0;	// select the BMA150

	// transmit the address
    SPI_INTERRUPT_FLAG = 0;
    SPIBUF = BMA150_READ | address;	// set the read bit in the address
    while (!SPI_INTERRUPT_FLAG);

	BMA150_Delay();

	// receive the data
    SPI_INTERRUPT_FLAG = 0;
    SPIBUF = 0x00;					// clear the buffer
    while (!SPI_INTERRUPT_FLAG);	// wait for the data

    BMA150_CS = 1;	// unselect the BMA150

    return SPIBUF;
}

void BMA150_Delay(void)
{
	int i;

	for (i=0;i<64;i++);
}


void BMA150_GetXYZ(PBMA150_XYZ pAcc)
{
	BYTE temp;
	
	temp = (BMA150_ReadByte (0x02)>>6);
	pAcc->x = (signed char)BMA150_ReadByte (0x03);
	pAcc->x <<= 2;
	pAcc->x |= temp;

	temp = (BMA150_ReadByte (0x04)>>6);
	pAcc->y = (signed char)(BMA150_ReadByte (0x05));
	pAcc->y <<= 2;
	pAcc->y |= temp;

	temp = (BMA150_ReadByte (0x06)>>6);
	pAcc->z = (signed char)(BMA150_ReadByte (0x07));
	pAcc->z <<= 2;
	pAcc->z |= temp;
}
