//////////////////////////////////////////////////////////////////
//                                                              //
//    CDHApplication header                                     //
//    last edited by: Craig Nemeth                              //
//    date: August 31, 2012                                     //
//                                                              //
//////////////////////////////////////////////////////////////////

#include "COMApplication.h"
///////////////////////////////////////////////////////////////////

#if COM_PROCESSOR_COMPILE
#define COMMAND_ADDRESS 17
#define CMD_SEND_120_PACKETS 120
#define CMD_HANDSHAKE_ONE 15
#define CMD_HANDSHAKE_TWO 52
#define PACKET_SIZE 64

	///////////////////////////////////////////////////////////////////
	
	bool timeToChangePhase = false;
	UI16 currentToneIndex = 0;
	bool toggle = high;
	
	///////////////////////////////////////////////////////////////////
	

int bitPositionInPacket = 0;

///////////////////////////////////////////////////////////////////
bool linkEstablished = false;
void* nextPacketGroupToSend; //motherfucking voidstar ... wut?!
bool transmitting = false;
int listenTimeDivideCounter =0; //used to divide Timer A to listen at 3600 times per second
bool radioReadingNewest = false;
bool radioReadingMiddle = false;
bool radioReadingOldest = false;
bool listeningSynced = false;
int bitCountWhileSynced = 0;
int bitPositionInMasterBuffer = 0x80;

int testCount = 3;
///////////////////////////////////////////////////////////////////

UI16 nextSDCardAddress;
UI16 lastStoredSDCardAddress;
UI8 packetsInPhaseFormToSDCard[512];
UI16 PhaseBufferSize;

//must be generated
const UI8 stageTwoHandShake[] = { 0x97, 0x90, 0x51, 0x70, 0x30, 0xbe, 0x76, 0x0a, 0x18, 0x6b, 0x00, 0x00, 0x18, 0x6b, 0x00, 0x00, 0x0e, 0x65, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x64, 0x19, 0x60, 0x18, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30 };
const UI8 outOfDataMessage[] = { 0x97, 0x90, 0x51, 0x70, 0x30, 0xbe, 0x76, 0x0a, 0x18, 0x6b, 0x00, 0x00, 0x18, 0x6b, 0x00, 0x00, 0x0e, 0x65, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x64, 0x19, 0x60, 0x18, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30 };
///////////////////////////////////////////////////////////////////

void COM_timerA_ISR(void)
{
	runRadio();
}
	
	///////////////////////////////////////////////////////////////////
	

void COM_timerA2_ISR(void)
{
	listen();
}

///////////////////////////////////////////////////////////////////

void COM_application_main(void)
{
	initializePSKBuffer();
	enableInterrupts();
	logLine("COM scheduler initialized");
	for(;;)
	{
		COMMainScheduleLoop();
	}
}

void COMMainScheduleLoop(void)
{

	//enable interrupts to communicate with GND and listen
	enableInterrupts();
	int packetGroup;
	//control Radio interface/////////////////////////////////////////////////////////////////////////////////////////////
	if(AcquiredNewData())//set from the listening interrupt
	{
		if(findPacket(0))
		{	
			UI8 groundCommandNumber = retrievedPacket[COMMAND_ADDRESS];
			switch(groundCommandNumber)
			{
				case CMD_HANDSHAKE_ONE:
				
					nextPacketGroupToSend = &stageTwoHandShake;//TODO: hardcode this as phase changes
					//set the global var transmitting to true so the radio interrupt sends the next buffer of packets
					transmitting = true;
					while(transmitting);//wait for the interrupt to finish sending the packet. it will set transmitting false
				break;
				case CMD_SEND_120_PACKETS:
				
					
					//send 10 groups of 12 packets in phase shift form
					//SD card must be read from at 512 bytes at a time
					//the packets in phase shift from are 40 bytes (40*12 = 480)
					//the last 32 bytes from the SD card will be zero filled which will do nothing to the output signal
					
					for(packetGroup =0; packetGroup<10; packetGroup++)
					{
						if(nextSDCardAddress<=lastStoredSDCardAddress)
						{
							spiSDCardGetPacketGroup(nextPacketGroupToSend, nextSDCardAddress*512);//get packet from SD
							
							//set the global var transmitting to true so the radio interrupt sends the next buffer of packets
							transmitting = true;
							while(transmitting);//wait for the interrupt to finish sending the packet. it will set transmitting false
							
							//increment to next SD memory location
							nextSDCardAddress++;
						}else
						{
							nextPacketGroupToSend = &outOfDataMessage;
							//set the global var transmitting to true so the radio interrupt sends the next buffer of packets
							transmitting = true;
							while(transmitting);//wait for the interrupt to finish sending the packet. it will set transmitting false
						}
					}
					
				break;
				default:
				
					
				break;
			}
		}
	}
	//end control of radio interface/////////////////////////////////////////////////////////////////////////////////////////
	//note: radio interrupt is still running
	//control CDH interface//////////////////////////////////////////////////////////////////////////////////////////////////
	if(((P1IN&0x01)==0x00) && !transmitting)//CDH pulls spi cs low and not transmitting
	{
		disableInterrupts();//no more radio interface
		//TODO reset the buffer for the radio listening interrupt so old data is discarded when listening resumes
		UI8* packetFromCDH;
		CDHSPISendHandshake();//tell CDH that COM is ready to recieve data
		SPICDHGetPacket(packetFromCDH);//recieve packet from CDH
		convertBinaryToPSK(packetFromCDH,64);//convert and add to phase shifts from CDH buffer
		if(PhaseBufferSize==512)//if you have filled the buffer
		{
			spiSDCardStorePacketGroup(packetsInPhaseFormToSDCard, (++lastStoredSDCardAddress)*512);//send phase shifts to SD
		}
		enableInterrupts();
	}
	//end control CDH interface//////////////////////////////////////////////////////////////////////////////////////////////
}

