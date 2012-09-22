
#include "./BDOT.h"

#if CDH_PROCESSOR_COMPILE
	
	void BDOT_getTorquerMoment(/*SI16 phi, SI16 theta, SI16 psi, SI16* histPhi, SI16* histTheta, SI16* histPsi, UI16 timeSinceEpoch*/)
	{
		SI16 gain = -1;
		
		// B Field in spacecraft frame
		SI16 magnetometerXAxisNanoTeslas = getXAxisMagnetometerReading(&devices.magnetometer);
		SI16 magnetometerYAxisNanoTeslas = getYAxisMagnetometerReading(&devices.magnetometer);
		SI16 magnetometerZAxisNanoTeslas = getZAxisMagnetometerReading(&devices.magnetometer);
		
		// Temporary
		setTorqueRodMoment(&devices.torqueRods, gain*magnetometerXAxisNanoTeslas, TorquerAxis_X);
		setTorqueRodMoment(&devices.torqueRods, gain*magnetometerYAxisNanoTeslas, TorquerAxis_Y);
		setTorqueRodMoment(&devices.torqueRods, gain*magnetometerZAxisNanoTeslas, TorquerAxis_Z);
	}
	
#endif
