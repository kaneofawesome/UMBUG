//////////////////////////////////////////////////////////////////
//                                                              //
//    SDCard header                                        		//
//    last edited by: Kane Anderson                             //
//    date: April 06, 2012                                      //
//																//
//                                                              //
//////////////////////////////////////////////////////////////////

#ifndef SDCARD_H
#define SDCARD_H

#include "../DriversConfig.h"
#include "../devices/msp430/NickTianSPI/common.h"
#include "../devices/msp430/NickTianSPI/error_codes.h"
#include "../devices/msp430/NickTianSPI/crc.h"

// definitions
#define SDCARD_UNINITIALIZED 1
#define SDCARD_INITIALIZED 0
#define SDCARD_BLOCK_SIZE 512

// SD Card response sizes (in bytes)
#define R1				1
#define R2				2
#define R3				5
#define R7				5
#define MAX_R			5

// Meaning of R1
#define R1_ERR			0x7F	// R1 indicates an error if any bit is set
#define R1_IDLE			BIT0	// R1: card is initializing
#define R1_ERASE		BIT1	// R1: erase sequence reset
#define R1_ILLEGAL		BIT2	// R1: illegal command
#define R1_CRC			BIT3	// R1: comm CRC error
#define R1_ER_SEQ		BIT4	// R1: error in erase sequence
#define R1_ADD			BIT5	// R1: address error
#define R1_PARAM		BIT6	// R1: paramater error

// SD Card command set
#define CMD_LENGTH    	5
#define CMD0			0		// GO_IDLE_STATE
#define CMD0_R			R1
#define CMD1            1
#define CMD1_R          R1
#define CMD2            2
#define CMD2_R          R2
#define CMD8			8		// SEND_IF_COND
#define CMD8_R			R7
#define CMD9			9		// SEND_IF_COND
#define CMD9_R			R1
#define CMD13			13		// SEND_STATUS
#define CMD13_R			R2
#define CMD16			16		// SET_BLOCKLEN
#define CMD16_R			R1
#define CMD17			17		// READ_SINGLE_BLOCK
#define CMD17_R			R1
#define CMD18           18
#define CMD18_R         R1
#define CMD24			24		// WRITE_BLOCK
#define CMD24_R			R1
#define CMD55			55		// APP_CMD
#define CMD55_R			R1
#define CMD58			58		// READ_OCR
#define CMD58_R			R3
#define CMD59			59		// CRC_ON_OFF
#define CMD59_R			R1
#define ACMD41			41		// SD_SEND_OP_COND
#define ACMD41_R		R1

// SD Card CRC Polynomials
#define CRC7_POLY		0x09	// The polynomial used for the CRC7
#define CRC16_POLY		0x1021	// The polynomial used for the CRC16

#define CMD_BITS		0x40	// Used to set the proper bit in a command for tx
#define CMD_MASK		0x3F	// Used to make sure commands are only 6 bits long

#define TOK_START		0xFE	// Data start token
#define TOK_ERR_MASK	0xF0	// Used to find an error token
#define TOK_ERR_ECC		0x04	// Bit indicating an ECC error in the card
#define TOK_ERR_RANGE	0x08	// Bit indicating out of valid range

#define SD_BLOCK_POW	0x09	// 2^9 bytes per physical block
#define SD_CHECK		0xAA	// Use the recommended check pattern of 10101010b
#define SD_VS			0x01	// Voltage supply of 2.7v-3.3v

#define SD_V1			1		// Indicates the SD card is version 1.x
#define SD_V2			2		// Indicates the SD card is version 2.x

#define SD_TIMEOUT		TIMEOUT

#define SD_MAX_RESP_LENGTH      5

#define SD_EMPTY_ARGS	0

// struct //////////////////////////////////

typedef struct
{
	SPI_Device		SPI;
	DigitalOutput*	power;
	unsigned long	cardSize;
	unsigned char	status;
	
	Byte			RX_blockBuffer[SDCARD_BLOCK_SIZE];
	Byte			TX_blockBuffer[SDCARD_BLOCK_SIZE];
	
}
SDCard;

// external interface
void sdCard_initialize(SDCard* card);
void sdCard_read(long blockAddress, SDCard* card);
void sdCard_write(long blockAddress, SDCard* card);

#endif
