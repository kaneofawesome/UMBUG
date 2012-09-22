
/*
 * This class represents the scheduler
 * Only one of these should exist unless multiple processors are introduced.
 * In this respect it could be beneficial to use the singleton pattern.  However this may add complexity as well.
 * 
 * It should have functions to get the current time, or a fucntion that the RTC interrupt calls to increment the time.
 * 
 * Needs list of routine operations, as well as ground commands
 * 
*/
#include "TimeCounter.h"
#include "Task.h"
#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#endif /*SCHEDULER_H_*/


typedef struct{
	
	TimeCounter currentTime;
	//Task *tasks;
	//Task *currentTask;
	
	
} Scheduler;

void initScheduler(Scheduler *a);
void initTimers();

