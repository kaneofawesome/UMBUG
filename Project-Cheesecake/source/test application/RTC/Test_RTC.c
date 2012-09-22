//////////////////////////////////////////////////////////////////
//                                                              //
//    TestRTC source     		                                //
//    last edited by: Kane Anderson                             //
//    date: 09/16/2012		                                    //
//                                                              //
//////////////////////////////////////////////////////////////////

#include "./Test_RTC.h"

///////////////////////////////////////////////////////////////////

#if DebugMode

	#if RTC_CONNECTED
		
		extern void realTimeClock_unprotect(RealTimeClock* clock);
		
		void test_realTimeClock(void)
		{
			logLine("\r\ntesting real time clock");
			if (!initialize_SPI(&devices.realTimeClock.SPI))
			{
				logLine("    Could not initialize SPI\r\n");
				assert(false);
				return;
			}
			
			// each transaction with the rtc must be a burst of at least
			// 2 bytes.  The first byte, you tell it what address to use
			// in the following byte.
			// On a read, the second byte will come to you from rtc.
			// On a write, the second byte must be sent to the rtc.
			
		
			// Poll the status register
			realTimeClock_unprotect(&devices.realTimeClock);
			//printf("transmission: %x\r\n", (devices.realTimeClock.SPI.transmitMessage[0]));
			//printf("transmission: %x\r\n", (devices.realTimeClock.SPI.transmitMessage[1]));
			
			Byte toRTC[2];
			toRTC[0] = RTC_READ_CONTROL_REGISTER;
			toRTC[1] = EMPTY_CHAR;
			SPI_transmitStream(&devices.realTimeClock.SPI, toRTC, 2, true);
			//printf("transmission: %x\r\n", (devices.realTimeClock.SPI.transmitMessage[0]));
			//printf("transmission: %x\r\n", (devices.realTimeClock.SPI.transmitMessage[1]));
			
			// should have read the byte you just wrote (RTC_DISABLE_WRITE_PROTECT)
			//printf("read control register: %x\r\n", (devices.realTimeClock.SPI.receiveMessage[0]));
			//printf("read control register: %x\r\n\r\n", (devices.realTimeClock.SPI.receiveMessage[1]));
			assert(devices.realTimeClock.SPI.receiveMessage[1] == RTC_DISABLE_WRITE_PROTECT);
			logLine("    real time clock test write was successful");
			
			// test the time set function
			Time t;
			t.seconds	= 0x01;	// 
			t.minutes	= 0x37; // 
			t.hours		= 0x20; // 20:37:01
			t.day		= 0x05; // Friday
			t.date		= 0x03; // 3rd
			t.month		= 0x08; // August
			t.year		= 0x12; // 2012
			bool timeSetSuccessfully = realTimeClock_set(&devices.realTimeClock, &t);
			assert(timeSetSuccessfully);
			logLine("    real time clock successfully set to 8:37 August 3, 2012");
			
			fflush(stdout);
		
		}
		
		//////////////////////////////////////////////////////////////////////////////
		
		void test_BinaryCodedDecimal(void)
		{
			logLine("\r\nTesting conversion of binary coded decimal (BCD) numbers");
			
			BCD_Value result;
			
			int i;
			for (i = 0; i < 10; i++)
			{
				result = convertDecimalToBinaryCodedDecimal(i);
				assert(result == i);
			}
			
			result = convertDecimalToBinaryCodedDecimal(10);
			assert(result == 0x10);
			
			result = convertDecimalToBinaryCodedDecimal(12);
			assert(result == 0x12);
			
			result = convertDecimalToBinaryCodedDecimal(23);
			assert(result == 0x23);
			
			result = convertDecimalToBinaryCodedDecimal(33);
			assert(result == 0x33);
			
			result = convertDecimalToBinaryCodedDecimal(50);
			assert(result == 0x50);
			
			result = convertDecimalToBinaryCodedDecimal(62);
			assert(result == 0x62);
			
			result = convertDecimalToBinaryCodedDecimal(87);
			assert(result == 0x87);
			
			result = convertDecimalToBinaryCodedDecimal(99);
			assert(result == 0x99);
			
			result = convertDecimalToBinaryCodedDecimal(100);
			assert(result == 0x00);
			
			result = convertDecimalToBinaryCodedDecimal(159);
			assert(result == 0x00);
			
			result = convertDecimalToBinaryCodedDecimal(255);
			assert(result == 0x00);
			
			logLine("    BCD is OK");
			
		}
		
	#endif
	
#endif
