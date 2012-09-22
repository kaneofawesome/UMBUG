#ifndef HEATER_H_
#define HEATER_H_

// includes ///////////////////////////////////

#include "../DriversConfig.h"

// structure //////////////////////////////////
typedef struct
{
	DigitalOutput* voltageOutput;
}
Heater;

void startHeater(Heater* heater);
void stopHeater(Heater* heater);

#endif /*HEATER_H_*/
