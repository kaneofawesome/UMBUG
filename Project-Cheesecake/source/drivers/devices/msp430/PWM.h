// file header

#ifndef PWM_H
#define PWM_H

// includes //////////////////////////////////////////
#include "../../DriversConfig.h"

typedef struct
{
	DigitalOutput rod1;
	DigitalOutput rod2;
	DigitalOutput rod3;
	DigitalOutput rod4;
	DigitalOutput rod5;
	DigitalOutput rod6;
}
PWMOut;

#endif
