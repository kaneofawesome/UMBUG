//******************************************************************************
//  SPI for MSP-FET430x169 Device Driver Header File
//
//  Description: This header file contains the interface for the SPI driver
//
//  Chris Nichols
//  University of Manitoba
//  January 2008
//  Built with IAR Embedded Workbench Version: 4.01
//******************************************************************************

// prevent multiple instances of the same file
#ifndef __SPI_H__
#define __SPI_H__

	/**
	 * DEBUG flag for the SPI driver
	 * Turning this on will cause printing of information regarding the operation 
	 * of the SPI driver to standard output regardless of the master DEBUG flag
	 **/
	#define SPI_DEBUG				TRUE

	/**
	 * Include MSP430 pin definitions
	 **/
	#include <msp430x16x.h>

	/**
	 * Include commonly used definitions
	 **/
	#include <common.h>

	/**
	 * Include error codes
	 **/
	#include <error_codes.h>

	/**
	 * Include crc generating routines
	 */
	#include <crc.h>

	/************************************************************ 
	 * Global Constants
	 ************************************************************/
	
	// SPI speed settings
	#define SPI_FULL_SPEED			0x0002

	// SPI pins
	#define SPI_CS					BIT0			// -CS_SD pin (active low)
	#define SPI_SIMO				BIT1			// SPI pin Slave In Master Out
	#define SPI_SOMI				BIT2			// SPI pin Slave Out Master In
	#define SPI_SCLK				BIT3			// SPI Pin Clock	

	/************************************************************ 
	 * Functions
	 ************************************************************/

	/**
	 * Initializes and enables the SPI module
	 *
	 * IN: void
	 * OUT: int - error code (FALSE if no error)
	 **/
	int spi_enable(void);

	/**
	 * Disables the SPI module
	 *
	 * IN: void
	 * OUT: int - error code (FALSE if no error)
	 **/
	int spi_disable(void);

	/**
	 * Macro that asserts the CS signal
	 **/
	#define __spi_assert_cs()		P3OUT &= ~SPI_CS

	/**
	 * Macro that de-asserts the CS signal
	 **/
	#define __spi_deassert_cs()		P3OUT |= SPI_CS

	/**
	 * Changes the clock divider for the SPI module
	 *
	 * IN: speed - indicates the desired divider for the SPI module
	 * OUT: int - new SPI speed setting
	 **/
	int spi_set_speed(int speed);

	/**
	 * Transmits a single byte on the SPI bus
	 *
	 * IN: data - the byte to be sent
	 * OUT: int - error code (FALSE if no error)
	 **/
	int spi_tx(char data);

	/**
	 * Receives a single byte from the SPI bus
	 *
	 * IN: *data - pointer to the char where the received byte will be stored
	 * OUT: int - error code (FALSE if no error)
	 **/
	int rx_spi(char* data);

#endif // __SPI_H__
