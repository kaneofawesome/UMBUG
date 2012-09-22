//////////////////////////////////////////////////////////////////
//                                                              //
//    Binary coded decimal header      	                       	//
//    last edited by: Kane Anderson                             //
//    date: 03/08/2012      	                            	//
//                                                              //
//////////////////////////////////////////////////////////////////

#ifndef BINARYCODEDDECIMAL_H
#define BINARYCODEDDECIMAL_H

// includes //////////////////////////////////////////////////////

#include "../SimpleDefinitions.h"

// definitions ///////////////////////////////////////////////////

typedef enum
{
	BCD_SUNDAY		= 0x01,
	BCD_MONDAY		= 0x02,
	BCD_TUESDAY		= 0x03,
	BCD_WEDNESDAY	= 0x04,
	BCD_THURSDAY	= 0x05,
	BCD_FRIDAY		= 0x06,
	BCD_SATURDAY	= 0x07
}
BCD_Day;

typedef enum
{
	BCD_JANUARY		= 0x01,
	BCD_FEBRUARY	= 0x02,
	BCD_MARCH		= 0x03,
	BCD_APRIL		= 0x04,
	BCD_MAY			= 0x05,
	BCD_JUNE		= 0x06,
	BCD_JULY		= 0x07,
	BCD_AUGUST		= 0x08,
	BCD_SEPTEMBER	= 0x09,
	BCD_OCTOBER		= 0x10,
	BCD_NOVEMBER	= 0x11,
	BCD_DECEMBER	= 0x12
}
BCD_Month;

typedef Byte BCD_Value;

// functions /////////////////////////////////////////////////////

BCD_Value convertDecimalToBinaryCodedDecimal(UI8 input);

#endif
