//******************************************************************************
//  SPI for MSP-FET430x169 Device Driver Source File
//
//  Description: This source file contains the implementation for the SPI driver
//
//  Chris Nichols
//  University of Manitoba
//  January 2008
//  Built with IAR Embedded Workbench Version: 4.01
//
//  Modified by Tianshao Ni
//  University of Manitoba
//  January 2012
//  Built with IAR Embedded Workbench Version: 5.30.1
//******************************************************************************

/*#include <spi.h>
#include <stdio.h>

#define MIN_DIV		0x0002				// Minimum SPI clock divider

int spi_cur_div = MIN_DIV;				// Current SPI clock divider

**
 * Initializes and enables the SPI module
 *
 * IN: void
 * OUT: int - error code (FALSE if no error)
 **
int spi_enable(void)
{
	// Check to make sure module is not in use
	//if()
	//{
	//	return ERR_BUS_BUSY;
	//}
	//else
	//{
		// Set SMCLK ~ 1.832MHz (Change this for faster?)
		//BCSCTL1 |= XTS;					// Use HF mode Y U NO NOT DO DIS
		BCSCTL1 &= ~XT2OFF;				// Ensure XT2CLK is active
		BCSCTL2 |= SELS;				// SMCLK = XT2CLK
		BCSCTL2 &= ~(DIVS0 + DIVS1);	// Ensure SMCLK = XT2CLK / 1
		
		// Configure Port 3
		P3SEL |= SPI_SIMO + SPI_SOMI + SPI_SCLK;	// Pins used by SPI module
		__spi_deassert_cs();			// Set -CS_SD high
		P3DIR |= SPI_CS;				// Make sure -CS_SD is output
		
		// Recommended initalization procedure
		U0CTL = SWRST;					// Software reset USART0
		U0CTL |= CHAR + SYNC + MM;		// 8 bit characters, SPI Master mode
		U0MCTL = 0x00;					// Modulation control not used for SPI
		spi_set_speed(spi_cur_div);			// Set the clock speed
		U0TCTL |= CKPH + SSEL1 + STC;	// UCLK delayed half cycle, UCLK = SMCLK/U0BRx, 3 pin
	
		// Make sure Interrupts are cleared and disabled
		IE1 &= ~(UTXIE0 + URXIE0);
		IFG1 &= ~(UTXIFG0 + URXIFG0);
		
		// Enable the SPI Module
		ME1 |= USPIE0;					// Enable the SPI module
		U0CTL &= ~SWRST;				// Clear SWRST
	
		return NO_ERROR;
	//}
}

**
 * Disables the SPI module
 *
 * IN: void
 * OUT: int - error code (FALSE if no error)
 **
int spi_disable(void)
{
	int error = NO_ERROR;
	
	U0CTL |= SWRST;						// Reset the USART
	ME1 &= ~USPIE0;						// Disable the SPI Module
	
	return error;
}

**
 * Changes the clock divider for the SPI module
 *
 * IN: speed - indicates the desired divider for the SPI module
 * OUT: int - new SPI speed setting
 **
int spi_set_speed(int speed)
{
	int div = speed;
  
        if(spi_cur_div != speed)
	{
		U0CTL |= SWRST;					// Disable the SPI module
		
		// Make sure the divider is valid ( >= 2)
		if(div<MIN_DIV)
			div = MIN_DIV;
		
		// Change the divider settings
		U0BR1 = div >> 8;
		U0BR0 = div;
		
		spi_cur_div = div;					// Keep track of the current divider
		U0CTL &= ~SWRST;				// Enable the SPI module
	}
	
	return div;						// Return new speed
}

**
 * Transmits a single byte on the SPI bus
 *
 * IN: data - the byte to be sent
 * OUT: int - error code (FALSE if no error)
 **
int spi_tx(char data)
{
	int error = NO_ERROR;
	int i = 0;
	
	U0TXBUF = data;						// Load  the transmit buffer
	
	// Wait for the transmission to complete or timeout
	while( ((U0TCTL & TXEPT) != TXEPT) && (i < TIMEOUT) )
	{
		i++;
	}
	
	data = U0RXBUF;						// Dummy read to clear OE flag
	
	// Check to see if there was a timeout error
	if(i >= TIMEOUT)
		error = MODULE_SPI + ERR_TIMEOUT;
	
	return error;
}

**
 * Receives a single byte from the SPI bus
 *
 * IN: *data - pointer to the char where the received byte will be stored
 * OUT: int - error code (FALSE if no error)
 **
int rx_spi(char* data)
{
	int error = NO_ERROR;
	int i = 0;
	
	IFG1 &= ~URXIFG0;					// Clear the receive interrupt flag
	
	// Transmit and receive occur simultaneously
	U0TXBUF = 0xFF;						// Dummy write

	// Wait for receive to complete or timeout
	while( ((IFG1 & URXIFG0) != URXIFG0) && (i < TIMEOUT) )
	{
                
		i++;
	}

	*data = U0RXBUF;					// Copy the received byte
	
	// Check to see if there was a timeout or overrun error
	if(i >= TIMEOUT)
		error = MODULE_SPI + ERR_TIMEOUT;
	else if(U0RCTL & OE)
		error = MODULE_SPI + ERR_FLOW;
	
	return error;
}
*/

