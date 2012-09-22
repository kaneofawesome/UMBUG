#include "PLD2.h"

#define PLD2Bytes 2

void pld2_routine(void)
{
	//TODO:
	Byte bytesToSend[PLD2Bytes];
	
	if (getUARTState() == UART_CAMorSPEC)
	{	
		//we're in the middle of sending things.
		if (0 /*TODO: we've sent the whole image OR TODO: we have timed out*/)
		{
			setUARTState(UART_NOT_RESERVED); // unset the flag to say we are done with the UART
		}
	}
	else if (getUARTState() == UART_NOT_RESERVED && 0 /*TODO: enough time since last run*/)
	{
		setUARTState(UART_CAMorSPEC); //claim the UART
		Packetize(PKT_TARDIGRADEIMAGEMODE1, bytesToSend, PLD2Bytes); // start sending the data to the packetizer to be timestamped
	  
	}
}




