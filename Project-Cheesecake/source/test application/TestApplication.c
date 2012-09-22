//////////////////////////////////////////////////////////////////
//                                                              //
//    TestApplication source                                    //
//    last edited by: Kane Anderson                             //
//    date: April 06, 2012                                      //
//                                                              //
//////////////////////////////////////////////////////////////////

#include "TestApplication.h"


//////////////////////////////////

void test_application_initialize(void)
{
	#if DebugMode
		
		#if SD_CONENCTED
			clearDigitalOutput(devices.sdCard.SPI.chipSelect.out);
		#endif
		
		#if LogicAnalyzerDelay
			printf("time to start logic analyzer... ");
			fflush(stdout);
			UL32 wait;
			UL32 dummy = 0;
			for (wait = 0; wait < 60000; wait++)
			{
				dummy++;
				if (dummy > 1000)
				{
					printf(".");
					dummy = 0;
					fflush(stdout);
				}
			}
			printf("done! starting test program\r\n");
			fflush(stdout);
		#endif
		
		// start printing to file
		#if CDH_PROCESSOR_COMPILE
			logLine("running test on CDH processor");
			logLine("please check UMSATS_CDH_log.txt");
		#else
			logLine("running test on COM processor");
			logLine("please check UMSATS_COM_log.txt");
		#endif
		initializeLogFile();
		
	#endif
}

void test_application_main(void)
{
	//test_SPI();
	//test_analogToDigital();

	//test_SPI_framework();
	//test_SPI_framework_2();
	//int i;
	//for (i = 0;i < 10000;i++)
	//{
	//	test_realTimeClock();
	//}
	//int i;
	//for (i = 0;i < 10000;i++)
	//{
		//test_sdCard();
	//}
	

	//test_COMmain();

	//test_thermocouple();
	
	//test_digitalToAnalog();
	//test_radio();
	//test_PSK();
	//test_toneGenerator();

	#if DebugMode
		
		#if RTC_CONNECTED
			test_realTimeClock();
			test_BinaryCodedDecimal();
		#endif
		
		#if SD_CONNECTED
			test_sdCard();
		#endif
	#endif

		//test_SPI_framework();
		//test_SPI_framework_2();
		//test_COMmain();
		//test_thermocouple();
		//test_digitalToAnalog();
		//test_radio();
		//test_PSK();
		//test_toneGenerator();

		//test_SPI();
		//test_analogToDigital();
	
	test_packetGrabbing();
	
	logLine("");
	logLine("All tests complete! --------------------");
	system_abort();
}

//////////////////////////////////////////////////////////////////


