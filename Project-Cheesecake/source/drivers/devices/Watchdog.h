//////////////////////////////////////////////////////////////////
//                                                              //
//    Watchdog header                                        	//
//    last edited by: Kane Anderson                             //
//    date: January 4, 2012                                     //
//                                                              //
//////////////////////////////////////////////////////////////////

#ifndef WATCHDOG_H
#define WATCHDOG_H

#include "../DriversConfig.h"

///////////////////////////////////////////////

// structure //////////////////////////////////
typedef struct
{
	DigitalOutput* WDI;
}
Watchdog;

// functions //////////////////////////////////
#define StopMSP430WatchdogTimer WDTCTL = WDTPW | WDTHOLD
void watchdog_initialize(Watchdog* watchdog);
void kickTheDog(Watchdog* watchdog);

#endif
