//////////////////////////////////////////////////////////////////
//                                                              //
//    Real time clock source                                  	//
//    last edited by: Kane Anderson                             //
//    date: January 4, 2012                                     //
//                                                              //
//////////////////////////////////////////////////////////////////

#include "RealTimeClock.h"

// private function... not in header //////////

// enables writing
void realTimeClock_unprotect(RealTimeClock* clock)
{
	Byte toRTC[2] = {RTC_WRITE_CONTROL_REGISTER, RTC_DISABLE_WRITE_PROTECT};
	SPI_transmitStream(&clock->SPI, toRTC, 2, true);
}

// functions //////////////////////////////////

void realTimeClock_initialize(RealTimeClock* clock)
{
	realTimeClock_reset(clock);
	initialize_SPI(&clock->SPI);
	realTimeClock_unprotect(clock);
	realTimeClock_set(clock, &clock->currentTime);
}

void realTimeClock_update(RealTimeClock* clock)
{
	// read the time
	Byte fromRTC[8] =  {	DUMMY_CHAR, DUMMY_CHAR, DUMMY_CHAR, DUMMY_CHAR,
		  					DUMMY_CHAR, DUMMY_CHAR, DUMMY_CHAR, DUMMY_CHAR	};
	fromRTC[0] = RTC_READ_SECONDS;
	SPI_transmitStream(&clock->SPI, fromRTC, 8, true);
	
	// copy in
	clock->currentTime.seconds	= clock->SPI.receiveMessage[1];
	clock->currentTime.minutes	= clock->SPI.receiveMessage[2];
	clock->currentTime.hours	= clock->SPI.receiveMessage[3];
	clock->currentTime.day		= clock->SPI.receiveMessage[4];
	clock->currentTime.date		= clock->SPI.receiveMessage[5];
	clock->currentTime.month	= clock->SPI.receiveMessage[6];
	clock->currentTime.year		= clock->SPI.receiveMessage[7];
}

void realTimeClock_reset(RealTimeClock* clock)
{
	clock->currentTime.seconds	= 0;
	clock->currentTime.minutes	= 0;
	clock->currentTime.hours	= 0;
	clock->currentTime.day		= BCD_SUNDAY;
	clock->currentTime.date		= 0x01;
	clock->currentTime.month	= 0x01;
	clock->currentTime.year		= 0x12;
	
	clock->alarm0 = clock->currentTime;
	clock->alarm1 = clock->currentTime;
	
}


// returns whether the operation was successful
bool realTimeClock_set(RealTimeClock* clock, Time* t)
{
	// first send the new data
	Byte toRTC[8];
	toRTC[0] = RTC_WRITE_SECONDS;	// initial write location
	toRTC[1] = t->seconds;
	toRTC[2] = t->minutes;
	toRTC[3] = t->hours;
	toRTC[4] = t->day;
	toRTC[5] = t->date;
	toRTC[6] = t->month;
	toRTC[7] = t->year;
	SPI_transmitStream(&clock->SPI, toRTC, 8, true);
	
	// then read it back
	Byte fromRTC[8] =  {	DUMMY_CHAR, DUMMY_CHAR, DUMMY_CHAR, DUMMY_CHAR,
		  					DUMMY_CHAR, DUMMY_CHAR, DUMMY_CHAR, DUMMY_CHAR	};
	fromRTC[0] = RTC_READ_SECONDS;
	SPI_transmitStream(&clock->SPI, fromRTC, 8, true);
	
	// compare (exclude seconds)
	if (	t->minutes	== clock->SPI.receiveMessage[2] &&
			t->hours	== clock->SPI.receiveMessage[3] &&
			t->day		== clock->SPI.receiveMessage[4] &&
			t->date		== clock->SPI.receiveMessage[5] &&
			t->month	== clock->SPI.receiveMessage[6] &&
			t->year		== clock->SPI.receiveMessage[7]
		)
	{
		// copy in
		clock->currentTime.seconds	= clock->SPI.receiveMessage[1];
		clock->currentTime.minutes	= clock->SPI.receiveMessage[2];
		clock->currentTime.hours	= clock->SPI.receiveMessage[3];
		clock->currentTime.day		= clock->SPI.receiveMessage[4];
		clock->currentTime.date		= clock->SPI.receiveMessage[5];
		clock->currentTime.month	= clock->SPI.receiveMessage[6];
		clock->currentTime.year		= clock->SPI.receiveMessage[7];
		
		return true;
	}
	
	return false;
}




