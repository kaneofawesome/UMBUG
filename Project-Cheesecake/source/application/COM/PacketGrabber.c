
#include "PacketGrabber.h"

//input
int ptrRead =0;
int ptrWrite =0;
UI8 masterInputBuffer[MASTER_BUFFER_SIZE];

//output
UI8* retrievedPacket;

//we expect to find a packet that looks like this
/*
 * Bytes		 1		7		  7		  1		1	  1		11	  2	  1
 * purpose		FLAG DESTINATION SOURCE CONTROL PID COMMAND ZEROS CRC FLAG
 * 
 */

//if a packet is found
//it returns 1 and places the packet in global array "retrievedPacket"
int findPacket(int* address)
{
	UI8 possiblePacket[MIN_RECIEVED_PACKET_SIZE];
	int foundPacket = 0;
	
	//printf("ptrRead = %d \n", ptrRead);
	//printf("byte1[ptrRead] = %x \n", masterInputBuffer[ptrRead]);
	//printf("byte2[ptrRead] = %x \n", masterInputBuffer[ptrRead+1]);
	
	int startingBitOfStartFlag = findAX25Flag(masterInputBuffer[ptrRead], masterInputBuffer[ptrRead+1], 0, 8);
	//printf("startingBitOfStartFlag = %d \n", startingBitOfStartFlag);
	int startingBitOfEndFlag =0;
	if(startingBitOfStartFlag >= 0)//found a start flag
	{
		//printf("found start flag\n");
		int i;
		for(i=MIN_RECIEVED_PACKET_SIZE+1; i<=MAX_RECIEVED_PACKET_SIZE+1; i++)//for each possible end flag location
		{
			if(i == MIN_RECIEVED_PACKET_SIZE+1)
			{//jump ahead and start
				startingBitOfEndFlag = findAX25Flag(masterInputBuffer[ptrRead+i], masterInputBuffer[ptrRead+i+1], startingBitOfStartFlag, 8);
			}else if (i == MAX_RECIEVED_PACKET_SIZE+1)
			{//stop early
				startingBitOfEndFlag = findAX25Flag(masterInputBuffer[ptrRead+i], masterInputBuffer[ptrRead+i+1], 0, startingBitOfStartFlag+1);
			}else
			{//checking bytes in middle, therefore check all bits
				startingBitOfEndFlag = findAX25Flag(masterInputBuffer[ptrRead+i], masterInputBuffer[ptrRead+i+1], 0, 8);
			}
			
			if(startingBitOfEndFlag >= 0)//found both flags
			{
				//remove bit stuffing from the contents between the flags
				printf("got Flags!\n");
				if(removeBitStuffing(ptrRead+1, startingBitOfStartFlag, i-1, startingBitOfEndFlag, possiblePacket))
				{//removeBitSutffing == true if it removed zeros and found a proper length packet
					//check the CRC
					if(checkCRC(possiblePacket))
					{
						//check to see if the packet was from or gnd station and for our satellite
						if(checkAddresses(possiblePacket))
						{
							//got a packet
							retrievedPacket = possiblePacket;
							foundPacket = true;
							ptrRead += i;
						}
					}
				}
			}
		}
	}else//didn't find a start flag
	{
		ptrRead++;
	}
	
	return foundPacket;
}

bool AcquiredNewData(void)
{	//return true if there is enough new data to find a packet in
	return ((ptrRead + MAX_RECIEVED_PACKET_SIZE)<= ptrWrite) || ((ptrRead > ptrWrite) && (MASTER_BUFFER_SIZE - ptrRead + ptrWrite >= MAX_RECIEVED_PACKET_SIZE));
}

int findAX25Flag(UI8 byte1, UI8 byte2, int startingPosition, int endPosition)
{
	//create 16bit holder for the data
	UI16 data = (((UI16)byte1)<<8) + (UI16)byte2;
	//16 bit mask to be shifted
	UI16 mask = 0xFF00>>startingPosition;
	//16bit flag comparator
	UI16 flag = 0x7E00>>startingPosition;
	
	int i;
	for(i = startingPosition; i<endPosition; i++)//for all bits in byte1 up to the end position which is usually 8
	{
		
		if((UI16)(data&mask) == (UI16)flag)//found a flag
		{
			return i;//return start position of the flag byte
		}
		mask = mask>>1;
		flag = flag>>1;
	}
	return -1;//return nothing found error
}

