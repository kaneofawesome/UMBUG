//////////////////////////////////////////////////////////////////
//                                                              //
//    IO Types   	                                            //
//    last edited by: Kane Anderson                             //
//    date: March 8, 2012 		                                //
//                                                              //
//////////////////////////////////////////////////////////////////

#ifndef IOTYPES_H
#define IOTYPES_H

#include <msp430fg4618.h>
#include "../SimpleDefinitions.h"
#include "./devices/msp430/AnalogToDigitalConverter.h"
#include "./devices/msp430/DigitalToAnalogConverter.h"

///////////////////////////////////////////////

typedef struct
{
	volatile unsigned char* port;
	char pin;
	bool state;
}
DigitalInput;

void initializeDigitalInput(DigitalInput* input, volatile unsigned char* port, char pin);
void readDigitalInput(DigitalInput* input);

///////////////////////////////////////////////


typedef DigitalInput SerialInput;

void initializeSerialInput(SerialInput* input, volatile unsigned char* port, char pin);
void setSerialInput(SerialInput* input);
void clearSerialInput(SerialInput* input);

///////////////////////////////////////////////

typedef struct
{
	volatile unsigned char* port;
	char pin;
	Millivolts value;
}
AnalogInput;

void initializeAnalogInput(AnalogInput* input, volatile unsigned char* port, char pin);
void readAnalogInput(AnalogInput* input);

////////////////////////////////////////////////

typedef struct
{
	volatile unsigned char* port;
	char pin;
	Word value;
}
AnalogOutput;

void initializeAnalogOutput(AnalogOutput* output, volatile unsigned char* port, char pin);
void sendAnalogOutput(AnalogOutput* output);

////////////////////////////////////////////////


typedef struct
{
	volatile unsigned char* port;
	char pin;
	bool state;
}
DigitalOutput;

void initializeDigitalOutput(DigitalOutput* output, volatile unsigned char* port, char pin);
void setDigitalOutput(DigitalOutput* output);
void clearDigitalOutput(DigitalOutput* output);

/////////////////////////////////////////////////

typedef DigitalOutput SerialOutput;

void initializeSerialOutput(SerialOutput* output, volatile unsigned char* port, char pin);
void setSerialOutput(SerialOutput* output);
void clearSerialOutput(SerialOutput* output);

///////////////////////////////////////////////

#endif
