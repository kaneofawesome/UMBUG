
#include "Heater.h"

void startHeater(Heater* heater){
	setDigitalOutput(heater->voltageOutput);
}

void stopHeater(Heater* heater){
	clearDigitalOutput(heater->voltageOutput);
}