void runRadio(void)
{
	if(transmitting)
	{	
		// TODO make this happen sometimes
		//bool timeToChangePhase = false;
		//static UI16 weirdTemp = 234;
		static UI16 phaseOffset = 150/4;
		static UI16 counter = 0;
		if (/*timeToChangePhase == true*/false)
		{
			UI8 currentPhaseChangeOutOf32 = phaseShifts[currentPhaseShiftIndex];
			phaseShifts[currentPhaseShiftIndex] = 0;
			currentPhaseShiftIndex++;
			if (currentPhaseShiftIndex >= PhaseShiftHistoryLength)
			{
				currentPhaseShiftIndex = 0;
			}
			UI16 degreesChange = phaseAngles[currentPhaseChangeOutOf32];
			UI16 toneIndexChange = ToneIndexPositionsPerDegreePhase * degreesChange;
			currentToneIndex += toneIndexChange;
		}
		//else
		//{
			currentToneIndex += 150;
		//	currentToneIndex = currentToneIndex % SINE_LENGTH;
			//weirdTemp += 38;
		//}
		
		counter++;
		if(counter >= SINE_LENGTH/150)
		{
			counter = 0;
			phaseOffset = phaseOffset == 2400 ? 0:2400;
		}
		
		
		/*if (currentToneIndex%SINE_LENGTH < currentToneIndex)
		{
			phaseOffset += 150;	
		}
		*/
		currentToneIndex = currentToneIndex%SINE_LENGTH;
		phaseOffset = phaseOffset%SINE_LENGTH;
		
		
		/*
		if (currentToneIndex+phaseOffset >= SINE_LENGTH)
		{
			//currentToneIndex += weirdTemp;
			currentToneIndex = (currentToneIndex % (SINE_LENGTH - phaseOffset));
		}
		*/
		devices.radio.microphone->value = getToneValueAt((currentToneIndex + phaseOffset)%SINE_LENGTH);
		startNewDigitalToAnalogConversion(devices.radio.microphone->value);
	
	}
}

void listen(void)
{
	if(testCount==3)
	{
		//printf("flip it\n");
		if (devices.craigsTest->state == high)
		{
			clearDigitalOutput(devices.craigsTest);
		}
		else
		{
			setDigitalOutput(devices.craigsTest);
		}
		testCount=1;
	}else
	{
		testCount++;
	}
		
	if(!transmitting)
	{	
		//catch bits
		
		//shuffle and get new data
		radioReadingOldest = radioReadingMiddle;
		radioReadingMiddle = radioReadingNewest;
		readDigitalInput(devices.craigsTest2);
		radioReadingNewest = devices.craigsTest2->state;
		
		if(listeningSynced)
		{
			if(bitCountWhileSynced==2)//its the third bit in the sequence
			{
				//check this bit with its surroundings
				if((radioReadingMiddle==radioReadingNewest) || (radioReadingMiddle==radioReadingOldest))
				{
					if(radioReadingMiddle)//add a one to the buffer
					{
						masterInputBuffer[ptrWrite] |= bitPositionInMasterBuffer;
						printf("one\n");
					}else//add a zero to the buffer
					{
						masterInputBuffer[ptrWrite] &= ~bitPositionInMasterBuffer;
						printf("zero\n");
					}
					
					if(bitPositionInMasterBuffer==0x01)//increment the bit position
					{
						bitPositionInMasterBuffer = 0x80;
						ptrWrite++;
					}else
					{
						bitPositionInMasterBuffer = bitPositionInMasterBuffer>>1;
					}						
				}else
				{
					listeningSynced = false;
				}
				
				bitCountWhileSynced =0;
			}else
			{
				bitCountWhileSynced++;
			}
		}else
		{
			if(radioReadingNewest && radioReadingMiddle)//found the starting of a one
			{
				listeningSynced = true; //now synced
				masterInputBuffer[ptrWrite] |= bitPositionInMasterBuffer;//add a one to the buffer
				bitCountWhileSynced = 2;
				printf("synced\n");
				
				if(bitPositionInMasterBuffer==0x01)//increment the bit position
				{
					bitPositionInMasterBuffer = 0x80;
					ptrWrite++;
				}else
				{
					bitPositionInMasterBuffer = bitPositionInMasterBuffer>>1;
				}
			}
		}	
	}
	
	printf("bitPositionInMasterBuffer = %x\n", bitPositionInMasterBuffer);
	
}


#endif



