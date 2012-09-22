//////////////////////////////////////////////////////////////////
//                                                              //
//    simple definitions                                        //
//    last edited by: Kane Anderson                             //
//    date: January 17, 2012                                    //
//                                                              //
//////////////////////////////////////////////////////////////////

#ifndef SIMPLEDEFINITIONS_H
#define SIMPLEDEFINITIONS_H

#include <stdbool.h>

// logic //////////////////////////////////////
#define high true
#define low false
///////////////////////////////////////////////

// data lengths ///////////////////////////////
typedef unsigned char UI8;
typedef signed char SI8;
typedef unsigned int UI16;
typedef signed int SI16;
typedef unsigned long UL32;
///////////////////////////////////////////////
typedef signed int Percentage;


// voltage and current ////////////////////////
typedef SI16 Millivolts;
typedef SI16 Milliamps;
#define OneMillivolt 1
#define ThreePointThreeVolts 3300

// byte and word //////////////////////////////
typedef UI8 Byte;
typedef UI16 Word;
Word MultiByte2(Byte b1, Byte b2);
UL32 MultiByte4(Byte b1, Byte b2, Byte b3, Byte b4);

// temperature ////////////////////////////////
typedef UI8	DegreesCelsius;

// time ///////////////////////////////////////
typedef UL32 Time_ms;
#define OneSecond 1000

typedef struct
{
	Byte	seconds;
	Byte	minutes;
	Byte	hours;
	Byte	day;
	Byte	date;
	Byte	month; 
	Byte	year; 
}
Time;

#endif
