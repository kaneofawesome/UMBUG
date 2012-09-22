//////////////////////////////////////////////////////////////////
//                                                              //
//    Counter header                                        	//
//    last edited by: Kane Anderson                             //
//    date: January 10, 2012                                    //
//                                                              //
//////////////////////////////////////////////////////////////////

#ifndef COUNTER_H
#define COUNTER_H

#include "../DriversConfig.h"

///////////////////////////////////////////////

// structure //////////////////////////////////
typedef struct
{
	DigitalInput enable;
	DigitalOutput count0;
	DigitalOutput count1;
	DigitalOutput count2;
	DigitalOutput count3;
}
Counter;

// functions //////////////////////////////////

void counter_initialize(void);
void counter_startCount(Counter* counter);
void counter_resetCount(Counter* counter);

#endif