#if DebugMode
	
	//////////////////////////////////////////////////////////////////
	
	void test_SPI_framework(void)
	{
		#if CDH_PROCESSOR_COMPILE
			logLine("testing CDH SPI with framework");
			logLine("    transmitting: Kane is awesome **********");
			SPI_transmit(&devices.COM_Processor, 'K', true);
			SPI_transmit(&devices.COM_Processor, 'a', true);
			SPI_transmit(&devices.COM_Processor, 'n', true);
			SPI_transmit(&devices.COM_Processor, 'e', true);
			SPI_transmit(&devices.COM_Processor, ' ', true);
			SPI_transmit(&devices.COM_Processor, 'i', true);
			SPI_transmit(&devices.COM_Processor, 's', true);
			SPI_transmit(&devices.COM_Processor, ' ', true);
			SPI_transmit(&devices.COM_Processor, 'a', true);
			SPI_transmit(&devices.COM_Processor, 'w', true);
			SPI_transmit(&devices.COM_Processor, 'e', true);
			SPI_transmit(&devices.COM_Processor, 's', true);
			SPI_transmit(&devices.COM_Processor, 'o', true);
			SPI_transmit(&devices.COM_Processor, 'm', true);
			SPI_transmit(&devices.COM_Processor, 'e', true);
			SPI_transmit(&devices.COM_Processor, ' ', true);
		
			int i;
			for (i = 0; i < 10; i++)
			{
				SPI_transmit(&devices.COM_Processor, '*', true);
			}
			
			SPI_transmit(&devices.COM_Processor, '\r', true);
			SPI_transmit(&devices.COM_Processor, '\n', true);
			
		#else
			logLine("testing COM SPI with framework");
			int i;
			for (i = 0; i < 28; i++)
			{
				SPI_receive(&devices.CDH_Processor, true);
				char received = devices.CDH_Processor.receiveMessage[0];
				if (received != DUMMY_CHAR)
				{
					printf("%c", received);
				}
			}
			printf("\r\nfinished receiving\r\n");
			fflush(stdout);
		#endif
	}
	
	// test 2
	
	void test_SPI_framework_2(void)
	{
		#if CDH_PROCESSOR_COMPILE
			logLine("testing CDH SPI with framework (2)");
			logLine("    transmitting: pwnage<-");
			logLine("    with one TX");
			Byte array[8] = {'p','w','n','a','g','e','<','-'};
			SPI_transmitStream(&devices.COM_Processor, array, 8, true);
			
			SPI_transmit(&devices.COM_Processor, '\r', true);
			SPI_transmit(&devices.COM_Processor, '\n', true);
		
		#else
			logLine("testing COM SPI with framework (2)");
			int i;
			for (i = 0; i < 10; i++)
			{
				SPI_receive(&devices.CDH_Processor, true);
				char received = devices.CDH_Processor.receiveMessage[0];
				if (received != DUMMY_CHAR)
				{
					printf("%c", received);
				}
			}
			printf("\r\nfinished receiving\r\n");
			fflush(stdout);
		#endif
	}
	
	//////////////////////////////////////////////////////////////////
	
	void test_SPI(void)
	{
		logLine("testing SPI");
		
		P5DIR |= BIT1;                // P5.1 as output
	  	P5OUT |= BIT1;                // P5.1 set high
	
		// testing SPI
	
		#if CDH_PROCESSOR_COMPILE
		
			// TODO uncomment and test
			/*
		
			P3OUT &= ~0x01;		// slave enable
			
			char nextCharToSend = '1';
			for(;;nextCharToSend++)
			{
	
				UCB0CTL1 |= UCSWRST;
				UCB0CTL1 &= ~UCSWRST;
				if (nextCharToSend == ':') nextCharToSend = '1';
				
				P3OUT &= ~0x01;  // set STE low for slave enable
				char buff = spiSendByte(nextCharToSend);
				printf("recieved: %c\n", buff);
				
				P3OUT |= 0x01; // set STE high for slave disable
				
				// just a time killing loop
				int waitTimer;
				for (waitTimer = 10000; waitTimer > 0; waitTimer--){ ; }
		
			}
			*/
		#else		// SLAVE
			// TODO uncomment
			/*
			printf("    COM Slave Initialize\r\n");
			printf("Searching for: %c\n", 'C');
			fflush(stdout);
			
		  int x;
		  for(x =0;x<100;x++)
		  {
	
			UCB0CTL1 |= UCSWRST;
			UCB0CTL1 &= ~UCSWRST;
		  	UCB0TXBUF = 'C';
			while((P3IN & 0x01) == 0x01);	// wait for enable
			bool enabled = ((P3IN | 0xFE) == 0xFE);
			if (enabled)
			{
				char buff = UCB0RXBUF;
				printf("recieved: %c\n", buff);
				
			}
			
		  }
		  */
		#endif
		
	}
	
	///////////////////////////////////////////////////////////////////
	
	void test_analogToDigital(void)
	{
		// TODO
		logLine("testing A to D conversion");
	}
	
	void test_thermocouple(void)
	{
		/*
		logLine("Testing thermocouple");
		Word raw;
		for (;;)
		{
			raw = thermocouple_read(&devices.testThermocouple);
			logCombo("raw voltage: ", raw);
		}
		*/
	}
	
	///////////////////////////////////////////////////////////////////
	
	void test_digitalToAnalog(void)
	{
		logLine("testing D to A conversion");
		
		int D2A_tests;
		for (D2A_tests = 0; D2A_tests < 10; D2A_tests++)
		{ 
			int i;
			for (i = 0; i < 0xFFF; i++)
			{
				#if COM_PROCESSOR_COMPILE
				
					devices.radio.microphone->value = i;
					startNewDigitalToAnalogConversion(devices.radio.microphone->value);
					
				#endif
			}
		}
	}
	
	//////////////////////////////////////////////////////////////
	
	void test_radio(void)
	{
		#if COM_PROCESSOR_COMPILE
			logLine("testing output to radio");
			
			// 500 mV / 3.3 V = 620 / 4096
			#define radio_high 620
			#define radio_low 0
			
			bool toggle = low;
			
			for (;;)
			{
				toggle = toggle ? low : high;
				devices.radio.microphone->value = toggle ? radio_high : radio_low;
				startNewDigitalToAnalogConversion(devices.radio.microphone->value);
				int i;
				for (i = 0; i < 12000; i++) ; // wait
			}
			
			#undef radio_high
			#undef radio_low
		#endif
	}

	
	///////////////////////////////////////////////////////////////////
	
	void test_COMmain(void)
	{
		#if COM_PROCESSOR_COMPILE
		
		//nvm im just gonna put this straight into  a real com main
		
		#endif
	}
	
	///////////////////////////////////////////////////////////////////
	
	void test_toneGenerator(void)
	{
		enableInterrupts();
		
		#if COM_PROCESSOR_COMPILE
			for (;;)
			{
				//startNewDigitalToAnalogConversion(devices.radio.microphone->value);
				
				//UI16 wait;
				//for (wait = 6000; wait --> 0;) { }
			}
		#endif
	}
	
	///////////////////////////////////////////////////////////////////
	
	void test_PSK(void)
	{
		logLine("Testing PSK");
		
		disableInterrupts();
	
		Byte data[8];
		data[0] = 0xFF;
		data[1] = 0xFF;
		data[2] = 0xA1;
		data[3] = 0x2C;
		data[4] = 0xB6;
		data[5] = 0x10;
		data[6] = 0x00;
		data[7] = 0x89;
		
		printf("data: ");
		int i;
		for(i = 0; i < 8; i++)
		{
			printf(" %x\t", data[i]);
		}
		fflush(stdout);
		
		convertBinaryToPSK(data,8);
		
		printf("\n\nPhase Shift History: ");
		for(i = 0; i < PhaseShiftHistoryLength; i++)
		{
			printf("%d, ", phaseShifts[i]);
		}
		printf("\n");
    //
	///convertBinaryToPSK(data,32); // TODO: leftover from merge. Should it be here?
		
		enableInterrupts();
}

