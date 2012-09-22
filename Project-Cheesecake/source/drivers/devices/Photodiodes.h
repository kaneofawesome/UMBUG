//////////////////////////////////////////////
//	Photodiodes Header File					//
//	last edited by:Hossain Al Masroor		//
//	date: February 1, 2012					//
//											//
//////////////////////////////////////////////


#ifndef PHOTODIODES_H
#define PHOTODIODES_H

#include <msp430fg4618.h>
#include "../DriversConfig.h"

//structures////////////////////////////////


typedef struct
{
	Word pin;
	Milliamps current;
}
Photodiode;

//methods//////
void readPhotodiode(Photodiode* p);

#endif /*PHOTODIODES_H*/
