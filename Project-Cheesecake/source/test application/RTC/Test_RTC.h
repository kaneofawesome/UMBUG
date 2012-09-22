//////////////////////////////////////////////////////////////////
//                                                              //
//    TestRTC header     		                                //
//    last edited by: Kane Anderson                             //
//    date: 09/16/2012		                                    //
//                                                              //
//////////////////////////////////////////////////////////////////

#ifndef TESTRTC_H
#define TESTRTC_H

#include "../../userConfig.h"

	#if DebugMode
		
		#if RTC_CONNECTED
			
			#include "../../system/System.h"
			#include <assert.h>
			#include <stdio.h>
		
			void test_realTimeClock(void);
			void test_BinaryCodedDecimal(void);
			
		#endif
		
	#endif

#endif

