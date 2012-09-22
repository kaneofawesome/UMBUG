//////////////////////////////////////////////////////////////////
//                                                              //
//    Log source      		                                  	//
//    last edited by: Kane Anderson                             //
//    date: April 30, 2012      	                            //
//                                                              //
//////////////////////////////////////////////////////////////////

#include "./Log.h"

void logLine(char* string)
{
	printf("%s\r\n", string);
	fflush(stdout);
}

void logUI32(UL32 value)
{
	printf("%d\r\n", value);
	fflush(stdout);
}

void logCombo(char* s, UL32 value)
{
	printf("%s: %d\r\n", s, value);
	fflush(stdout);
}

void initializeLogFile(void)
{
	FILE* fp = fopen(DataLogFileName, "w");
	if (fp == NULL)
	{
		logLine("Error in opening a file...");
		fflush(stdout);
	}
	else
	{
		fp = freopen(DataLogFileName, "w", stdout);
	}
}


