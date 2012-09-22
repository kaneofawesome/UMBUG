//////////////////////////////////////////////////////////////////
//                                                              //
//    User config header                                        //
//    last edited by: Craig Nemeth                              //
//    date: May 14, 2012	                                    //
//                                                              //
//////////////////////////////////////////////////////////////////

#ifndef USERCONFIG_H_
#define USERCONFIG_H_

///////////////////////////////////////////////////////////////////////////////////////////////////////
#define DebugMode 1

// Delay to give you time for starting a logic analyzer
// (if you're into that kind of thing)
#define LogicAnalyzerDelay 1

// choose whether to compile code for the CDH redundant controllers
// or the COM encoding controller
// IMPORTANT: only one of these should be defined as 1.
// NOT BOTH OF THEM
#define CDH_PROCESSOR_COMPILE 0
#define COM_PROCESSOR_COMPILE 1

#if CDH_PROCESSOR_COMPILE
	#if COM_PROCESSOR_COMPILE
		#error Cannot compile for both processors - userConfig.h
	#endif
#else
	#undef COM_PROCESSOR_COMPILE
	#define COM_PROCESSOR_COMPILE 1
#endif

#if CDH_PROCESSOR_COMPILE

	//SUBSYSTEMS CONNECTED TO CDH
	#define COM_CONNECTED 0
	#define ADC_CONNECTED 0
	#define PWR_CONNECTED 0
	#define PLD1_CONNECTED 0
	#define PLD2_CONNECTED 0
	#define THM_CONNECTED 0
	#define STR_CONNECTED 0
	
#endif

// devices connected
#define RTC_CONNECTED 1
#define SD_CONNECTED 0

////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif /*USERCONFIG_H_*/
