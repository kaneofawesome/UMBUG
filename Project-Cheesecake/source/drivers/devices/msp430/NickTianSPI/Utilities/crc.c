//******************************************************************************
//  CRC Calculations for the MSP430 source file
//
//  Description: This source file contains the implementation of several CRC
//               generating/checking algorithms
//
//  Chris Nichols
//  University of Manitoba
//  January 2008
//  Built with IAR Embedded Workbench Version: 4.01
//  
//  Tianshao Ni
//  University of Manitoba
//  January 2012
//  Built with IAR Embedded Workbench Version: 5.30.1
//******************************************************************************

#include "../crc.h"

/**
 * Generates a CRC-8 given a polynomial and a num-byte sequence
 *
 * IN: data - a sequence of bytes which for which a CRC is desired
 *     numBytes - the size (in bytes) of data (max 255)
 *     poly - the polynomial to be used to generate the CRC
 * OUT: char - the CRC byte for data
 **/
char make_crc8(Byte *data, char numBytes, char poly)
{
	char crc = 0x00;
	char carry = 0x00;

	char i,j;

	// Go through all of the data bytes
	for(i = 0; i < numBytes; i++)
	{
		// XOR the current CRC with the next data byte
		crc ^= data[i];

		// Shift through every bit in the CRC
		for(j = 0; j < 8; j++)
		{
			// Check to see if the bit shifted out of the CRC is a 1
			carry = crc & 0x80;

			// Shift the CRC
			crc <<= 1;

			// XOR the CRC with the poly if a 1 was shifted out
			if(carry)
				crc ^= poly;
		} 
	}
	return crc;
}

/**
 * Generates a CRC-7 given a polynomial and a num-byte sequence
 *
 * IN: data - a sequence of bytes which for which a CRC is desired
 *     numBytes - the size (in bytes) of data (max 255)
 *     poly - the polynomial to be used to generate the CRC
 * OUT: char - the CRC byte for data
 **/
char make_crc7(Byte *data, char numBytes, char poly)
{
	char crc = 0x00;
	char curr;
	char carry;
	
	char i,j;
	
	// Go through all of the data bytes
	for(i = 0; i < numBytes; i++)
	{
		curr = data[i];
		
		// Shift in every bit
		for(j = 0; j < 8; j++)
		{
			// XOR the outgoing bit of the CRC with the incoming data bit
			carry = ((crc & 0x40) << 1) ^ (curr & 0x80);
			
			// Shift the current data byte and the crc
			curr = curr << 1;
			crc = crc << 1;
			
			// XOR the CRC with the poly depending on the result of carry
			if(carry)
				crc ^= poly;
		}
	}
	
	crc &= 0x7F;			// Only the last 7 bits are the CRC
	
	return crc;
}

/**
 * Generates a CRC-16 given a polynomial and a num-byte sequence
 *
 * IN: data - a sequence of bytes which for which a CRC is desired
 *     numBytes - the size (in bytes) of data (max 2048)
 *     poly - the polynomial to be used to generate the CRC
 * OUT: int - the CRC bytes for data
 **/
int make_crc16(Byte *data, int numBytes, int poly)
{
	int crc = 0x0000;
	char curr;
	char carry;
	
	int i;
	char j;
	
	// Go through all of the data bytes
	for(i = 0; i < numBytes; i++)
	{
		curr = data[i];
		
		// Shift in every bit
		for(j = 0; j < 8; j++)
		{
			// XOR the outgoing bit of the CRC with the incoming data bit
			carry = (curr & 0x80) ^ ((crc & 0x8000) >> 8);
			
			// Shift the current data byte and the crc
			curr = curr << 1;
			crc = crc << 1;
			
			// XOR the CRC with the poly depending on the result of carry
			if(carry)
				crc ^= poly;
		}
	}
	
	return crc;
}

/**
 * Generates a CRC-16 for a fixed 512 byte. Data less than 512 byte is padded with zero.
 * This function is used exclusively to generate CRC for the SD card.
 *
 * IN: data - a sequence of bytes which for which a CRC is desired
 *     numBytes - the size (in bytes) of data (max 2048)
 *     poly - the polynomial to be used to generate the CRC
 * OUT: int - the CRC bytes for data
 **/
int make_crc16_sd(Byte *data, int numBytes, int poly)
{
	int crc = 0x0000;
	char curr;
	char carry;
	
	int i;
	char j;
	
	// Go through all of the data bytes
	for(i = 0; i < 512; i++)
	{
                if (i < numBytes)
		    curr = data[i];
                else
                    curr = 0x00;
		
		// Shift in every bit
		for(j = 0; j < 8; j++)
		{
			// XOR the outgoing bit of the CRC with the incoming data bit
			carry = (curr & 0x80) ^ ((crc & 0x8000) >> 8);
			
			// Shift the current data byte and the crc
			curr = curr << 1;
			crc = crc << 1;
			
			// XOR the CRC with the poly depending on the result of carry
			if(carry)
				crc ^= poly;
		}
	}
	
	return crc;
}
