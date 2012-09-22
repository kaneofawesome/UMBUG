#include "PLD1.h"

#define PLD1Bytes 2

void pld1_routine(void)
{
	int lengthOfCameraData = 0;
	
	if (getUARTState() == UART_NOT_RESERVED && 1/*TODO: enough time since last run*/)
	{
		//Get COM ready to receive the data
		initializeDataToCOMOverSPI(lengthOfCameraData);
		
		//Tell the camera we want to start receiving images
		//TODO: hit the mux to tell the uart that we want to talk to the camera
		
		// disable the HiRes Frame Differencing
		sendUARTData(0x48); //'H'
		sendUARTData(0x44); //'D'
		sendUARTData(0x20); //' '
		sendUARTData(0x30); //'0'
		sendUARTData(0x0D); //'\r'
		
		// enable HiRes mode (NOT FOR TESTING!)
		//sendUARTData(0x00); //'H'
		//sendUARTData(0x00); //'R'
		//sendUARTData(0x00); //' '
		//sendUARTData(0x00); //'1'
		//sendUARTData(0x00); //'\r'
		
		//Get ready to flood the data on through to COM
		sendUARTDataToCOMOverSPI(lengthOfCameraData); // TODO: put this after the next block ???
		
		// take a picture
		sendUARTData(0x53); //'S'
		sendUARTData(0x46); //'F'
		sendUARTData(0x0D); //'\r'
	}
}




