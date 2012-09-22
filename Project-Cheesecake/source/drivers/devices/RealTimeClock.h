//////////////////////////////////////////////////////////////////
//                                                              //
//    Real time clock header                                  	//
//    last edited by: Kane Anderson                             //
//    date: January 10, 2012                                    //
//                                                              //
//////////////////////////////////////////////////////////////////

#ifndef REALTIMECLOCK_H
#define REALTIMECLOCK_H

#include "../DriversConfig.h"
#include "../../system/BinaryCodedDecimal.h"

// address space (for DS1306) /////////////////

// read

#define RTC_READ_SECONDS				0x00
#define RTC_READ_MINUTES				0x01
#define RTC_READ_HOURS					0x02
#define RTC_READ_DAY					0x03
#define RTC_READ_DATE					0x04
#define RTC_READ_MONTH					0x05
#define RTC_READ_YEAR					0x06

#define RTC_READ_ALARM0_SECONDS			0x07
#define RTC_READ_ALARM0_MINUTES			0x08
#define RTC_READ_ALARM0_HOURS			0x09
#define RTC_READ_ALARM0_DAY				0x0A

#define RTC_READ_ALARM1_SECONDS			0x0B
#define RTC_READ_ALARM1_MINUTES			0x0C
#define RTC_READ_ALARM1_HOURS			0x0D
#define RTC_READ_ALARM1_DAY				0x0E

#define RTC_READ_CONTROL_REGISTER		0x0F
#define RTC_READ_STATUS_REGISTER		0x10
#define RTC_READ_TRICKLE_CHARGER		0x11
#define RTC_DISABLE_WRITE_PROTECT		0x04

#define RTC_READ_USER_RAM_FIRST_BYTE	0x20
#define RTC_READ_USER_RAM_LAST_BYTE		0x7F
#define RTC_READ_USER_RAM_BYTE_SIZE		96

// write

#define RTC_WRITE_SECONDS				0x80
#define RTC_WRITE_MINUTES				0x81
#define RTC_WRITE_HOURS					0x82
#define RTC_WRITE_DAY					0x83
#define RTC_WRITE_DATE					0x84
#define RTC_WRITE_MONTH					0x85
#define RTC_WRITE_YEAR					0x86

#define RTC_WRITE_ALARM0_SECONDS		0x87
#define RTC_WRITE_ALARM0_MINUTES		0x88
#define RTC_WRITE_ALARM0_HOURS			0x89
#define RTC_WRITE_ALARM0_DAY			0x8A

#define RTC_WRITE_ALARM1_SECONDS		0x8B
#define RTC_WRITE_ALARM1_MINUTES		0x8C
#define RTC_WRITE_ALARM1_HOURS			0x8D
#define RTC_WRITE_ALARM1_DAY			0x8E

#define RTC_WRITE_CONTROL_REGISTER		0x8F
#define RTC_WRITE_STATUS_REGISTER		0x90
#define RTC_WRITE_TRICKLE_CHARGER		0x91

#define RTC_WRITE_USER_RAM_FIRST_BYTE	0xA0
#define RTC_WRITE_USER_RAM_LAST_BYTE	0xFF

// structure //////////////////////////////////
typedef struct
{
	SPI_Device SPI;
	
	Time currentTime;
	
	Time alarm0;
	Time alarm1;
	
}
RealTimeClock;

// functions //////////////////////////////////

void realTimeClock_initialize(RealTimeClock* clock);
void realTimeClock_update(RealTimeClock* clock);
void realTimeClock_reset(RealTimeClock* clock);
bool realTimeClock_set(RealTimeClock* clock, Time* t);

#endif
