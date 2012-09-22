//////////////////////////////////////////////////////////////////
//                                                              //
//    CDHApplication header                                     //
//    last edited by: Kane Anderson                             //
//    date: January 16, 2012                                    //
//                                                              //
//////////////////////////////////////////////////////////////////

#ifndef CDHAPPLICATION_H
#define CDHAPPLICATION_H

//////////////////////////////////////////////////////////////////

#include "../ApplicationConfig.h"
#include "../../system/System.h"
#include "../../system/Log.h"
#include "../THM/THM.h"

typedef enum
{
	// This is a list of every possible type of packet
	PKT_THERMAL_READINGS, //There is only one, and it's for the Tardigrade chamber
	PKT_SPECTROMETERMODE1, //low resolution; more frequent
	PKT_SPECTROMETERMODE2, //higher resolution; less frequent
	PKT_TARDIGRADEIMAGEMODE1, //low resolution; more frequent
	PKT_TARDIGRADEIMAGEMODE2, //higher resolution; less frequent
	PKT_CAMERAHIST,
	PKT_ADCSREADINGS, // there are 12 sun sensors, and measurements for the torque rods
	PKT_ADCSALGORITHM, //which one is currently running B-dot and sun-pointing
	PKT_PEEKDATA, //check the table of values
	PKT_CDHUPKEEP, //processor load %, micro temp, memory use, watchdog counts
	PKT_COMUPKEEP, //watchdog timeouts, received callsigns, memory use RX, memory use TX
	PKT_COMMANDCONFIRMED, //to confirm sent packets (maybe COM processor is on control of this?
	PKT_ANTENNADEPLOYCONFIRM, //if the antenna has successfully deployed
	PKT_TARDIGRADEONOFF,
	PKT_SPECTROMETERONOFF,
	PKT_PHASE, //one of 6 mission phases (did we open the valve, etc. purely for the tardigrade experiment)
	PKT_BATTERYSTATE,
	PKT_SMARTSWITCHSTATE, //"The switch does something funky that needs to be filled in later" ????
	PKT_OPERATIONMODE, //The operation mode of the satellite (different from phase?)
	PKT_HEATERSTATUS //Are we storing this ??? (not priority)
}
PacketType; //This is an AX.25 packet


void CDH_timerA_ISR(void);

void CDH_application_main(void);
void CDHMainScheduleLoop(void);
void Packetize(PacketType type, Byte* dataBytes, int length);
void CheckForTimeTaggedCommands(void);
void CheckForTimeTaggedCommands(void);
void SetModeSwitch(double howFarInTheFutureInSeconds, int whichMode);

#endif
