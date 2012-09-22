//////////////////////////////////////////////////////////////////
//                                                              //
//    SPIDevice source                                        	//
//    last edited by: Kane Anderson                             //
//    date: April 06, 2012                                      //
//                                                              //
//////////////////////////////////////////////////////////////////

//I am using the 'B0' USCI module

#include "SPIDevice.h"
#include <stdio.h>

// functions //////////////////////////////////

/* initialize_SPI
 * returns whether or not this was successful
 * 
 * lots of comments on how it works start... now
 *
 *	CONTROL REGISTERS
 *  =================
 *	UCB0CTL0 : Control Register 0
 * ---------------------------------------------------------------
 * |    7   |    6   |   5   |    4   |   3   |   2   1   |    0   | 
 * | UCCKPH | UCCKPL | UCMSB | UC7BIT | UCMST |  UCMODEx  | UCSYNC |
 * ---------------------------------------------------------------
 * UCCKPH (Clock phase)              = 0b  ->  Data is changed on the first UCLK edge and captured on the following edge.
 * UCCKPL (Clock polarity)           = 0b  ->  The inactive state is low
 * UCMSB (MSB first select)          = 1b  ->  MSB first
 * UC7BIT (Character length)         = 0b  ->  8-bit data
 * UCMST (Master mode)               = 1b  ->  Master mode
 * UCMODEx (USCI mode)               = 00b ->  3-Pin SPI
 * UCSYNC (Synchronous mode enable)  = 1b  ->  Synchronous mode
 * 
 * 
 * UCA0CTL1 : Control Register 1
 * ------------------------------------------------------------------
 * |   7    6     |   5       4       3      2            |    0    |
 * |   UCSSELx    |                  Unused               | UCSWRST |
 * ------------------------------------------------------------------
 * UCSSELx (USCI clock source select)= 10b ->  SMCLK
 * UCSWRST (Software reset)          = 1b  ->  normally set by a PUC
 * 
 * 
 * 
 * UCB0BR0, UCB0BR1 : DATA RATE
 * Data rate = SMCLK/2 ~= 500kHz
 * 
 * 
 */
bool initialize_SPI(SPI_Device* device)
{
	
	if (device->type == SPI_TYPE_Master)
	{
		if (device->activeHigh) clearDigitalOutput(device->chipSelect.out);
		else setDigitalOutput(device->chipSelect.out);
	}
	
	volatile Byte* control_0	= NULL;
	volatile Byte* control_1	= NULL;
	volatile Byte* rate_0		= NULL;
	volatile Byte* rate_1		= NULL;
	volatile Byte* port_sel		= NULL;
	volatile Byte* port_dir		= NULL;
	
	if (device->channel == SPI_CHANNEL_1)
	{
		control_0	= &(UCB0CTL0);
		control_1	= &(UCB0CTL1);
		rate_0		= &(UCB0BR0);
		rate_1		= &(UCB0BR1);
		port_sel	= &(P3SEL);
		port_dir	= &(P3DIR); 
	}
	else if (device->channel == SPI_CHANNEL_2)
	{
		control_0	= &(UCA0CTL0);
		control_1	= &(UCA0CTL1);
		rate_0		= &(UCA0BR0);
		rate_1		= &(UCA0BR1);
		port_sel	= &(P7SEL);
		port_dir	= &(P7DIR);
	}
	else
	{
		return false;
	}
	
	(*control_1)	|= UCSWRST;
	(*control_0)	 = device->controlRegister0;
	(*control_1)	 = device->controlRegister1;
	(*rate_0)		 = device->bitRateRegister0;
	(*rate_1)		 = device->bitRateRegister1;
	(*port_sel)		|= 0x0E;
	(*port_dir)		|= 0x01;
	(*port_sel)		&= ~0x01;
	(*port_dir)		&= ~0x10;
	
	return true;

}

///////////////////////////////////////////////

// Utility functions

void SPI_reset(SPI_CHANNEL channel)
{
	switch (channel)
	{
		case SPI_CHANNEL_1:	UCB0CTL1 |= UCSWRST; UCB0CTL1 &= ~UCSWRST; break;
		case SPI_CHANNEL_2:	UCA0CTL1 |= UCSWRST; UCA0CTL1 &= ~UCSWRST; break;
		default			  :	return;
	}
}

void SPI_slaveDisable(SPI_CHANNEL channel)
{
	switch (channel)
	{
		case SPI_CHANNEL_1:	P3OUT |= 0x01; break;					// set STE high for slave disable
		case SPI_CHANNEL_2:	P7OUT |= 0x01; break;					// set STE high for slave disable
		default			  :	return;
	}
}

void SPI_slaveEnable(SPI_CHANNEL channel)
{
	switch (channel)
	{
		case SPI_CHANNEL_1:	P3OUT &= ~0x01; break;					// set STE low for slave enable
		case SPI_CHANNEL_2:	P7OUT &= ~0x01; break;					// set STE low for slave enable
		default			  :	return;
	}
}

void SPI_clearInterruptFlag(SPI_CHANNEL channel)
{
	switch (channel)
	{
		case SPI_CHANNEL_1:	IFG2 &= ~UCB0RXIFG; break;
		case SPI_CHANNEL_2:	IFG2 &= ~UCA0RXIFG; break;
		default			  :	return;
	}
}

