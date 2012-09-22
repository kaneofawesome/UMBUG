//////////////////////////////////////////////////////////////////
//                                                              //
//    representation of the processor's D2A                     //
//    last edited by: Kane Anderson                             //
//    date: June 26, 2012                                    	//
//																//
//////////////////////////////////////////////////////////////////

#ifndef DIGITALTOANALOGCONVERTER_H
#define DIGITALTOANALOGCONVERTER_H

//////////////////////////////////////////////////////////////////

#include <msp430fg4618.h>
#include "../../../SimpleDefinitions.h"

//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////

void initialize_digitalToAnalogConverter(void);
void startNewDigitalToAnalogConversion(Word digital_12_bit_value);

#endif
