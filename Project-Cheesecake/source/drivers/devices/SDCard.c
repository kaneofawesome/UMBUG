//////////////////////////////////////////////////////////////////
//                                                              //
//    SDCard source                                        		//
//    last edited by: Kane Anderson                             //
//    date: April 06, 2012                                      //
//                                                              //
//////////////////////////////////////////////////////////////////

#include "SDCard.h"

#if DebugSD1
	#include "Log.h"
#endif

// functions

void sdCard_sendCommand(Byte cmd, long args, UI8 responseSize, SDCard* card)
{
	#if DebugSD1
		printf("            CMD: 0x%x\r\n", cmd);
		printf("            args: 0x%x\r\n", args);
		logCombo("            expected response size", responseSize);
	#endif
	
	int i = 0;
	char crc;
	Byte command[SD_MAX_RESP_LENGTH+1];
	Byte response[SD_MAX_RESP_LENGTH+1];

	// Set the transmission bit in the command byte
	command[0] = (cmd & CMD_MASK) | CMD_BITS;
	// Load the argument bytes into the array
	command[1] = args >> 24;
	command[2] = args >> 16;
	command[3] = args >> 8;
	command[4] = args;

	// Generate the CRC and set the end bit
    crc = (make_crc7(&command[0], CMD_LENGTH, CRC7_POLY) << 1) | BIT0;
    
	command[5] = crc;
    
    #if DebugSD1
    	printf("            CRC: 0x%x\r\n", command[5]);
    #endif
      
	// Send the command and the first arguments and the CRC
	
	#if DebugSD1
		logLine("            tx command...");
		printf("                0x%x\r\n", command[0]);
		printf("                0x%x\r\n", command[1]);
		printf("                0x%x\r\n", command[2]);
		printf("                0x%x\r\n", command[3]);
		printf("                0x%x\r\n", command[4]);
		printf("                0x%x\r\n", command[5]);
	#endif
	
	// Assert CS before issuing any commands
	clearDigitalOutput(card->SPI.chipSelect.out);
	SPI_transmitStream(&card->SPI, command, SD_MAX_RESP_LENGTH+1, false);
    
    #if DebugSD1
    	logLine("            tx done");
    #endif
    
    i = 0;
	// Receive bytes until the first bit of an incoming byte is 0
	do
	{
		SPI_receive(&card->SPI, false);
        i++;
	}
	while( ((card->SPI.receiveMessage[0] & BIT7) == BIT7) && (i < SD_TIMEOUT));

	// If there was a time out, then just leave
	if(i >= SD_TIMEOUT)
	{
		#if DebugSD1
			logLine("        *** SD card had SPI timeout! ***");
			printf("            it happened during CMD%x\r\n", cmd);
			fflush(stdout);
		#endif
		return;
	}
	else
	{
		#if DebugSD1
			logLine("            getting response...");
		#endif
		
		// copy first part of response
		response[0] = card->SPI.receiveMessage[0];
		
		if (responseSize > 1)
		{
			// receive the appropriate number of additional bytes for the response
			// starting at 1 because the first byte was already received above
			for (i = 1; i < responseSize; i++)
			{
				SPI_receive(&card->SPI, false);
				response[i] = card->SPI.receiveMessage[0];
			}
		}
		
		// receive the CRC in the last byte
		SPI_receive(&card->SPI, false);
		response[SD_MAX_RESP_LENGTH] = card->SPI.receiveMessage[0];
	
	}
	
	
	for (i = 0; i < responseSize+1; i++)
	{
		card->SPI.receiveMessage[i] = response[i];
	} 
		
	#if DebugSD1
		for (i = 0; i < responseSize+1; i++)
		{
			printf("                0x%x\r\n", card->SPI.receiveMessage[i]);
		}
		printf("        done sending CMD%d\r\n", cmd);
	#endif
}

/////////////////////////////////////////////

void sdCard_initialize(SDCard* card)
{
	int i;
	
	initialize_SPI(&card->SPI);
	
	// clear the buffers
	for (i = 0; i < SDCARD_BLOCK_SIZE; i++)
	{
		card->RX_blockBuffer[i] = 0;
		card->TX_blockBuffer[i] = 0;
	}
	
	setDigitalOutput(card->SPI.chipSelect.out);

	// Send 80 clocks, SD card require at least 74 clock cycles
	for(i = 0; i < 10; i++)
	{
		SPI_transmit(&card->SPI, 0xFF, false);
	}
    // Assert CS before issuing any commands
	clearDigitalOutput(card->SPI.chipSelect.out);
	
	//CMD0 - Begin the initialization procedure
	sdCard_sendCommand(CMD0, SD_EMPTY_ARGS, CMD0_R, card);
	
	//CMD8 - Send the interface conditions, mandatory for SDHC cards
	sdCard_sendCommand(CMD8, (SD_VS << 8) + SD_CHECK, CMD8_R, card);
	
	//CMD59 to indicate that CRC is used for SD card
	sdCard_sendCommand(CMD59, 1, CMD59_R, card);
	// ignore illegal
	if(card->SPI.receiveMessage[0] & R1_ILLEGAL)
	{
		card->SPI.receiveMessage[0] &= ~R1_ILLEGAL;
	}
	
	//CMD55 indicate that the next command is an application specific command
	//ACMD41 starts the internal initialization routine for SD card, 
	//when its response is 0 then the init is done
	i = 0;
	do
	{
		sdCard_sendCommand(CMD55, SD_EMPTY_ARGS, CMD55_R, card);
		sdCard_sendCommand(ACMD41, 0x40000000, ACMD41_R, card);

		i++;
	    SPI_receive(&card->SPI, false);
	}
	while( ((card->SPI.receiveMessage[0] & R1_IDLE) == R1_IDLE) && (i < SD_TIMEOUT) );
	
	setDigitalOutput(card->SPI.chipSelect.out);

}


