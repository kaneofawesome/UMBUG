//////////////////////////////////////////////////////
//	Magnetometer										//
//	last edited by: Hossain Al Masroor				//
//	date: February1,2012							//
//													//
//////////////////////////////////////////////////////


#include "Magnetometer.h"

void magnetometerspiInitialize(Magnetometer* m )
{
	// TODO
	/*
	if (m->hardware.input.miso.state == high)
	{
		// do stuff
	}
	
	if(m->hardware.input.mosi.state==low)
	{
		//DO SOMETHING
	}
	if(m->hardware.transmitMessage.data[8])
	{
		//Do Something
	}
	if(m->hardware.input.clk.state==high)
	{
		//To Do
	}
	if(m->hardware.input.cs.state==low)
	{
		//To Do	
	}
	*/
	
}

void WriteByteSPI(Magnetometer* byte)
{
	//Load byte to data register
	//Wait for transmission to complete

}

void ReadByteSPI(Magnetometer* addr)
{
	//Load byte to data register
	//Wait for transmission to complete

}


UI16 ReadMagnetometerValue(){
	//TODO: rig up to framework however that needs to happen.
	UI16 value = 0x00;
	return value;
}

