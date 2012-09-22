//////////////////////////////////////////////////////////////////
//                                                              //
//    Packet header                                             //
//    last edited by: Kane Anderson                             //
//    date: January 17, 2012                                    //
//                                                              //
//////////////////////////////////////////////////////////////////

#ifndef PACKET_H
#define PACKET_H

#include "System.h"

//Structures///////////////////////////////////////////
typedef struct
{
	char *index;
	unsigned int size;
}
Packet; //This is an AX.25 packet

typedef struct
{
	bool type;// info==true, command==false
	char *index;//contents
	//if info data
	//The first byte of the info array will contain the layout key for the array
	//This will differentiate the different types of info packets
	//if command data
	//TODO
	unsigned int size;//size
}
Data; //This is a chunk of information to be stuffed into, or taken out of, a packet

#endif
