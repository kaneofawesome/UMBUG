//////////////////////////////////////////////////////////////////
//                                                              //
//    PSK header                                                //
//    last edited by: Tong Duan                                 //
//    date: July 10, 2012                                       //
//                                                              //
//////////////////////////////////////////////////////////////////

#ifndef PSK_H
#define PSK_H

#include "../../system/Packet.h"//includes the Packet struct
#include "../../drivers/IOTypes.h"//includes the IOType struct
#include "../COM/Tone.h"

#define M_PSK 32

extern const Word phaseAngles[M_PSK];

#define PhaseShiftHistoryLength 8		// chosen because 64 / (8/5) = 40

void convertBinaryToPSK(Byte data[], int size);
UI8 phaseChange(int digital[]);
void initializePSKBuffer();

extern UI8 currentPhaseShiftIndex;
extern UI8 phaseShifts[PhaseShiftHistoryLength];

#endif
