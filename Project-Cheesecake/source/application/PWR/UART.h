#ifndef UART_H_
#define UART_H_



//******************************************************************************
//  File UART.H
//
//  Description: This header file provides all the required functions to send
//               and receive data using UART module
// version1.0  
//Author: Mohamed Temam Nasri
//		  31/05/2012 	
//******************************************************************************

#include <msp430fg4618.h> 
#include "../../SimpleDefinitions.h"
#include <stdio.h>

typedef enum{ // These are now only being used to switch between UART_NOT_RESERVED and UART_OVER_GROUNDSTATION because uart will now be a blocking operation.
    UART_NOT_RESERVED,
    UART_POWER,
    UART_CAMorSPEC,
    UART_ADCS,
    UART_OVER_GROUNDSTATION // This is the indicator to say that we are over the ground station
                            // usage: if (getUARTState() == UART_OVER_GROUNDSTATION)
}UART_RESERVE_STATE;


/*#define USART_A_MODULE  1     // Select which USCI_A module to use [0-1]
#define UART_BAUDRATE  9600 //Specify baudrate
#define UART_BAUDRATE_REG  (unsigned short)(MCLK_FREQ/UART_BAUDRATE)

//define uart registers                   // check which port is available 
#define UART_PxIN      P4IN
#define UART_PxOUT     P4OUT
#define UART_PxDIR     P4DIR
#define UART_PxIFG     P4IFG
#define UART_PxIE      P4IE
#define UART_PxSEL     P4SEL


#define UART_RX_PAD    BIT1 // select uart pins To receive data
#define UART_TX_PAD    BIT0 // select uart pins To select data
*/

//include "TI_USCI_UART_Regs.h"
//Global Functions
void InitUART(void);
void setUARTState(UART_RESERVE_STATE res);
UART_RESERVE_STATE getUARTState();
UI8 UARTDataReady();
UI8 readUARTData();
void sendUARTData(UI8 data);
void sendUARTDataArray(UI8* data, int length);
void initializeDataToCOMOverSPI(int length);
void sendUARTDataToCOMOverSPI(int length);
 


#endif /*UART_H_*/

