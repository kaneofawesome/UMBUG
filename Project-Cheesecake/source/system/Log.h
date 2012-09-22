//////////////////////////////////////////////////////////////////
//                                                              //
//    Log header      		                                  	//
//    last edited by: Kane Anderson                             //
//    date: April 30, 2012      	                            //
//                                                              //
//////////////////////////////////////////////////////////////////

#ifndef LOG_H
#define LOG_H

#include "../drivers/DriversConfig.h"
#include "./SystemConfig.h"
#include <stdio.h>

// for printing a line to the file
void logLine(char* s);
void logUI32(UL32 value);
void logCombo(char* s, UL32 value);

void initializeLogFile(void);

#endif
