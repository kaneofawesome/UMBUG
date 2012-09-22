//////////////////////////////////////////////////////////////////
//                                                              //
//    Binary coded decimal 		      	                       	//
//    last edited by: Kane Anderson                             //
//    date: 03/08/2012      	                            	//
//                                                              //
//////////////////////////////////////////////////////////////////

// includes //////////////////////////////////////////////////////

#include "../system/BinaryCodedDecimal.h"

// functions /////////////////////////////////////////////////////

BCD_Value convertDecimalToBinaryCodedDecimal(UI8 input)
{
	if (input <= 9)
	{
		return input;
	}
	if (input > 99)
	{
		return 0; // error
	}
	
	UI8 result = 0;
	result	+= (UI8) (input % 10);
	result	+= (UI8) ((input / 10) % 10) << 4;
	
	return result;
}
