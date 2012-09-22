
#ifndef TIMERA_H_
#define TIMERA_H_

// includes ////////////////////////////////////////////////////

#include "msp430fg4618.h"
#if COM_PROCESSOR_COMPILE
	#include "../../../application/COM/COMApplication.h"
#endif

#if CDH_PROCESSOR_COMPILE
	#include "../../../application/CDH/CDHApplication.h"
#endif

////////////////////////////////////////////////////////////////

//pointer to function to call for interrupt.  change this to change interrupt function.
extern void (*timerAInt_taccr1)(void);

void initTimerA();

////////////////////////////////////////////////////////////////

#endif

