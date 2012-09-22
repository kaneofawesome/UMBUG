//////////////////////////////////////////////////////////////////
//                                                              //
//    DFlipFlop header                                        	//
//    last edited by: Kane Anderson                             //
//    date: January 12, 2012                                    //
//                                                              //
//////////////////////////////////////////////////////////////////

#ifndef DFLIPFLOP_H
#define DFLIPFLOP_H

#include "../DriversConfig.h"

///////////////////////////////////////////////

// structure //////////////////////////////////
typedef struct
{
	DigitalInput D;
	DigitalInput Set;
	DigitalInput Reset;
	
	DigitalOutput Q;
	DigitalOutput notQ;
}
DFlipFlop;

// functions //////////////////////////////////

void DFF_initialize(DFlipFlop* dff);
void DFF_set(DFlipFlop* dff);
void DFF_reset(DFlipFlop* dff);
void DFF_toggle(DFlipFlop* dff);

#endif
