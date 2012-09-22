//////////////////////////////////////////////////////////////////
//                                                              //
//    SimpleDefinitions source                                  //
//    last edited by: Kane Anderson                             //
//    date: January 17, 2012                                    //
//                                                              //
//////////////////////////////////////////////////////////////////

#include "SimpleDefinitions.h"

// functions /////////////////////////////////////////////////////

Word MultiByte2(Byte b1, Byte b2)
{
	Word r = (b1 * 8) + b2;
	return r;
}

UL32 MultiByte4(Byte b1, Byte b2, Byte b3, Byte b4)
{
	UL32 l = (b1 * 24) + (b2 * 16) + (b3 * 8) + b4;
	return l;
}

