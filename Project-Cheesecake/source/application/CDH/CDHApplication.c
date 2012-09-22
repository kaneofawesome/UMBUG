//////////////////////////////////////////////////////////////////
//                                                              //
//    CDHApplication header                                     //
//    last edited by: Kane Anderson                             //
//    date: January 16, 2012                                    //
//                                                              //
//////////////////////////////////////////////////////////////////

#include "CDHApplication.h"

bool newTimeTaggedCommand = false;
int modeToSwitchTo = 0; // the value of this currently affects nothing.
double howFarInTheFutureToSwitchToNewModeInSeconds = 0;
double whenWeStarted = 0;


///////////////////////////////////////////////////////////////////

void CDH_timerA_ISR(void)
{
	kickTheDog(&devices.systemWatchdog);
}

///////////////////////////////////////////////////////////////////

void CDH_InterpretGroundCommand(Byte* dataBytes){
	//TODO: This will interpret the ground commands and do things thusly. Most of them will probably just change 
	//      global variables so that different things happen when the applications are run.
	
	//This should be run from an interrupt ?????????
	
	//List of ground commands to run:
	//- switch out of LEOP into waiting mode (swap schedules)
 	//- switch out of waiting mode into PLD1 (swap schedules)
 	//- open/close valve 1 (full command)
 	//- open/close valve 2 (full command)
 	//- switch out of PLD1 into PLD2 (swap schedules)
 	//- Send requested table of values values to ground (full command)
 	//- Set values in the table of values (change variable)
 	//- Query present ADCS information and collect it. (immediate command) (change varaible)
 	//- Switch from burst mode to once-per-day mode for the spectrometer (change variable)
 	//- Switch from high resolution once-per-day mode to frequent low resolution mode (change variable)
}

void CDH_application_main(void)
{
	// TODO: This will be where the scheduler is started, and before that, the timer to 
	
	// TODO: make a mock-up schedule along with its datastructure.
	//       - don't forget about function pointers. Those will be important.
	// TODO: start the hardware interrupt timer for the next thing that needs to run from scheduler
	//       - use CommandTimerFacade's setTimer() command.
	//       - also use LimitTimerFacade's setTimer() command to set the time limit for the current command (send ground an error if we go over the limit).
	
	logLine("CDH scheduler initialized");
	
	CDHMainScheduleLoop();
}

void CDHMainScheduleLoop(void)
{
	// TODO: write the always-running loop here which gathers and runs commands from the ground and gets interrupted by the schedule.
	//       - make a data structure which holds commands (Maybe function pointers and parameters somehow? Maybe just packets which will be parsed later?)
	
	//testing ADC stuff
	
	//int adcreading = 0;
		
	for(;;)
	{
		kickTheDog(&devices.systemWatchdog);
		
		// read the current time (second precision)
		realTimeClock_update(&devices.realTimeClock);
		
		
		bool oneSecondHasPassed = (devices.realTimeClock.currentTime.seconds > systemTime.seconds);
		bool oneMinuteHasPassed = (devices.realTimeClock.currentTime.minutes > systemTime.minutes);
		bool oneHourHasPassed	= (devices.realTimeClock.currentTime.hours   > systemTime.hours);
		bool oneDayHasPassed	= (devices.realTimeClock.currentTime.date    > systemTime.date);
		
		if (oneSecondHasPassed)
		{
			systemTime.seconds	= devices.realTimeClock.currentTime.seconds;
			
			toggleStatusLED();
		}
		if (oneMinuteHasPassed)
		{
			systemTime.minutes	= devices.realTimeClock.currentTime.minutes;
			
		}
		if (oneHourHasPassed)
		{
			systemTime.hours	= devices.realTimeClock.currentTime.hours;
			
		}
		if (oneDayHasPassed)
		{
			systemTime.date		= devices.realTimeClock.currentTime.date;
			systemTime.month	= devices.realTimeClock.currentTime.month;
			systemTime.year		= devices.realTimeClock.currentTime.year;
			
		}
		
		//THM_application_main();
	
		//Freeze, criminal! >:|
		
		//List of function pointers:
		//float (*pt3Func)(float, float); // TODO: something like this...http://www.newty.de/fpt/intro.html
		// TODO: List of time limits for those functions:
		// TODO: List of time between those functions:
		
		//TODO: set time-out timer (limittimerfacade)
		//TODO: start next process in the list (make a list first of function pointers)
		//pt2Func(a, b); // TODO: Something like this...http://www.newty.de/fpt/intro.html
		
	}
	
}


void Packetize(PacketType type, Byte* dataBytes, int length)
{
	//Packet newPkt;
	
	//TODO: set this up properly!
	
	//SPI_transmitStream(SPI_Device* device, const Byte* data, UI8 length)
}

void CheckForTimeTaggedCommands(void){
	//Currently, this just looks for the command to switch between modes.
	//these modes are stored in the eeprom (so that when the processor restarts, we'll be in the right mode still
	
	double currentTimeReadFromRTC;
	
	if (newTimeTaggedCommand){
		realTimeClock_update(&devices.realTimeClock);
		currentTimeReadFromRTC =  ((int)(&devices.realTimeClock.currentTime.seconds) * 60) + (int)(&devices.realTimeClock.currentTime.minutes);
		if (currentTimeReadFromRTC >= whenWeStarted){
			// TODO: switch between modes.
			// switchModes(whichMode);
			
			newTimeTaggedCommand = false;
		}
	}
}

void SetModeSwitch(double howFarInTheFutureInSeconds, int whichMode){
	modeToSwitchTo = whichMode; // the value of this currently affects nothing.
	howFarInTheFutureToSwitchToNewModeInSeconds = howFarInTheFutureInSeconds;
	newTimeTaggedCommand = true;
	
	realTimeClock_update(&devices.realTimeClock);
	whenWeStarted =  ((int)(&devices.realTimeClock.currentTime.seconds) * 60) + (int)(&devices.realTimeClock.currentTime.minutes);
}








