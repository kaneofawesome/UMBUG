//////////////////////////////////////////////////////////////////
//                                                              //
//    Multiplexer source                                        //
//    last edited by: Kane Anderson                             //
//    date: January 22, 2012                                    //
//                                                              //
//////////////////////////////////////////////////////////////////

#include "Multiplexer.h"

///////////////////////////////////////////////

// functions //////////////////////////////////

void readMultiplexedDigitalInput(DigitalMultiplexer_8_1_Inputs* mux)
{
	     if (!mux->selectLines->S0->state && !mux->selectLines->S1->state && !mux->selectLines->S2->state) mux->input[0] = mux->currentInput->state;
	else if (!mux->selectLines->S0->state && !mux->selectLines->S1->state &&  mux->selectLines->S2->state) mux->input[1] = mux->currentInput->state;
	else if (!mux->selectLines->S0->state &&  mux->selectLines->S1->state && !mux->selectLines->S2->state) mux->input[2] = mux->currentInput->state;
	else if (!mux->selectLines->S0->state &&  mux->selectLines->S1->state &&  mux->selectLines->S2->state) mux->input[3] = mux->currentInput->state;
	else if ( mux->selectLines->S0->state && !mux->selectLines->S1->state && !mux->selectLines->S2->state) mux->input[4] = mux->currentInput->state;
	else if ( mux->selectLines->S0->state && !mux->selectLines->S1->state &&  mux->selectLines->S2->state) mux->input[5] = mux->currentInput->state;
	else if ( mux->selectLines->S0->state &&  mux->selectLines->S1->state && !mux->selectLines->S2->state) mux->input[6] = mux->currentInput->state;
	else if ( mux->selectLines->S0->state &&  mux->selectLines->S1->state &&  mux->selectLines->S2->state) mux->input[7] = mux->currentInput->state;
}

void readMultiplexedAnalogInput(AnalogMultiplexer_8_1_Inputs* mux)
{
	     if (!mux->selectLines->S0->state && !mux->selectLines->S1->state && !mux->selectLines->S2->state) mux->input[0] = mux->currentInput->value;
	else if (!mux->selectLines->S0->state && !mux->selectLines->S1->state &&  mux->selectLines->S2->state) mux->input[1] = mux->currentInput->value;
	else if (!mux->selectLines->S0->state &&  mux->selectLines->S1->state && !mux->selectLines->S2->state) mux->input[2] = mux->currentInput->value;
	else if (!mux->selectLines->S0->state &&  mux->selectLines->S1->state &&  mux->selectLines->S2->state) mux->input[3] = mux->currentInput->value;
	else if ( mux->selectLines->S0->state && !mux->selectLines->S1->state && !mux->selectLines->S2->state) mux->input[4] = mux->currentInput->value;
	else if ( mux->selectLines->S0->state && !mux->selectLines->S1->state &&  mux->selectLines->S2->state) mux->input[5] = mux->currentInput->value;
	else if ( mux->selectLines->S0->state &&  mux->selectLines->S1->state && !mux->selectLines->S2->state) mux->input[6] = mux->currentInput->value;
	else if ( mux->selectLines->S0->state &&  mux->selectLines->S1->state &&  mux->selectLines->S2->state) mux->input[7] = mux->currentInput->value;
}

