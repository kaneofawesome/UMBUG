//////////////////////////////////////////////////////////////////
//                                                              //
//    TestSD source     		                                //
//    last edited by: Kane Anderson                             //
//    date: 09/16/2012		                                    //
//                                                              //
//////////////////////////////////////////////////////////////////

#include "./Test_SD.h"

///////////////////////////////////////////////////////////////////

#if SD_CONNECTED
	
	extern void sdCard_sendCommand(Byte cmd, long args, UI8 responseSize, SDCard* card);
	extern void SPI_WRITE(SPI_CHANNEL channel, Byte byte);
	
	//////////////////////////////////////////////////////////////

	void test_sdCard(void)
	{
		logLine("");
		logLine("Testing the SD card");
		disableInterrupts();
		
		#if DebugSD2
			logLine("    making sure SPI is initialized");
		#endif
		
		test_sdCard_initialization();
		test_sdCard_write_and_read();	

	}

	//////////////////////////////////////////////////////////////
	
	void test_sdCard_initialization(void)
	{
		#if DebugSD2
			logLine("    test SD card initialization");
		#endif
		
		// put MSP SPI settings in place
		setDigitalOutput(devices.sdCard.SPI.chipSelect.out);
		if (!initialize_SPI(&devices.sdCard.SPI))
		{
			logLine("    Could not initialize SPI\r\n");
			return;
		}
		
		clearSerialOutput(devices.sdCard.SPI.CLK.out);
			
		int i;
		
		// clear the buffers
		for (i = 0; i < SDCARD_BLOCK_SIZE; i++)
		{
			devices.sdCard.RX_blockBuffer[i] = 0;
			devices.sdCard.TX_blockBuffer[i] = 0;
		}
		
		/*
		setDigitalOutput(devices.sdCard.power);
		// short delay... card needs at least 1 ms
		for (i = 0; i < 10; i++)
		{
			
			setDigitalOutput(devices.sdCard.SPI.chipSelect);
			
		}
		*/
		
		#if DebugSD2
			logLine("        sending FF 10 times... card requires 74 clock cycles");
		#endif
		
		// Send 120 clocks, SD card require at least 74 clock cycles
		for(i = 0; i < 15; i++)
		{
			setDigitalOutput(devices.sdCard.power);
			SPI_WRITE(devices.sdCard.SPI.channel, 0xFF);
		}
		
		//CMD0 - Begin the initialization procedure
		#if DebugSD2
			logLine("        sending CMD0");
		#endif
		sdCard_sendCommand(CMD0, SD_EMPTY_ARGS, CMD0_R, &devices.sdCard);
		
		//CMD8 - Send the interface conditions, mandatory for SDHC cards
		#if DebugSD2
			logLine("        sending CMD8");
		#endif
		sdCard_sendCommand(CMD8, (SD_VS << 8) + SD_CHECK, CMD8_R, &devices.sdCard);
		
		//CMD59 to indicate that CRC is used for SD card
		#if DebugSD2
			logLine("        sending CMD59");
		#endif
		sdCard_sendCommand(CMD59, 1, CMD59_R, &devices.sdCard);
		// ignore illegal
		if(devices.sdCard.SPI.receiveMessage[0] & R1_ILLEGAL)
		{
			devices.sdCard.SPI.receiveMessage[0] &= ~R1_ILLEGAL;
		}
		
		//CMD55 indicate that the next command is an application specific command
    	//ACMD41 starts the internal initialization routine for SD card, 
    	//when its response is 0 then the init is done
		i = 0;
		do
		{
			#if DebugSD2
				logLine("        sending CMD55");
			#endif
			sdCard_sendCommand(CMD55, SD_EMPTY_ARGS, CMD55_R, &devices.sdCard);
			
			#if DebugSD2
				logLine("        sending ACMD41");
			#endif
			sdCard_sendCommand(ACMD41, 0x40000000, ACMD41_R, &devices.sdCard);

			i++;
		    SPI_receive(&devices.sdCard.SPI, false);
		}
		while( ((devices.sdCard.SPI.receiveMessage[0] & R1_IDLE) == R1_IDLE) && (i < SD_TIMEOUT) );
		
		assert(i < SD_TIMEOUT);
           
    
		//CMD58 read OCR, is used to check SD card accepted voltage level and initialization status
		//use this CMD to verify that the specific SD card is okay to use
		sdCard_sendCommand(CMD58, 1, CMD58_R, &devices.sdCard);
    	assert(!(devices.sdCard.SPI.receiveMessage[0] & R1_ERR));
    	
    	setDigitalOutput(devices.sdCard.SPI.chipSelect.out);
    	#if DebugSD2
			logLine("    SD initialization done");
			logLine("");
		#endif
		
		clearDigitalOutput(devices.sdCard.power);
		
	}
	
	/////////////////////////////////////////////////////
	
	void test_sdCard_write_and_read(void)
	{
		setDigitalOutput(devices.sdCard.SPI.chipSelect.out);
		initialize_SPI(&devices.sdCard.SPI);
		
		#if DebugSD2
			logLine("    test SD card write");
		#endif
		
		int i = 0;
		
		//generate test data
		for (i = 0; i < 10; i++)
		{
			devices.sdCard.TX_blockBuffer[i] = i%0xff;
		}
		
		#if DebugSD2
			// print to log
			printf("        data: ");
			for (i = 0; i < 10; i++)
			{
				if (i < 9) printf("%x, ", devices.sdCard.TX_blockBuffer[i]);
				else       printf("%x\r\n", devices.sdCard.TX_blockBuffer[i]);
			}
		#endif
		
		UI16 SD_Write_Location = 1;
		sdCard_write(SD_Write_Location, &devices.sdCard);
		
		#if DebugSD2
			logCombo("        data written to block", SD_Write_Location);
			logLine("    SD write done");
			logLine("");
		
			//
		
			logLine("    test SD card read");
		#endif
			
		sdCard_read(SD_Write_Location, &devices.sdCard);
		
		#if DebugSD2
			logCombo("        data was read from block", SD_Write_Location);
		
			// print to log
			printf("        data: ");
			for (i = 0; i < 10; i++)
			{
				if (i < 9) printf("%x, ", devices.sdCard.RX_blockBuffer[i]);
				else       printf("%x\r\n", devices.sdCard.RX_blockBuffer[i]);
			}
			
			logLine("    SD read done");
			logLine("");
		#endif
		
		for (i = 0; i < 10; i++)
		{
			//assert(devices.sdCard.RX_blockBuffer[i] == devices.sdCard.TX_blockBuffer[i]);
		}
		
		
	}

	
	
#endif
	
