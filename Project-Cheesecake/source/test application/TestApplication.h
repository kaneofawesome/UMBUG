//////////////////////////////////////////////////////////////////
//                                                              //
//    TestApplication header                                    //
//    last edited by: Kane Anderson                             //
//    date: November 22, 2011                                   //
//                                                              //
//////////////////////////////////////////////////////////////////

#ifndef TESTAPPLICATION_H
#define TESTAPPLICATION_H

//////////////////////////////////

#include "../system/System.h"
#include "../application/ApplicationConfig.h"
#include "../application/COM/Tone.h"
#include "../application/COM/PSK.h"
#include "../application/COM/PacketGrabber.h"
#include "../application/PWR/UART.h"
#include "../userConfig.h"
#include <assert.h>
#include <stdio.h>

void test_SPI(void);
void test_SPI_framework(void);
void test_SPI_framework_2(void);
void test_realTimeClock(void);
void test_analogToDigital(void);
void test_digitalToAnalog(void);
void test_thermocouple(void);
void test_sdCard(void);
void test_COMmain(void);
void test_radio(void);
void test_toneGenerator(void);
void test_PSK(void);
void test_packetGrabbing(void);

//////////////////////////////////

void test_application_initialize(void);
void test_application_main(void);
		
	#if DebugMode
		
		//////////////////////////////////
		
		#include "../system/System.h"
		#include "../application/ApplicationConfig.h"
		#include "../application/COM/Tone.h"
		#include "../application/COM/PSK.h"
		#include <assert.h>
		#include <stdio.h>
		
		void test_SPI(void);
		void test_SPI_framework(void);
		void test_SPI_framework_2(void);
		void test_analogToDigital(void);
		void test_digitalToAnalog(void);
		void test_thermocouple(void);
		
		#if RTC_CONNECTED
			#include "./RTC/Test_RTC.h"
		#endif
		
		#if SD_CONNECTED
			#include "./SD/Test_SD.h"
		#endif
		
		void test_COMmain(void);
		void test_radio(void);
		void test_toneGenerator(void);
		void test_PSK(void);
		void test_BinaryCodedDecimal(void);
		void test_NaturalLogarithm(void);
		
			//////////////////////////////////
	
	#endif

#endif
	
