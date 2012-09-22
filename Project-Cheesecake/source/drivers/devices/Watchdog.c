//////////////////////////////////////////////////////////////////
//                                                              //
//    Watchdog source                                        	//
//    last edited by: Kane Anderson                             //
//    date: March 3, 2012        								//
//                                                              //
//////////////////////////////////////////////////////////////////

#include "Watchdog.h"

// functions //////////////////////////////////

void watchdog_initialize(Watchdog* watchdog)
{
	//
}

void kickTheDog(Watchdog* watchdog)
{
	
	switch (watchdog->WDI->state)
	{
		 case low	:	watchdog->WDI->state = high;
		 				setDigitalOutput(watchdog->WDI);
						break;
		 
		 case high	:	watchdog->WDI->state = low;
						clearDigitalOutput(watchdog->WDI);
						break;
		 
		 default	:	; // do nothing
						
	}
}