void sendSoftwareMultiplexedDigitalOutput(DigitalSoftwareMultiplexer_8_1_Outputs* mux)
{
	     if (!mux->selectLines->S0->state && !mux->selectLines->S1->state && !mux->selectLines->S2->state) mux->currentOutput->state = mux->output[0];
	else if (!mux->selectLines->S0->state && !mux->selectLines->S1->state &&  mux->selectLines->S2->state) mux->currentOutput->state = mux->output[1];
	else if (!mux->selectLines->S0->state &&  mux->selectLines->S1->state && !mux->selectLines->S2->state) mux->currentOutput->state = mux->output[2];
	else if (!mux->selectLines->S0->state &&  mux->selectLines->S1->state &&  mux->selectLines->S2->state) mux->currentOutput->state = mux->output[3];
	else if ( mux->selectLines->S0->state && !mux->selectLines->S1->state && !mux->selectLines->S2->state) mux->currentOutput->state = mux->output[4];
	else if ( mux->selectLines->S0->state && !mux->selectLines->S1->state &&  mux->selectLines->S2->state) mux->currentOutput->state = mux->output[5];
	else if ( mux->selectLines->S0->state &&  mux->selectLines->S1->state && !mux->selectLines->S2->state) mux->currentOutput->state = mux->output[6];
	else if ( mux->selectLines->S0->state &&  mux->selectLines->S1->state &&  mux->selectLines->S2->state) mux->currentOutput->state = mux->output[7];
}


void goToNextMultiplexerSelection(MultiplexerSelectLines* selectLines)
{
	static int multiplexerSelectIndex = 0;	// only set on the first time
	switch(multiplexerSelectIndex++)	// loops from now on
	{
		case 0:		selectLines->S0->state = low;
					selectLines->S1->state = low;	// 000
					selectLines->S2->state = low;
					break;
		
		case 1:		selectLines->S0->state = low;
					selectLines->S1->state = low;	// 001
					selectLines->S2->state = high;
					break;
		
		case 2:		selectLines->S0->state = low;
					selectLines->S1->state = high;	// 010
					selectLines->S2->state = low;
					break;
		
		case 3:		selectLines->S0->state = low;
					selectLines->S1->state = high;	// 011
					selectLines->S2->state = high;
					break;
		
		case 4:		selectLines->S0->state = high;
					selectLines->S1->state = low;	// 100
					selectLines->S2->state = low;
					break;
		
		case 5:		selectLines->S0->state = high;
					selectLines->S1->state = low;	// 101
					selectLines->S2->state = high;
					break;
		
		case 6:		selectLines->S0->state = high;
					selectLines->S1->state = high;	// 110
					selectLines->S2->state = low;
					break;
		
		case 7:		selectLines->S0->state = high;
					selectLines->S1->state = high;	// 111
					selectLines->S2->state = high;
					break;
		
		default:	multiplexerSelectIndex = 0;
	}
}

/*
void mux_initialize(void)
{
	// TODO
}

void mux_2_1_Setup(MUX_2_1* mux, bool S0)
{
	     if (!S0) mux->out.state = mux->in0.state;
	else if ( S0) mux->out.state = mux->in1.state;
}

void mux_4_1_Setup(MUX_4_1* mux, bool S0, bool S1)
{
	     if (!S0 && !S1) mux->out.state = mux->in0.state;
	else if (!S0 &&  S1) mux->out.state = mux->in1.state;
	else if ( S0 && !S1) mux->out.state = mux->in2.state;
	else if ( S0 &&  S1) mux->out.state = mux->in3.state;
}

void mux_8_1_Setup(MUX_8_1* mux, bool S0, bool S1, bool S2)
{
	     if (!S0 && !S1 && !S2) mux->out.state = mux->in0.state;
	else if (!S0 && !S1 &&  S2) mux->out.state = mux->in1.state;
	else if (!S0 &&  S1 && !S2) mux->out.state = mux->in2.state;
	else if (!S0 &&  S1 &&  S2) mux->out.state = mux->in3.state;
	else if ( S0 && !S1 && !S2) mux->out.state = mux->in4.state;
	else if ( S0 && !S1 &&  S2) mux->out.state = mux->in5.state;
	else if ( S0 &&  S1 && !S2) mux->out.state = mux->in6.state;
	else if ( S0 &&  S1 &&  S2) mux->out.state = mux->in7.state;
}

void mux_1_2_Setup(MUX_1_2* mux, bool S0)
{
	if (!S0)
	{
		mux->out0.state = mux->in.state;
		mux->out1.state = low;
	}
	if (S0)
	{
		mux->out0.state = low;
		mux->out1.state = mux->in.state;
	}
}
*/


