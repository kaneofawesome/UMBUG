//////////////////////////////////////////////////////////////////
//                                                              //
//    TestSD header     		                                //
//    last edited by: Kane Anderson                             //
//    date: 09/16/2012		                                    //
//                                                              //
//////////////////////////////////////////////////////////////////

#ifndef TESTSD_H
#define TESTSD_H

#define DebugSD1 0
#define DebugSD2 0

#include "../../userConfig.h"

	#if DebugMode
		
		#if SD_CONNECTED
			
			#include "../../system/System.h"
			#include <assert.h>
			#include <stdio.h>
		
			void test_sdCard_initialization(void);
			void test_sdCard_write_and_read(void);
			void test_sdCard(void);
	
		#endif
		
	#endif

#endif


