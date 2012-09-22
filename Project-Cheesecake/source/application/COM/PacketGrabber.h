#ifndef PACKETGRABBER_H_
#define PACKETGRABBER_H_

/*
 * This method grabs packets out of two arrays that hold the incoming bits from the radio
 * and returns a pointer to the packet
 * 
 * It basically finds start and end flags and checks the source address to be from our ground station
 * returns a 1 if a packet was found, 0 if no packet found
 * 
 * 
 *	   AX25 Packet
 * 		^	   ^
 * 		|	   |
 *   masterInputBuffer <- 1Byte at a time from radio listening interrupt
 * 
 */
#include "../../drivers/IOTypes.h"//includes the IOType struct
#include "../../drivers/devices/msp430/NickTianSPI/crc.h"
#include <stdio.h>

#define MAX_RECIEVED_PACKET_SIZE 10//39//(32 + 7) = 120%
#define MIN_RECIEVED_PACKET_SIZE 8//32
#define MASTER_BUFFER_SIZE 128 //TODO change to 256
#define DEST_BYTE_1 0x01
#define DEST_BYTE_2 0x00
#define DEST_BYTE_3 0x00
#define DEST_BYTE_4 0x00
#define DEST_BYTE_5 0x00
#define DEST_BYTE_6 0x00
#define DEST_BYTE_7 0x00
#define SRC_BYTE_1 0x02
#define SRC_BYTE_2 0x00
#define SRC_BYTE_3 0x00
#define SRC_BYTE_4 0x00
#define SRC_BYTE_5 0x00
#define SRC_BYTE_6 0x00
#define SRC_BYTE_7 0x00

//input
extern int ptrRead;
extern int ptrWrite;
extern UI8 masterInputBuffer[MASTER_BUFFER_SIZE];

//output
extern UI8* retrievedPacket;

//finds a packet in masterInputBuffer and puts it in retrievedPacket
int findPacket(int* address);
bool AcquiredNewData(void);
int findAX25Flag(UI8 byte1, UI8 byte2, int startingPosition, int endPosition);
bool removeBitStuffing(int firstByte, int firstStartBit, int secondByte, int secondStartBit, UI8* unstuffedPacket);
bool checkCRC(UI8* data);
bool checkAddresses(UI8* data);


#endif /*PACKETGRABBER_H_*/