///////////////////////////////////////////////////////////////////


void test_packetGrabbing(void)
{
	int i;
	for(i=0;i<8;i++)
	{
		UI16 big = 0x7E55>>i;
		UI8 one = (UI8)(big>>8);
		UI8 two = (UI8)(big);
		unsigned int pos = findAX25Flag(one, two, 0, 8);
		
		printf("found at %d\n", pos);
		fflush(stdout);
	}


	masterInputBuffer[0] = 0x55;
	masterInputBuffer[1] = 0x3E;
	masterInputBuffer[2] = 0x34;
	masterInputBuffer[3] = 0x56;
	masterInputBuffer[4] = 0x34;
	masterInputBuffer[5] = 0x34;
	masterInputBuffer[6] = 0x34;
	masterInputBuffer[7] = 0x34;
	masterInputBuffer[8] = 0x56;
	masterInputBuffer[9] = 0x7E;
	masterInputBuffer[10] = 0x34;
	masterInputBuffer[11] = 0x0E;
	masterInputBuffer[12] = 0x56;
	masterInputBuffer[13] = 0x34;
	
	ptrRead = 0;
	ptrWrite = 13;
	
	printf("byte0 = %x \n", masterInputBuffer[0]);
	printf("byte1 = %x \n", masterInputBuffer[1]);
	printf("byte2 = %x \n", masterInputBuffer[2]);	
	
	//findPacket(0);
	
	UI8 possiblePacket[3];
	removeBitStuffing(0, 0, 2, 1, possiblePacket);

	for(i=0;i<3;i++)
	{
		printf("%x ", possiblePacket[i]);
	}
	
	fflush(stdout);
	
	const UI8 stageTwoHandShake[] = {0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 52,
	 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF};
	 printf("\n");
	convertBinaryToPSK((Byte *)stageTwoHandShake,64);
	for(i=0;i<40;i++)
	{
		
		printf("0x%x, ", phaseShifts[i]);
	}
	
	enableInterrupts();
	for(;;){;}
}

///////////////////////////////////////////////////////////////////
	
	// put other tests here


#endif
