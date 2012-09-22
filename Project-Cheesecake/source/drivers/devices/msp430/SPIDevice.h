//////////////////////////////////////////////////////////////////
//                                                              //
//    SPIDevice header                                        	//
//    last edited by: Kane Anderson                             //
//    date: April 06, 2012                                      //
//                                                              //
//////////////////////////////////////////////////////////////////

#ifndef SPIDEVICE_H
#define SPIDEVICE_H

// includes ///////////////////////////////////

#include "../../DriversConfig.h"

// definitions ////////////////////////////////

#ifndef DUMMY_CHAR
#define DUMMY_CHAR 				0xFF
#endif
#ifndef EMPTY_CHAR
#define EMPTY_CHAR				0x00
#endif

typedef enum
{
	SPI_TYPE_Master				= 0,
	SPI_TYPE_Slave				= 1
}
SPI_TYPE;

typedef enum 
{
    SPI_CHANNEL_1				= 1,
    SPI_CHANNEL_2				= 2
}
SPI_CHANNEL;

#define SPI_TX_READY			(UC0IFG & UCB0TXIFG)
#define SPI_TX_DONE				(UCB0STAT & UCBUSY)
#define SPI_RX_READY			(UC0IFG & UCB0RXIFG)

#define SPI_RX_BUFFER_SIZE		16
#define SPI_TX_BUFFER_SIZE		16

#define SPI_TIME_BETWEEN_BYTES	256
#define SPI_BIT_RATE_REGISTER	0x04

// structures /////////////////////////////////

typedef struct
{
	SPI_TYPE					type;
	SPI_CHANNEL					channel;
		
	Byte						transmitMessage[SPI_TX_BUFFER_SIZE];
	Byte						receiveMessage[SPI_RX_BUFFER_SIZE];
	
	bool						activeHigh;
	
	Byte						controlRegister0;
	Byte						controlRegister1;
	Byte						bitRateRegister0;
	Byte						bitRateRegister1;
	
	// TODO use the above 4 bytes in the SPI initialization routine.
	
	union
	{
		DigitalOutput*			out;
		DigitalInput*			in;
	}
	chipSelect;
	
	union
	{
		SerialOutput*			out;
		SerialInput*			in;
	}
	CLK;
	
	union
	{
		SerialOutput*			out;
		SerialInput*			in;
	}
	MOSI;
	
	union
	{
		SerialOutput*			out;
		SerialInput*			in;
	}
	MISO;
	
}
SPI_Device;

// functions //////////////////////////////////

bool initialize_SPI(SPI_Device* device);		// returns true if OK
void SPI_transmit(SPI_Device* device, const Byte data, bool useChipSelect);
void SPI_transmitStream(SPI_Device* device, const Byte* data, UI8 length, bool useChipSelect);
void SPI_receive(SPI_Device* device, bool useChipSelect);

#endif