/**
 * Reads a block of data from the SD card. Status of read can be
 * checked through sd_check_status()
 *
 * IN:  block_addr - the address to read from (max depends on the card)
 *      card - what SD card to read (in case of multiples)
 * OUT: none
 **/
void sdCard_read(long blockAddress, SDCard* card)
{
	int i;
    unsigned int crc = 0, crc_check = 0;
     
    clearDigitalOutput(card->SPI.chipSelect.out);
        
    //CMD17, read a block
    // block_addr goes 0x01, 0x02, 0x03 ...
    sdCard_sendCommand(CMD17, blockAddress, CMD17_R, card);

	// Wait for the start (or error) token
	i = 0;
	do
	{
		SPI_receive(&card->SPI, false);
		i++;
	}
	while((card->SPI.receiveMessage[0] == 0xFF) & (i < SD_TIMEOUT));
	
	if(i >= SD_TIMEOUT)
	{
		setDigitalOutput(card->SPI.chipSelect.out);
		#if DebugSD1
			printf("        *** SD card timed out in receive method ***\r\n");
			fflush(stdout);
		#endif
		return;
	}        
        
	// Check the token received
    if(card->SPI.receiveMessage[0] == TOK_START)
	{
		#if DebugSD1
			printf("        SD start token received\r\n");
			fflush(stdout);
		#endif
		
		for(i = 0; i < SDCARD_BLOCK_SIZE; i++)
		{
			SPI_receive(&card->SPI, false);
			card->RX_blockBuffer[i] = card->SPI.receiveMessage[0];
	    }

		// for commands the CRC is only one byte
		// but for data, the CRC is two bytes
		SPI_receive(&card->SPI, false);
		crc = card->SPI.receiveMessage[0] << 8;
		SPI_receive(&card->SPI, false);
		crc |= card->SPI.receiveMessage[0];
		
		crc_check = make_crc16_sd(card->RX_blockBuffer, SDCARD_BLOCK_SIZE, CRC16_POLY);
		//printf("crc read: %d %d\n", crc_check, crc);
		#if DebugSD1
			printf("        CRC: %x, %x\r\n", crc, crc_check);
			fflush(stdout);
		#endif
		
		if (crc != crc_check)
		{
			#if DebugSD1
				printf("        *** CRC did not match in SD receive method ***\r\n");
				fflush(stdout);
			#endif
		}           
	}
	else if( (card->SPI.receiveMessage[0] & TOK_ERR_MASK) == 0)
	{
		#if DebugSD1
			printf("        read failed! got token error!\r\n");
			printf("        response: %x\r\n", card->SPI.receiveMessage[0]);
			fflush(stdout);
			// Check for errors indicated in the token
			if(card->SPI.receiveMessage[0] & TOK_ERR_ECC)
			{
				UI16 error = MODULE_SD + ERR_ECC;
				printf("            error: ECC %x\r\n", error);
				fflush(stdout);
			}
			else if(card->SPI.receiveMessage[0] & TOK_ERR_RANGE)
			{
				UI16 error = MODULE_SD + ERR_ADDR;
				printf("            error: ADDR %x\r\n", error);
				fflush(stdout);
			}
			else
			{
				UI16 error = MODULE_SD + ERR_OTHER;
				printf("            error: OTHER %x\r\n", error);
				fflush(stdout);
			}
		#endif
	}
	else
	{
        // did not receive anything we can interperet
        #if DebugSD1
        	printf("        read failed!  unintelligible response\r\n");
        	fflush(stdout);
        #endif
	}      
        
	setDigitalOutput(card->SPI.chipSelect.out);
}

/**
 * Writes a block of data to the SD card.  Status of write can be
 * checked through sd_check_status()
 *
 * IN:	block_addr - the address to write to
 * 		card - the card to write to
 * OUT:	int - error code (FALSE if no error)
 **/


void sdCard_write(long blockAddress, SDCard* card)
{
	char crc = 0;
	UI16 i = 0;
	unsigned int crc_check = 0;

	clearDigitalOutput(card->SPI.chipSelect.out);

	// Send CMD24
	sdCard_sendCommand(CMD24, blockAddress, CMD24_R, card);
	
	SPI_transmit(&card->SPI, TOK_START, false);	// this is the start token

    for(i = 0; i < SDCARD_BLOCK_SIZE; i++)
    {
    	SPI_transmit(&card->SPI, card->TX_blockBuffer[i], false);
    }
    
    // 2byte CRC
    crc_check = make_crc16_sd(card->TX_blockBuffer, SDCARD_BLOCK_SIZE, CRC16_POLY);
    crc = crc_check >> 8;
    SPI_transmit(&card->SPI, crc, false);
    crc = crc_check;
    SPI_transmit(&card->SPI, crc, false);
    
    SPI_receive(&card->SPI, false);
    
    if ((card->SPI.receiveMessage[0] & 0x1F) != 0x05)
    {
    	#if DebugSD1
		    if ((card->SPI.receiveMessage[0] & 0x1F) != 0x05)
		    {
				printf("        write to sd card FAILED\r\n");
				printf("            response: %x\r\n", card->SPI.receiveMessage[0]);
				printf("            needed: (%x & 0x1F) == 0x05\r\n", card->SPI.receiveMessage[0]);
				fflush(stdout);
		    }
		#endif
    }
    
	do
    {
    	SPI_receive(&card->SPI, false);
    	i++;
    }
    while (card->SPI.receiveMessage[0] != 0xff & i < SD_TIMEOUT);
    
    setDigitalOutput(card->SPI.chipSelect.out);
    
}



