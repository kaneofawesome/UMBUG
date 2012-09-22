//////////////////////////////////////////////////////////////////
//                                                              //
//    Spectrometer source                                      	//
//    last edited by: Kane Anderson                             //
//    date: January 22, 2012                                    //
//                                                              //
//////////////////////////////////////////////////////////////////

#include "Spectrometer.h"

//declarations/////////////////////////////////


// functions //////////////////////////////////

void spectrometer_initialize(Spectrometer* spectrometer)
{
	// TODO
}

void spectrometerClk(Spectrometer* spectrometer)
{
	// Set the frequency of the clock 
	// TODO use whatever clock is available... maybe ACLK or similar.
	//spectrometer     = 800; //Set Spectrometer clock to be 800 MHz
							//Timers from the microprocessor may need to be used for this function
							//Since I do not know how to use this properly I wont worry about it AT PRESENT
		
}
void spectrometer_endStartPulse(Spectrometer* spectrometer)
{
	spectrometer->strtpulse->state = low;
}

void spectrometer_wait_1clock_cycle(Spectrometer* spectrometer)
{
	// wait for one clock cycle
	//HOW TO WAIT FOR ONE CLOCK CYCLE?
	//spectrometer-> 	
}
	
	void spectrometer_wait_half_clock_cycle(Spectrometer* spectrometer){
	//wait for one clock cycle
	//HOW TO WAIT FOR HALF CLOCK CYCLE?
	//spectrometer->	
	}
void startVideo(Spectrometer* spectrometer)
{
	static long memoryLocationIndex = 0x3000;
	
	spectrometer->oldClockState = spectrometer->newClockState;
	spectrometer->newClockState = spectrometer->clk->state;
	bool negativeEdgeOnClockOccurred = ((spectrometer->oldClockState == high) && (spectrometer->newClockState == low));
	bool positiveEdgeOnClockOccurred = ((spectrometer->oldClockState == low) && (spectrometer->newClockState == high));
	
	//Sequence Of Operation 1
	spectrometer->strtpulse->state=low;
	if(negativeEdgeOnClockOccurred){
		spectrometer->strtpulse->state=high;
	}
	spectrometer_wait_1clock_cycle(spectrometer);	
	takePicture(spectrometer);
	spectrometer_wait_1clock_cycle(spectrometer);
	spectrometer_wait_half_clock_cycle(spectrometer);
	spectrometer->trigger->state = low;
	spectrometer_wait_half_clock_cycle(spectrometer);
	spectrometer->trigger->state = high;
	spectrometer_wait_2clock_cycle(spectrometer);
	
	
	if(positiveEdgeOnClockOccurred){
		spectrometer_wait_1clock_cycle(spectrometer);
		if(negativeEdgeOnClockOccurred){
			spectrometer->trigger->state = low;
		}
		
	}
	spectrometer_wait_1clock_cycle(spectrometer);
		
	spectrometer->strtpulse->state = high;
	// TODO 
	// add functionality for using the SD card
	//sd [memoryLocationIndex] = spectrometer1.video;// does this make sense? 
	
	memoryLocationIndex += 0x01;	// to the next byte

}
void end_of_Sequence(Spectrometer* spectrometer)
{
	spectrometer->eos->state = low;
}

void spectrometer_trigger(Spectrometer* spectrometer)
{
	spectrometer->trigger->state = low;
}


void spectrometer_wait_2clock_cycle(Spectrometer* spectrometer)
{
	// wait for 2 clock cycles
	//HOW TO WAIT FOR TWO CLOCK CYCLES?
	
}
void takePicture(Spectrometer* spectrometer){

	// set ST pin on A2D chip on
	// do a quick low pulse
	spectrometer->strtpulse->state = low;
	clearDigitalOutput(spectrometer->strtpulse);
	int wait = 0;
	for (wait = 0; wait < 10; wait++){;}			// twiddle thumbs
	spectrometer->strtpulse->state = high;
	setDigitalOutput(spectrometer->strtpulse);
	
	//if (spectrometer.strtpulse == low)
	//{
		// wait for one clock cycle
		//HOW TO WAIT FOR ONE CLOCK CYCLE?
	
		// start inputing video data to the microprocesor 
			// capture the current analog value
			
			spectrometer->data.byte[spectrometer->currentIndexOfVideoCapture] = (Byte) spectrometer->video->value;
			spectrometer->currentIndexOfVideoCapture++;
			
		// wait for one clock cycle
		//HOW TO WAIT FOR ONE CLOCK CYCLE?
	
		//pull trigger signal low
		spectrometer->trigger = low;
	
	// read in data however that happens for this chip (SPI?)
	
	//}
	
	
	
}
void stopPicture(Spectrometer* spectrometer){
	//	TODO
	//stop taking pictures
}
	
void ccdReset(void)
{
	// TODO
}