bool removeBitStuffing(int firstByte, int firstStartBit, int secondByte, int secondStartBit, UI8* unstuffedPacket)
{
	//remove the stuffed zeroes from the data and place the data into unstuffedPacket
	int oneCount = 0;//count to 5 and remove the next zero
	int bitLength = 0;//must end up exactly packetSize*8 to return true
	
	int byteInOutput = 0;
	int bitInOutput = 0;
	
	int currentByte = firstByte;
	int currentBit = firstStartBit-1;
	
	int targetByte = (secondStartBit==0) ? secondByte : (secondByte+1);
	int targetBit = (secondStartBit==0) ? 7 : (secondStartBit-1);
	
	//printf("targetByte = %d \n", targetByte);
	//printf("targetBit = %d \n", targetBit);
	
	do//count and remove stuffed zeros
	{
		
		if(currentBit==7)
		{
			currentBit =0;
			currentByte++;	
		}else
		{
			currentBit++;
		}
		
		//printf("masterInputBuffer[currentByte] %x \n", masterInputBuffer[currentByte]);
		//printf("0x80>>currentBit %x \n", (0x80>>currentBit));
		//printf("masterInputBuffer[currentByte]&(0x80>>currentBit) = %x \n", masterInputBuffer[currentByte]&(0x80>>currentBit));
		if((UI8)(masterInputBuffer[currentByte]&(0x80>>currentBit)) == (UI8)(0x80>>currentBit))
		{//its a one
			//printf("its a one \n");
			oneCount++;
			//printf("oneCount = %d\n", oneCount);
			if(oneCount==5)
			{//skip to the next bit
				oneCount = 0;
				if(currentBit==7)
				{
					currentBit =0;
					currentByte++;	
				}else
				{
					currentBit++;
				}				
			}

			unstuffedPacket[byteInOutput] |= 0x80>>bitInOutput;
			//printf("printing a 1 at byte %d, bit %d \n", byteInOutput, bitInOutput);
			bitLength++;
			if(bitInOutput==7)
			{
				bitInOutput=0;
				byteInOutput++;
			}else
			{
				bitInOutput++;
			}
			
		}else
		{//its a zero
			//printf("its a zero \n");
			oneCount = 0;
			unstuffedPacket[byteInOutput] &= ~(0x80>>bitInOutput);
			bitLength++;
			if(bitInOutput==7)
			{
				bitInOutput=0;
				byteInOutput++;
			}else
			{
				bitInOutput++;
			}
		}
		

		
	}while(!(currentByte == targetByte && currentBit == targetBit));
	
	return (bitLength == (MIN_RECIEVED_PACKET_SIZE*8));
	
}

bool checkCRC(UI8* data)
{
	UI16 packetCRC = ((UI16)data[16])<<8 + (UI16)data[17];
	UI16 calculatedCRC = make_crc16(data, MIN_RECIEVED_PACKET_SIZE-4, 3);//CRC the packet minus the flags and the FCS
	return (packetCRC == calculatedCRC);
}

bool checkAddresses(UI8* data)
{
	return (data[0] == DEST_BYTE_1 && data[1] == DEST_BYTE_2 && data[2] == DEST_BYTE_3 && data[3] == DEST_BYTE_4 
			&& data[4] == DEST_BYTE_5 && data[5] == DEST_BYTE_6 && data[6] == DEST_BYTE_7 && data[7] == SRC_BYTE_1
			&& data[8] == SRC_BYTE_2 && data[9] == SRC_BYTE_3 && data[10] == SRC_BYTE_4 && data[11] == SRC_BYTE_5
			&& data[12] == SRC_BYTE_6  && data[13] == SRC_BYTE_7);
}

