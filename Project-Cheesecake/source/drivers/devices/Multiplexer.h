//////////////////////////////////////////////////////////////////
//                                                              //
//    Multiplexer header                                        //
//    last edited by: Kane Anderson                             //
//    date: November 23, 2011                                   //
//                                                              //
//////////////////////////////////////////////////////////////////

#ifndef MULTIPLEXER_H
#define MULTIPLEXER_H

#include "../DriversConfig.h"

///////////////////////////////////////////////

// structure //////////////////////////////////

typedef struct
{
	DigitalOutput* S0;
	DigitalOutput* S1;
	DigitalOutput* S2;
}
MultiplexerSelectLines;

typedef struct
{
	MultiplexerSelectLines* selectLines;
	
	DigitalInput* currentInput;
	
	bool input[8];
}
DigitalMultiplexer_8_1_Inputs;

typedef struct
{
	MultiplexerSelectLines* selectLines;
	
	AnalogInput* currentInput;
	
	Millivolts input[8];
}
AnalogMultiplexer_8_1_Inputs;

typedef struct
{
	MultiplexerSelectLines* selectLines;
	
	DigitalOutput* currentOutput;
	
	bool output[8];
}
DigitalSoftwareMultiplexer_8_1_Outputs;

// functions //////////////////////////////////

void readMultiplexedDigitalInput(DigitalMultiplexer_8_1_Inputs* mux);
void readMultiplexedAnalogInput(AnalogMultiplexer_8_1_Inputs* mux);
void sendSoftwareMultiplexedDigitalOutput(DigitalSoftwareMultiplexer_8_1_Outputs* mux);
void goToNextMultiplexerSelection(MultiplexerSelectLines* selectLines);

#endif
