#include "ADCS.h"

#define ADCSBytes 36
bool currentlyTorquing = false;

void sendADCSToPacketizer(UI16 TorqX1, UI16 TorqX2, UI16 TorqX3, UI16 TorqX4, UI16 TorqX5, UI16 TorqX6, UI16 TorqY1, UI16 TorqY2, UI16 TorqY3, UI16 TorqY4, UI16 TorqY5, UI16 TorqY6, UI16 TorqZ1, UI16 TorqZ2, UI16 TorqZ3, UI16 TorqZ4, UI16 TorqZ5, UI16 TorqZ6)
{
	//TODO: make bigger to collect the actually-necessary information as well (sun sensors (photodiodes), magnetometer value)
	Byte bytesToSend[ADCSBytes];
	
	bytesToSend[0] = (int)((TorqX1 >> 8) & 0xFF);
	bytesToSend[1] = (int)(TorqX1 & 0xFF);
	bytesToSend[2] = (int)((TorqX2 >> 8) & 0xFF);
	bytesToSend[3] = (int)(TorqX2 & 0xFF);
	bytesToSend[4] = (int)((TorqX3 >> 8) & 0xFF);
	bytesToSend[5] = (int)(TorqX3 & 0xFF);
	bytesToSend[6] = (int)((TorqX4 >> 8) & 0xFF);
	bytesToSend[7] = (int)(TorqX4 & 0xFF);
	bytesToSend[8] = (int)((TorqX5 >> 8) & 0xFF);
	bytesToSend[9] = (int)(TorqX5 & 0xFF);
	bytesToSend[10] = (int)((TorqX6 >> 8) & 0xFF);
	bytesToSend[11] = (int)(TorqX6 & 0xFF);
	bytesToSend[12] = (int)((TorqY1 >> 8) & 0xFF);
	bytesToSend[13] = (int)(TorqY1 & 0xFF);
	bytesToSend[14] = (int)((TorqY2 >> 8) & 0xFF);
	bytesToSend[15] = (int)(TorqY2 & 0xFF);
	bytesToSend[16] = (int)((TorqY3 >> 8) & 0xFF);
	bytesToSend[17] = (int)(TorqY3 & 0xFF);
	bytesToSend[18] = (int)((TorqY4 >> 8) & 0xFF);
	bytesToSend[19] = (int)(TorqY4 & 0xFF);
	bytesToSend[20] = (int)((TorqY5 >> 8) & 0xFF);
	bytesToSend[21] = (int)(TorqY5 & 0xFF);
	bytesToSend[22] = (int)((TorqY6 >> 8) & 0xFF);
	bytesToSend[23] = (int)(TorqY6 & 0xFF);
	bytesToSend[24] = (int)((TorqZ1 >> 8) & 0xFF);
	bytesToSend[25] = (int)(TorqZ1 & 0xFF);
	bytesToSend[26] = (int)((TorqZ2 >> 8) & 0xFF);
	bytesToSend[27] = (int)(TorqZ2 & 0xFF);
	bytesToSend[28] = (int)((TorqZ3 >> 8) & 0xFF);
	bytesToSend[29] = (int)(TorqZ3 & 0xFF);
	bytesToSend[30] = (int)((TorqZ4 >> 8) & 0xFF);
	bytesToSend[31] = (int)(TorqZ4 & 0xFF);
	bytesToSend[32] = (int)((TorqZ5 >> 8) & 0xFF);
	bytesToSend[33] = (int)(TorqZ5 & 0xFF);
	bytesToSend[34] = (int)((TorqZ6 >> 8) & 0xFF);
	bytesToSend[35] = (int)(TorqZ6 & 0xFF);
	
	Packetize(PKT_ADCSREADINGS, bytesToSend, ADCSBytes);
}

void adcs_routine(void){
	//This is the routine which will run during normal operations
	//  to keep the satellite pointing correctly.
	
	if (currentlyTorquing){
		if(0 /*enough torquing has happened*/){
			currentlyTorquing = false;
		}
	}
  
	if (0 /*TODO: enough time has passed since the last time we ran*/){
		//TODO: stop all torquers
		
		//TODO: collect necessary information from magnetometer and sun-sensors (photodiodes).
		
		//TODO: run algorithm to see if we need to torque, and in which manner.
		
		//TODO: start torquing necessary torquers
		
		//TODO: collect extra data from the system
		if (getUARTState() == UART_NOT_RESERVED){
			// TODO: send proper data to COM
			sendADCSToPacketizer(0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); // send the data to the packetizer to be timestamped and sent to COM processor
		}
	}
}

void adcs_LEOP(void){
	//TODO: This is the routine which runs right after launch
	//      to get the satellite out of a tumble. (B-DOT)
}



