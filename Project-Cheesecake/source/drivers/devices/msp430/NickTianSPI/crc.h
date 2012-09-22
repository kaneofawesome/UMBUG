//******************************************************************************
//  CRC Calculations for the MSP430 header file
//
//  Description: This header file contains the interface of several CRC
//               generating/checking algorithms
//
//  Chris Nichols
//  University of Manitoba
//  January 2008
//  Built with IAR Embedded Workbench Version: 4.01
//******************************************************************************

// prevent multiple instances of the same file
#ifndef __CRC_H__     
#define __CRC_H__

#include "../../../../SimpleDefinitions.h"

	/**
	 * Generates a CRC-7 given a polynomial and an num-byte sequence
	 *
	 * IN: data - a sequence of bytes which for which a CRC is desired
	 *     numBytes - the size (in bytes) of data (max 255)
	 *     poly - the polynomial to be used to generate the CRC
	 * OUT: char - the CRC byte for data
	 **/
	char make_crc7(Byte *data, char numBytes, char poly);

	/**
	 * Generates a CRC-8 given a polynomial and an num-byte sequence
	 *
	 * IN: data - a sequence of bytes which for which a CRC is desired
	 *     numBytes - the size (in bytes) of data
	 *     poly - the polynomial to be used to generate the CRC
	 * OUT: char - the CRC byte for data
	 **/
	char make_crc8(Byte *data, char numBytes, char poly);

	/**
	 * Generates a CRC-16 given a polynomial and an num-byte sequence
	 *
	 * IN: data - a sequence of bytes which for which a CRC is desired
	 *     numBytes - the size (in bytes) of data (max 65535)
	 *     poly - the polynomial to be used to generate the CRC
	 * OUT: int - the CRC bytes for data
	 **/
	int make_crc16(Byte *data, int numBytes, int poly);
        
    /**
     * Generates a CRC-16 for a fixed 512 byte. Data less than 512 byte is padded with zero.
     * This function is used exclusively to generate CRC for the SD card.
     *
     * IN: data - a sequence of bytes which for which a CRC is desired
     *     numBytes - the size (in bytes) of data (max 2048)
     *     poly - the polynomial to be used to generate the CRC
     * OUT: int - the CRC bytes for data
     **/
    int make_crc16_sd(Byte *data, int numBytes, int poly);

#endif // __CRC_H__
