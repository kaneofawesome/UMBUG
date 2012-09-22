//////////////////////////////////////////////////////////////////
//                                                              //
//    Thermocouple header                                     	//
//    last edited by: Kane Anderson                             //
//    date: January 10, 2012                                    //
//                                                              //
//////////////////////////////////////////////////////////////////

#ifndef THERMOCOUPLE_H
#define THERMOCOUPLE_H

// includes ///////////////////////////////////

#include "../DriversConfig.h"

// definition /////////////////////////////////

// this is 9.842 kiloOhms
#define ThermocouplePullUpResistor		9842
#define RoomTemperature_Kelvin_x100		29815
#define Denominator_A_x1000000			3354
#define Denominator_B_x1000000			2958

// structure //////////////////////////////////
typedef struct
{
	AnalogInput* voltageInput;
	
	DegreesCelsius temperature;
}
Thermocouple;

// functions //////////////////////////////////

void thermocouple_initialize(Thermocouple* thermocouple);
Word thermocouple_read(Thermocouple* thermocouple);
double rawA2DToDegreesCelsius(double rawVolts);

#endif
