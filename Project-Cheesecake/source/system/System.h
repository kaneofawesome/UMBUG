//////////////////////////////////////////////////////////////////
//                                                              //
//    System header                                             //
//    last edited by: Kane Anderson                             //
//    date: January 22, 2012                                    //
//                                                              //
//////////////////////////////////////////////////////////////////

#ifndef SYSTEM_H
#define SYSTEM_H

//////////////////////////////////

#include "../userConfig.h"
#include "../drivers/Drivers.h"
#include "../system/SystemConfig.h"
#include "../system/BinaryCodedDecimal.h"
#include "../system/UMSAT_Math/NaturalLogarithm.h"
#include <stdlib.h>

#if DebugMode
	#include "stdlib.h"
	#include "stdio.h"
	#include "assert.h"
	#include "./Log.h"

	extern void test_application_initialize(void);
	extern void test_application_main(void);
#endif

//////////////////////////////////

extern Time systemTime;

//////////////////////////////////

void system_initialize(void);
void system_main(void);
void system_abort(void);
void toggleStatusLED(void);
void enableInterrupts(void);
void disableInterrupts(void);
//////////////////////////////////

extern void application_main(void);
extern void application_initialize(void);


#endif
