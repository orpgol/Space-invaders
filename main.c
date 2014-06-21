#include <p18cxxx.h>
#include "menu.h"
#include "WDT.h"

void main()
{	
	WDT_init();	
	
	while(1)
	{
		 Menu_Run();
	}

}