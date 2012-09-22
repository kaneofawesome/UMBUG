//////////////////////////////////////////////////////////////
//															//
//		generates a tone									//
//		Kane Anderson										//
//		07/29/2012											//
//															//
//////////////////////////////////////////////////////////////

// includes //////////////////////////////////////////////////
#include "./Tone.h"

// found from SINE_LENGTH / 360 = 4800 / 360 = 13
const UI16 ToneIndexPositionsPerDegreePhase = 13;

Word getToneValueAt(UI16 time)
{
	if (time >= SINE_LENGTH)
	{
		return 9999;
	}
	else
	{
		return sineArray[time];
	}
}

