//////////////////////////////////////////////////////////////////
//                                                              //
//    representation of the processor's A2D                     //
//    last edited by: Kane Anderson                             //
//    date: March 8, 2012                                    	//
//																//
//////////////////////////////////////////////////////////////////

#include "./AnalogToDigitalConverter.h"

//////////////////////////////////////////////////////////////////

void initialize_analogToDigitalConverter(void)
{
	ADC12CTL0  = 0x0000;			// allows you to configure the analog to digital port
	ADC12CTL0 |= SHT01;				// 8 clock cycles per conversion
	ADC12CTL0 |= MSC;				// multiple sample and conversion
	ADC12CTL0 |= REFON;				// reference voltage supply on
	ADC12CTL0 |= ADC12ON;			// analog to digital converter on
	
	ADC12CTL1  = 0x0000;			// fresh start
	ADC12CTL1 |= CSTARTADD0;		// start at the first one
	ADC12CTL1 |= SHP;				// SAMPCON sourced from the sampling timer 
	ADC12CTL1 |= ADC12DIV0;
	ADC12CTL1 |= ADC12DIV1;
	ADC12CTL1 |= ADC12DIV2;			// divide the ADC clock by 8
	ADC12CTL1 |= ADC12SSEL1;		// use the master clock signal 
	ADC12CTL1 |= CONSEQ0;			// mode is sequence of channels
   	
	ADC12MCTL0	= 0x00;				// makes A0 go to MEM0, with V+ = Vcc and V- = Vss
	ADC12MCTL1	= 0x01;				// makes A1 go to MEM1, with V+ = Vcc and V- = Vss
	ADC12MCTL2	= 0x02;				// makes A2 go to MEM2, with V+ = Vcc and V- = Vss
	ADC12MCTL3	= 0x03;				// makes A3 go to MEM3, with V+ = Vcc and V- = Vss
	ADC12MCTL4	= 0x04;				// makes A4 go to MEM4, with V+ = Vcc and V- = Vss
	ADC12MCTL5	= 0x05;				// makes A5 go to MEM5, with V+ = Vcc and V- = Vss
	ADC12MCTL6	= 0x06;				// makes A6 go to MEM6, with V+ = Vcc and V- = Vss
	ADC12MCTL7	= 0x07;				// makes A7 go to MEM7, with V+ = Vcc and V- = Vss
	ADC12MCTL8	= 0x0C;				// makes A12 go to MEM8, with V+ = Vcc and V- = Vss
	ADC12MCTL9	= 0x0D;				// makes A13 go to MEM9, with V+ = Vcc and V- = Vss
	ADC12MCTL10	= 0x0E;				// makes A14 go to MEM10, with V+ = Vcc and V- = Vss
	ADC12MCTL11	= 0x0F | EOS;		// makes A15 go to MEM11, with V+ = Vcc and V- = Vss
	
	ADC12IE		= 0x00;				// disable analog to digital interrupts... we'll get to them soon enough
	
	P6SEL		= 0xFF; 			// sets port 6 to use all 8 A2D
}

//////////////////////////////////////////////////////////////////

#include "stdio.h"

void startNewAnalogToDigitalConversion(void)
{
	// this involves toggling the ENC bit of the ADC12CTL0 register
	// see msp430fg4618 user guide page 28-12
	ADC12CTL0 |= (ENC+ADC12SC);
	
	while ((ADC12CTL1 & ADC12BUSY))
	{
		;
	}

}






