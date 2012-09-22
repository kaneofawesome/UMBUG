//////////////////////////////////////////////////////////////////
//                                                              //
//    Radio header                                        		//
//    last edited by: Kane Anderson                             //
//    date: June 26, 2012                                       //
//                                                              //
//////////////////////////////////////////////////////////////////

#ifndef RADIO_H
#define RADIO_H

#include "../IOTypes.h"

///////////////////////////////////////////////

// structure //////////////////////////////////
typedef struct
{
	AnalogOutput* microphone;
	DigitalOutput* pushToTalk;
}
Radio;

// functions //////////////////////////////////

void radio_initialize(Radio* radio);

#endif
