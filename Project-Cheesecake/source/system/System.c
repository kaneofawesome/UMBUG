//////////////////////////////////////////////////////////////////
//                                                              //
//    System source                                             //
//    last edited by: Kane Anderson                             //
//    date: April 30, 2012                                   	//
//                                                              //
//////////////////////////////////////////////////////////////////

#include "../system/System.h"
#include "../drivers/devices/msp430/TimerA.h"
#include <stdio.h>

Time systemTime;

//////////////////////////////////////////////////////////////////

void system_initialize(void)
{
	disableInterrupts();
	StopMSP430WatchdogTimer;
	drivers_initialize();
	initTimerA();
	
	systemTime.seconds	= 0;
	systemTime.minutes	= 0;
	systemTime.hours	= 0;
	systemTime.date		= 0;
	systemTime.month	= 0;
	systemTime.year		= 0;
	
	
	#if DebugMode
		test_application_initialize();
	#else
		application_initialize();
	#endif
	
}

//////////////////////////////////////////////////////////////////

// 	main has an infinite loop which calls this function every time
void system_main(void)
{	
	// run the program
	#if DebugMode
		test_application_main();
	#else
		application_main();
	#endif
}

//////////////////////////////////////////////////////////////////

void system_abort(void)
{
	// infinite loop
	#if DebugMode
		logLine("");
		logLine("SYSTEM ABORT --------------");
	#endif
	
	for(;;)	{ }
}

//////////////////////////////////////////////////////////////////

void toggleStatusLED(void)
{

	switch (devices.systemStatusLED->state)
	{
		 case low	:	devices.systemStatusLED->state = high;
						setDigitalOutput(devices.systemStatusLED);
						break;
		 case high	:	devices.systemStatusLED->state = low;
						clearDigitalOutput(devices.systemStatusLED);
						break;
		 default	:	; // do nothing
						
	}
	
}

void enableInterrupts(void)
{

	__bis_SR_register(GIE);
	
}

void disableInterrupts(void)
{
	
	__bic_SR_register(GIE);
	
}
