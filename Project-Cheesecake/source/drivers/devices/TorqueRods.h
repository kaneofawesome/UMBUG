#ifndef TORQUERODS_H
#define TORQUERODS_H

#include <msp430fg4618.h>
#include "../DriversConfig.h"
#include "./msp430/PWM.h"

//structures/////////////////////////////

typedef struct
{
	DigitalOutput* voltageOutput;
}
TorqueRod;


//methods/////////////////////////////////

void startTorqueRod(TorqueRod* torq);
void stopTorqueRod(TorqueRod* torq);



#endif /*TORQUERODS_H*/
