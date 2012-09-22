//////////////////////////////////////////////////////////////////
//                                                              //
//    System config values                                      //
//    last edited by: Kane Anderson                             //
//    date: January 22, 2012                                    //
//                                                              //
//////////////////////////////////////////////////////////////////

#include "SystemConfig.h"

//////////////////////////////////

const Time_ms WatchdogKickTimeInterval = 200; // [ms]
#if CDH_PROCESSOR_COMPILE
	const char* DataLogFileName = "../../UMSATS_CDH_log.txt";
#else
	const char* DataLogFileName = "../../UMSATS_COM_log.txt";
#endif

