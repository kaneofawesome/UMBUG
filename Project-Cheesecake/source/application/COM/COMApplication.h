//////////////////////////////////////////////////////////////////
//                                                              //
//    CDHApplication header                                     //
//    last edited by: Kane Anderson                             //
//    date: January 16, 2012                                    //
//                                                              //
//////////////////////////////////////////////////////////////////

#ifndef COMAPPLICATION_H
#define COMAPPLICATION_H

#if COM_PROCESSOR_COMPILE
	
	#include "../ApplicationConfig.h"
	#include "../../system/System.h"
	#include "../../system/Log.h"
	#include "../../drivers/devices/msp430/TimerA.h"
	#include "../COM/Tone.h"
	#include "../COM/PSK.h"
	#include "../COM/PacketGrabber.h"
	
	void COM_timerA_ISR(void);
	void COM_timerA2_ISR(void);
	
	void COM_application_main(void);
	void COMMainScheduleLoop(void);
	void runRadio(void);
	void listen(void);

#endif
#endif
