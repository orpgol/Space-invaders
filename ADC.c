#include "ADC.h"
#include "oled.h"
#include "mtouch.h"
#include "isr.h"

void ADC_init ()
{
	//CONFIGURE:
	TRISAbits.TRISA5 = 1; // configure RA5/AN4 as input
	ANCON0bits.PCFG4 = 0; // configure AN4 as analog
 	// ADCON0
 	ADCON0bits.VCFG0 = 0; // Vref+ = AVdd
	ADCON0bits.VCFG1 = 0; // Vref- = Avss
	ADCON0bits.ADON = 1; // Turn on ADC, can be turned on only when performing the conversion.
	// ADCON1
	ADCON1bits.ADFM = 1; // Resulst format 1= Right justified
	ADCON1bits.ADCAL = 0; // Normal A/D conversion operation
	ADCON1bits.ACQT = 1; // Acquition time 2 = 4TAD 1=2TAD
	ADCON1bits.ADCS = 2; // Clock conversion bits 2=FOSC/32
}


int ADC_Read (int Channel)			//reads the avarege of 30 reads for an accurate result
{
int value, i;

for(i=0;i<30;i++)					// the avarege loop
{
	value+= ADC_Read_once(Channel);
}

return (value/30);					// return avarage

}



int ADC_Read_once(int Channel)
{

int value;

//Pefrorming conversion
	ADCON0bits.CHS = Channel;  // Select ADC channel 4
	ADCON0bits.GO = 1; 		   // Begin conversion

	while (ADCON0bits.GO);     // Wait for convertion
	value = ADRES;			   // Read the results

return value;
}


void Main_TestADC ()
{

	int value;
	char buffer[100];
	ADC_init();
	Oled_Init();
	Oled_Clear();

	while(1)
	{
		value = ADC_Read(4);			//read the potentiometer
	
		sprintf (buffer,"The value is: %3d ", value);

		Oled_PutString(buffer,2,15,0);
	
		Oled_DelayMs(200);				// delay the reaults for slower display
		
		if (!pbPressedFlag)
		{
			pbPressedFlag = 1;
			return;
		}
	}
	
}