void SPI_WRITE(SPI_CHANNEL channel, Byte byte)
{
	int timeout = 0;
	switch (channel)
	{
		case SPI_CHANNEL_1:
			while ((UC0IFG & UCB0TXIFG) == 0)						// wait while not ready for TX
			{
				if (timeout++ > 8000)
				{
					return;
				}
			}
			SPI_clearInterruptFlag(channel);
			UCB0TXBUF	 = byte;									// write
			while ((UC0IFG & UCB0RXIFG) == 0)						// wait for RX buffer (full)
			{
				if (timeout++ > 8000)
				{
					return;
				}
			}
			break;
			
		case SPI_CHANNEL_2:
			while ((UC0IFG & UCA0TXIFG) == 0)						// wait while not ready for TX
			{
				if (timeout++ > 8000)
				{
					return;
				}
			}
			SPI_clearInterruptFlag(channel);
			UCA0TXBUF	 = byte;									// write
			while ((UC0IFG & UCA0RXIFG) == 0)						// wait for RX buffer (full)
			{
				if (timeout++ > 8000)
				{
					return;
				}
			}
			break;
		
		default:
			return;
	}
}

Byte SPI_READ(SPI_CHANNEL channel)
{
	switch (channel)
	{
		case SPI_CHANNEL_1: return (UCB0RXBUF);
		case SPI_CHANNEL_2: return (UCA0RXBUF);
		default:			return DUMMY_CHAR;
	}
}

void SPI_setDummyOutput(SPI_CHANNEL channel)
{
	switch (channel)
	{
		case SPI_CHANNEL_1: UCB0TXBUF = DUMMY_CHAR;
		case SPI_CHANNEL_2: UCA0TXBUF = DUMMY_CHAR;
		default:			return;
	}
}

///////////////////////////////////////////////


void SPI_transmit(SPI_Device* device, const Byte data, bool useChipSelect)
{
	device->transmitMessage[0] = data;
	//SPI_reset(device->channel);
	
	if (device->type == SPI_TYPE_Master)
	{

		if (device->activeHigh) setDigitalOutput(device->chipSelect.out);
		else clearDigitalOutput(device->chipSelect.out);

		//SPI_slaveEnable(device->channel);
		SPI_WRITE(device->channel, device->transmitMessage[0]);
		device->receiveMessage[0] = SPI_READ(device->channel);
		//SPI_slaveDisable(device->channel);
		
		if (useChipSelect)
		{
			if (device->activeHigh == true) clearDigitalOutput(device->chipSelect.out);
			else setDigitalOutput(device->chipSelect.out);
		}
	}
	else if (device->type == SPI_TYPE_Slave)
	{
		int timeout = 0;
		while(!device->chipSelect.in->state)				// wait for enable
		{
			if (timeout++ > 10000) return;
		}
		SPI_clearInterruptFlag(device->channel);
		SPI_WRITE(device->channel, device->transmitMessage[0]);
		device->receiveMessage[0] = SPI_READ(device->channel);
	}
}

///////////////////////////////////////////////

void SPI_receive(SPI_Device* device, bool useChipSelect)
{
	device->receiveMessage[0] = DUMMY_CHAR;
	
	if (device->type == SPI_TYPE_Master)
	{
		SPI_transmit(device, DUMMY_CHAR, useChipSelect);
	}
	else if (device->type == SPI_TYPE_Slave)
	{
		int timeout = 0;
		SPI_reset(device->channel);
		SPI_setDummyOutput(device->channel);
		while(device->chipSelect.in->state == low)		// wait for chip select
	  	{
	  		readDigitalInput(device->chipSelect.in);
	  		if (timeout++ > 10000) return;
	  	}
		
		if (device->channel == SPI_CHANNEL_1)
		{	
		  	while((P3IN & 0x01) == 0x01)					// wait for slave transmit enable
		  	{
		  		if (timeout++ > 10000) return;
		  	}
		  	bool enabled = ((P3IN | 0xFE) == 0xFE);
			if (enabled)
			{
				while ((UC0IFG & UCB0RXIFG) == 0)			// wait for RX buffer (full)
				{
		  			if (timeout++ > 10000) return;
				}
			}
		}
		else if (device->channel == SPI_CHANNEL_2)
		{
		  	while((P7IN & 0x01) == 0x01)					// wait for slave transmit enable
		  	{
		  		if (timeout++ > 10000) return;
		  	}
		  	bool enabled = ((P7IN | 0xFE) == 0xFE);
			if (enabled)
			{
				while ((UC0IFG & UCB0RXIFG) == 0)			// wait for RX buffer (full)
				{
		  			if (timeout++ > 10000) return;
				}
			}
		}
		device->receiveMessage[0] = SPI_READ(device->channel);
	}
}

////////////////

void SPI_transmitStream(SPI_Device* device, const Byte* data, UI8 length, bool useChipSelect)
{
	if (length > SPI_RX_BUFFER_SIZE || length > SPI_TX_BUFFER_SIZE) return;	// error
	
	if (device->type == SPI_TYPE_Master)
	{
		int index;
		
		if (device->activeHigh == true) setDigitalOutput(device->chipSelect.out);
		else clearDigitalOutput(device->chipSelect.out);
		
		for (index = 0; index < length; index++)
		{
			device->transmitMessage[index] = data[index];
			SPI_WRITE(device->channel, device->transmitMessage[index]);
			device->receiveMessage[index] = SPI_READ(device->channel);
		}
		//SPI_slaveDisable(device->channel);
		
		if (useChipSelect)
		{
			if (device->activeHigh == true) clearDigitalOutput(device->chipSelect.out);
			else setDigitalOutput(device->chipSelect.out);
		}
	}
	else if (device->type == SPI_TYPE_Slave)
	{
		int timeout = 0;
		while(!device->chipSelect.in->state)					// slave must wait for enable
		{
			if (timeout++ > 10000) return;
		}
		int index;
		for (index = 0; index < length; index++)
		{
			SPI_reset(device->channel);
			SPI_clearInterruptFlag(device->channel);
			device->transmitMessage[index] = data[index];
			SPI_WRITE(device->channel, device->transmitMessage[index]);
			device->receiveMessage[index] = SPI_READ(device->channel);
		}
	}
}



