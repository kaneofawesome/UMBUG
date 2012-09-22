//////////////////////////////////////////////////////////////////
//                                                              //
//    main program	                                            //
//    last edited by: Kane Anderson                             //
//    date: March 3, 2012                                    	//
//																//
//	  This is where the magic starts							//
//                                                              //
//////////////////////////////////////////////////////////////////

#include <msp430fg4618.h>
#include "application/PWR/UART.h"
#include "application/COM/COMApplication.h"

extern void system_initialize(void);
extern void system_main(void);

//////////////////////////////////////////////////////////////////

void main(void)
{
	//volatile unsigned int i;
	 
	
	system_initialize();
	// InitUART(); // TODO: removed from merge. use for testing uart
	//for(;;) // TODO: removed from merge. use for testing uart
	//{ // TODO: removed from merge. use for testing uart
	//	while (!(IFG2 & UTXIFG1));                // USART1 TX buffer ready? // TODO: removed from merge. use for testing uart
	//		TXBUF1 = 0xAB;           // TODO: removed from merge. use for testing uart
	//} // TODO: removed from merge. use for testing uart
	for(;;)
	{
		system_main();
	}
	
}
