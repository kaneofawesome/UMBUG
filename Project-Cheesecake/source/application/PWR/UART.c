//******************************************************************************
//  File UART.c
//
//  Description: This  file provides all the required functions to send
//               and receive data using UART module
// version1.0  
//Author: Mohamed Temam Nasri
//		  31/05/2012
//******************************************************************************* 	


//#include "main.h"
#include "UART.h"

#if COM_PROCESSOR_COMPILE
	#include "../COM/COMApplication.h"
#endif

UART_RESERVE_STATE currentUARTUser = UART_NOT_RESERVED;

/*#include <stdio.h>
#define USAxCTL		         U1CTL		// USART Control Register  /	
    #define USAxBR0     	 U1BR0			// USART Baud Rate 0 /
    #define USAxBR1     	 U1BR1			// USART Baud Rate 1 /
    #define USAxMCTL   	     U1MCTL		    // USART modulation control register/
    #define USAxRXCTL   	 U1RCTL 		// USART Receive Control  Register /
    #define USAxTXCTL   	 U1TCTL   		// USART Transmit Control Register /
    #define USAxRXBUF        U1RXBUF        // USART Receive Register Buffer/
    #define USAxTXBUF        U1TXBUF       /// USART Transmit Register Buffer/
    #define USAxIE 		     IE2       		// USART Interrupt Enable Register /
    #define USAxIFG		     IFG2      		// USART Interrupt Flags Register /                        
    #define USAxME           ME2            // USART Module Enable /
    #define USAxMCTL         U1MCTL          // Modulation control register
  
    #define USAxRXIE         BIT4
    #define USAxTXIE         BIT5
    #define USAxRXIFG        BIT4
    #define USAxTXIFG        BIT5
  */
/**
* @brief Function Name:     InitUART.                                                 
* @brief  Description: This function initialized the USCI-UART.
* @param none                                                   
* @return none                                                    
*/     


void setUARTState(UART_RESERVE_STATE res)
{
	currentUARTUser = res;
}

UART_RESERVE_STATE getUARTState(){
	return currentUARTUser;
}


