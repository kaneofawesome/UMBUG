//////////////////////////////////////////////////////////////////
//                                                              //
//    IO Types	                                                //
//    last edited by: Kane Anderson                             //
//    date: June 26, 2012                                   	//
//                                                              //
//////////////////////////////////////////////////////////////////

#include "./IOTypes.h"

//////////////////////////////////////////////////////////////////

void initializeAnalogOutput(AnalogOutput* output, volatile unsigned char* port, char pin)
{
	// nothing to do here
}

void sendAnalogOutput(AnalogOutput* output)
{
	if ((output->port == &P6OUT) && (output->pin == 6))
	{
		startNewDigitalToAnalogConversion(output->value);
	}
}

//////////////////////////////////////////////////////////////////

void initializeDigitalInput(DigitalInput* input, volatile unsigned char* port, char pin)
{
	input->port = port;
	input->pin = pin;
	input->state = false;
}

void readDigitalInput(DigitalInput* input)
{
	
	if		(input->pin == 0) input->state = (bool)((*(input->port) & BIT0) >> 0);
	else if (input->pin == 1) input->state = (bool)((*(input->port) & BIT1) >> 1);
	else if (input->pin == 2) input->state = (bool)((*(input->port) & BIT2) >> 2);
	else if (input->pin == 3) input->state = (bool)((*(input->port) & BIT3) >> 3);
	else if (input->pin == 4) input->state = (bool)((*(input->port) & BIT4) >> 4);
	else if (input->pin == 5) input->state = (bool)((*(input->port) & BIT5) >> 5);
	else if (input->pin == 6) input->state = (bool)((*(input->port) & BIT6) >> 6);
	else if (input->pin == 7) input->state = (bool)((*(input->port) & BIT7) >> 7);
	

}

//////////////////////////////////////////////////////////////////

void initializeSerialInput(SerialInput* input, volatile unsigned char* port, char pin)
{
	input->port = port;
	input->pin = pin;
	input->state = false;
}

//////////////////////////////////////////////////////////////////

void initializeSerialOutput(SerialOutput* output, volatile unsigned char* port, char pin)
{
	output->port = port;
	output->pin = pin;
	output->state = false;
}

//////////////////////////////////////////////////////////////////



///////////////////////////////////////////////

void initializeAnalogInput(AnalogInput* input, volatile unsigned char* port, char pin)
{
	input->port = port;
	input->pin = pin;
	input->value = 0x0000;
}

void readAnalogInput(AnalogInput* input)
{
	startNewAnalogToDigitalConversion();
	
	//////////////
	
	// store the temporary reading 0 -> 4095
	UI16 temp = 0;
	
	if (input->port == &P5IN)
	{
		switch (input->pin)
		{
			case 0:		temp = ADC12MEM9; break;
			case 1:		temp = ADC12MEM8; break;
			default: return;
		}
	}
	
	else if (input->port == &P6IN)
	{
		switch (input->pin)
		{
			case 0:		temp = ADC12MEM0; break;
			case 1:		temp = ADC12MEM1; break;
			case 2:		temp = ADC12MEM2; break;
			case 3:		temp = ADC12MEM3; break;
			case 4:		temp = ADC12MEM4; break;
			case 5:		temp = ADC12MEM5; break;
			case 7:		temp = ADC12MEM7; break;
			default: return;
		}
	}
	
	else if (input->port == &P10IN)
	{
		switch (input->pin)
		{
			case 6:		temp = ADC12MEM11; break;
			case 7:		temp = ADC12MEM10; break;
			default: return;
		}
	}
	
	else
	{
		return;
	}
	
	// change the raw number 0 -> 4095 into voltage
	// we are using 3.3V = 3300 mV
	
	input->value = (Millivolts)((temp * ThreePointThreeVolts) / highestA2DReading);

}

///////////////////////////////////////////////

void initializeDigitalOutput(DigitalOutput* output, volatile unsigned char* port, char pin)
{
	output->port = port;
	output->pin = pin;
	output->state = false;
}

void setDigitalOutput(DigitalOutput* output)
{
	if		(output->pin == 0) *(output->port) |= BIT0;
	else if (output->pin == 1) *(output->port) |= BIT1;
	else if (output->pin == 2) *(output->port) |= BIT2;
	else if (output->pin == 3) *(output->port) |= BIT3;
	else if (output->pin == 4) *(output->port) |= BIT4;
	else if (output->pin == 5) *(output->port) |= BIT5;
	else if (output->pin == 6) *(output->port) |= BIT6;
	else if (output->pin == 7) *(output->port) |= BIT7;
	
}

void clearDigitalOutput(DigitalOutput* output)
{
	if		(output->pin == 0) *(output->port) &= ~BIT0;
	else if (output->pin == 1) *(output->port) &= ~BIT1;
	else if (output->pin == 2) *(output->port) &= ~BIT2;
	else if (output->pin == 3) *(output->port) &= ~BIT3;
	else if (output->pin == 4) *(output->port) &= ~BIT4;
	else if (output->pin == 5) *(output->port) &= ~BIT5;
	else if (output->pin == 6) *(output->port) &= ~BIT6;
	else if (output->pin == 7) *(output->port) &= ~BIT7;
	
}

///////////////////////////////////////////////

void readSerialInput(SerialOutput* input) { readDigitalInput((DigitalInput*)input); }

void setSerialOutput(SerialOutput* output) { setDigitalOutput((DigitalOutput*)output); }
void clearSerialOutput(SerialOutput* output) { clearDigitalOutput((DigitalOutput*)output); }




