//////////////////////////////////////////////////////////////////
//                                                              //
//    Spectrometer header                                      	//
//    last edited by: Kane Anderson                             //
//    date: January 12, 2012 									//
//	  edited last by : Hossain Al Masroor                       //
//                                                              //
//////////////////////////////////////////////////////////////////

#ifndef SPECTROMETER_H
#define SPECTROMETER_H

#include <msp430fg4618.h>
#include "../DriversConfig.h"

///////////////////////////////////////////////

// structure //////////////////////////////////
typedef struct
{
	// just guessing 8 bytes... not sure
	// I changed it to 16 bytes ...ham
	volatile Byte byte[16]; //the video signal coming out of the spectrometer is fed 
							//to ADC, The data is 16 bytes.If data is defined 
							//here then do we need to consider creating a separate 
							//video signal in the spectrometer struct?
	// TODO use the SD card
	// spectrometrydata sd[512];//to store data in ana rray and average the video data 
	UI16 index;
}
SpectrometryData;

typedef struct
{
	bool oldClockState;
	bool newClockState;
	
	UI16 currentIndexOfVideoCapture;
	
	DigitalOutput* clk; //lets say it is 800 khz READ uP datasheet to generate clock of 800 kHz do not forget to check the msp430 tutorial by Dario
	DigitalOutput* gain; //input to the spectrometer
	DigitalOutput* strtpulse; //input to the spectrometer
	DigitalOutput* eos; //end of scan channel, output from the spectrometer
	AnalogInput* video; //video rate 300 khz, output from the spectrometer
	DigitalOutput* trigger; //I am not sure how to use the trigger for the spectrometer Please see page 7 of Hamamtsu...Spectrometer.pdf
	
	SpectrometryData data;//
}
Spectrometer;


// functions //////////////////////////////////

void spectrometer_initialize(Spectrometer* spectrometer);
void spectrometer_startVideo(Spectrometer* spectrometer);
void spectrometer_endStartPulse(Spectrometer* spectrometer);
void spectrometer_wait_1clock_cycle(Spectrometer* spectrometer);
void spectrometer_wait_2clock_cycle(Spectrometer* spectrometer);
void takePicture(Spectrometer* spectrometer);

#endif
