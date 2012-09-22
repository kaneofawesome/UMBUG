#include "TorqueRods.h"


void startTorqueRod(TorqueRod* torq){
	setDigitalOutput(torq->voltageOutput);
}

void stopTorqueRod(TorqueRod* torq){
	clearDigitalOutput(torq->voltageOutput);
}