void InitUART(void){ 
/* --COPYRIGHT--,BSD_EX
 * Copyright (c) 2012, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *******************************************************************************
 * 
 *                       MSP430 CODE EXAMPLE DISCLAIMER
 *
 * MSP430 code examples are self-contained low-level programs that typically
 * demonstrate a single peripheral function or device feature in a highly
 * concise manner. For this the code may rely on the device's power-on default
 * register values and settings such as the clock configuration and care must
 * be taken when combining code from several examples to avoid potential side
 * effects. Also see www.ti.com/grace for a GUI- and www.ti.com/msp430ware
 * for an API functional library-approach to peripheral configuration.
 *
 * --/COPYRIGHT--*/
//******************************************************************************
//   MSP430xG46x Demo - USART1, 115200 UART Echo ISR, DCO SMCLK
//
//   Description: Echo a received character, RX ISR used. Normal mode is LPM0.
//   USART1 RX interrupt triggers TX Echo.
//   Baud rate divider with 1048576hz = 1048576/115200 = ~9.1 (009h|08h)
//   ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
//   //* An external watch crystal between XIN & XOUT is required for ACLK *//	
//
//                MSP430FG4619
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32kHz
//          --|RST          XOUT|-
//            |                 |
//            |       P4.0/UTXD1|------------>
//            |                 | 115200 - 8N1
//            |       P4.1/URXD1|<------------
//
//   K. Quiring
//   Texas Instruments Inc.
//   October 2005
//   Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.39 beta
//******************************************************************************
  volatile unsigned int i;
  
  printf("in Uart_init\n");
  fflush(stdout);

  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  //FLL_CTL0 |= XCAP14PF;                     // Configure load caps

  P4SEL |= 0x03;                            // P4.1,0 = USART1 TXD/RXD
  /*
  do{
  	IFG1 &= ~OFIFG;                           // Clear OSCFault flag
  	for (i = 0x47FF; i > 0; i--);             // Time for flag to set
  }while ((IFG1 & OFIFG));                   // OSCFault flag still set?
  */
  ME2 |= UTXE1 + URXE1;                     // Enable USART1 TXD/RXD
  U1CTL |= CHAR;                            // 8-bit character
  //U1TCTL |= SSEL1;                          // UCLK= ACLK
  U1TCTL |= SSEL1 + SSEL0;//SMCLK
  
  
  /*
  uart calculator: http://mspgcc.sourceforge.net/baudrate.html
  this program license is at: http://www.fsf.org/licenses/licenses.html#GPL
  this program is distributed WITHOUT ANY WARRANTY

  clock: 9500000Hz
  desired baud rate: 115200bps
  division factor: 82.5
  effective baud rate: 115152bps
  maximum error: 0.0489us   0.56%

  time table (microseconds):
        event      desired effective  error   error%
    startbit->D0      8.68      8.63  +0.0489  +0.56
    D0->D1           17.36     17.37  -0.0073  -0.08
    D1->D2           26.04     26.00  +0.0416  +0.48
    D2->D3           34.72     34.74  -0.0146  -0.17
    D3->D4           43.40     43.37  +0.0343  +0.40
    D4->D5           52.08     52.11  -0.0219  -0.25
    D5->D6           60.76     60.74   +0.027  +0.31
    D6->D7           69.44     69.47  -0.0292  -0.34
    D7->stopbit      78.12     78.11  +0.0197  +0.23
    end of stopb     86.81     86.84  -0.0365  -0.42
*/
//UBR00=0x52; UBR10=0x00; UMCTL0=0xAA; // uart0 9500000Hz 115151bps


  U1BR0 = 0x2f;//52;//4E;//0x56;//45                             // 5466.666MHz 115200
  U1BR1 = 0x00;                             // 1MHz 115200
  U1MCTL = 0xAA;//08;//0x7B;    //AA                        // 9.5MHz 115200 modulation
  U1CTL &= ~SWRST;                          // Initialize USART state machine
  IE2 |= URXIE1;                            // Enable USART1 RX interrupt

//LPM is for hosers
  _BIS_SR(/*LPM0_bits + */GIE);                 // Enter LPM0 w/ interrupt

  
}


#pragma vector=USART1RX_VECTOR
__interrupt void USART1_rx (void)
{
    if(IFG2 & URXIFG1)
    {
        switch(getUARTState())
        {
            case UART_NOT_RESERVED:
                break;
            case UART_POWER:
                break;
            case UART_CAMorSPEC:
                break;
            case UART_ADCS:
                break;
            case UART_OVER_GROUNDSTATION:
                break;
                
        }
    }
  //while (!(IFG2 & UTXIFG1));                // USART1 TX buffer ready?
  //TXBUF1 = RXBUF1;                          // RXBUF1 to TXBUF1
}

/*
 returns > 0 if we have data, else 0 for UART1 register
 */
UI8 UARTDataReady()
{
    return IFG2 & URXIFG1;
}

UI8 readUARTData()
{
    return RXBUF1;
}

void sendUARTData(UI8 data)
{
    while(!(IFG2 & UTXIFG1));
    TXBUF1 = data;
}

void sendUARTDataArray(UI8* data, int length)
{
	int i = 0;
	for (i = 0; i < length; i++){
		while(!(IFG2 & UTXIFG1));
    	TXBUF1 = data[i];
	}
}

void initializeDataToCOMOverSPI(int length){
	//TODO:
	
	//This will only be used by the spectrometer and the camera
	
	//Order of events:
	//- Tell coms what's about to go down.
	//- Send it the header, the packet ID, and the timestamp.
}

void sendUARTDataToCOMOverSPI(int length){
	//BIG TODO: this is critical and tricky. Best of luck.
	
	//This will only be used by the spectrometer and the camera
	
	//Order of events:
	//- Flood the camera data through to COM
	//- Send it the footer.
}
    
/* **************End of INITIALIZATION OF THE UART*****************************/


  


