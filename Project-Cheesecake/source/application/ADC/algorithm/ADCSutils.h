/**
* ADCSutils.h
*
* Contains prototypes for utility functions needed in ADCS code
*
* Last updated: 2012-09-11
*/

// TODO: CHANGE DATA TYPES -- NO DOUBLES

#ifndef _ADCSUTILSH
#define _ADCSUTILSH

#include "../../../SimpleDefinitions.h"

void editHistory(SI16 var, SI16 *history, UI16 histSize);
SI16 deriv(SI16 *array, UI16 size, UI16 timeSinceEpoch);
SI16 integrate(SI16 *array, UI16 size, UI16 timeSinceEpoch);

#endif
