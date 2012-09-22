//////////////////////////////////////////////////////////////////
//                                                              //
//    representation of the processor's D2A                     //
//    last edited by: Kane Anderson                             //
//    date: June 26, 2012                                    	//
//																//
//////////////////////////////////////////////////////////////////

#include "./DigitalToAnalogConverter.h"

//////////////////////////////////////////////////////////////////

void initialize_digitalToAnalogConverter(void)
{
	DAC12_0CTL  = 0x00;
	
	DAC12_0CTL &= ~DAC12OPS;		// output on P6.6
	DAC12_0CTL |= DAC12SREF1;		// 
	DAC12_0CTL |= DAC12SREF0;		// sets reference voltage to Vref+
	DAC12_0CTL &= ~DAC12RES;		// sets the resolution to 12 bits instead of 8
	DAC12_0CTL |= DAC12IR;			// output range is 0 -> Vref
	DAC12_0CTL |= DAC12AMP_7;		// high speed, high current usage
	
	DAC12_1CTL &= ~DAC12OPS;		// output on P6.7
	DAC12_1CTL &= ~DAC12SREF1;		// 
	DAC12_1CTL &= ~DAC12SREF0;		// sets reference voltage to Vref+
	DAC12_1CTL &= ~DAC12RES;		// sets the resolution to 12 bits instead of 8
	DAC12_1CTL |= DAC12IR;			// output range is 0 -> Vref
	DAC12_1CTL |= DAC12AMP_7;		// high speed, high current usage
	
	// Do a calibration
	DAC12_0CTL |= DAC12CALON;		// calibrate the DAC
	while ((DAC12_0CTL & DAC12CALON) == 0x0200) ;
}

//////////////////////////////////////////////////////////////////

void startNewDigitalToAnalogConversion(Word digital_12_bit_value)
{
	if (digital_12_bit_value > 0x0FFF)
	{
		return;
	}

	DAC12_0DAT = digital_12_bit_value;

}


