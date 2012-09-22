#ifndef TI_USCI_UART_REGS_H_
#define TI_USCI_UART_REGS_H_




#if (USART_A_MODULE == 0)
  #ifdef   __MSP430_HAS_USART_A0__         /***  check if module is  is available ***/
    #define USAxCTL		     U0CTL		/* USART Control Register  */	
    #define USAxBR0     	 U0BR0			/* USART Baud Rate 0 */
    #define USAxBR1     	 U0BR1			/* USART Baud Rate 1 */
    #define USAxMCTL   	     U0MCTL		    /* USART modulation control register*/
    #define USAxRXCTL   	 U0RCTL 		/* USART Receive Control  Register */
    #define USAxTXCTL   	 U0TCTL   		/* USART Transmit Control Register */
    #define USAxRXBUF        U0RXBUF        /* USART Receive Register Buffer*/
    #define USAxRXBUF        U0RXBUF        /* USART Receive Register Buffer*/
    #define USAxIE 		     IE1       		/* USART Interrupt Enable Register */
    #define USAxIFG		     IFG1      		/* USART Interrupt Flags Register */                        
    #define USAxME           ME1             /* USART Module Enable */

  
    #define USAxRXIE         BIT1
    #define USAxTXIE         BIT0
    #define USAxRXIFG        BIT6
    #define USAxTXIFG        BIT7
  
  #endif
  
#elif (USART_A_MODULE == 1)
  #ifdef   __MSP430_HAS_USART_A1__
     #define USAxCTL		 U1CTL		/* USART Control Register  */	
    #define USAxBR0     	 U1BR0			/* USART Baud Rate 0 */
    #define USAxBR1     	 U1BR1			/* USART Baud Rate 1 */
    #define USAxMCTL   	     U1MCTL		    /* USART modulation control register*/
    #define USAxRXCTL   	 U1RCTL 		/* USART Receive Control  Register */
    #define USAxTXCTL   	 U1TCTL   		/* USART Transmit Control Register */
    #define USAxRXBUF        U1RXBUF        /* USART Receive Register Buffer*/
    #define USAxRXBUF        U1RXBUF        /* USART Receive Register Buffer*/
    #define USAxIE 		     IE2       		/* USART Interrupt Enable Register */
    #define USAxIFG		     IFG2      		/* USART Interrupt Flags Register */                        
    #define USAxME           ME2            /* USART Module Enable */

  #endif
#else 
  #error "USART Module not supported"
#endif  



#endif /*TI_USCI_UART_REGS_H_*/
