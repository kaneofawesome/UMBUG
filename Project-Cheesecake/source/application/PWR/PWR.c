#include "PWR.h"
#include "Power_Management.h"
#include "Power_Switching_Function.h"
#include "UART.h"

#if CDH_PROCESSOR_COMPILE

#define PWRBytes 8 //TODO: reading from the sensor assume to be 8 byte reading

UI8 COMMAND_MODE = 0xE3; // set the DS24808 to Command mode
UI8 DATA_MODE = 0xE1; // set the DS24080 to Data mode
UI8 SET_VPP_DURATION = 0x29; // set Vpp duration to be 512 us for eprom programming
UI8 RESET_PULSE = 0XC1; // to generate a reset pulse for ds24808
UI8 SKIP_ROM_COMMAND = 0xCC; // this tell ds24808 to skip the command receiving
UI8 WRITE_MEMORY_COMMAND = 0x0F; //command for writing to memory
UI8 READ_MEMORY_COMMAND = 0xF0;
UI8 ADDRESS_TA1_READING = 0xFF;   // TA2+TA1 result 0x00FF
UI8 ADDRESS_TA2_READING = 0x00;   //TODO: this address is for reading eprom need to be assigned to be proper value check with Jesse ASAP!
//UI8 ADDRESS_TA1_WRITING [] = { 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A}; //TA1 address for all the eprom value we need to write
UI8 ADDRESS_TA1_WRITING = 0x60; //Starting address for ta1
UI8 ADDRESS_TA2_WRITING = 0x00; //TA2 address for writing eprom all 00
UI8 RECEIVE_CRC16 = 0xFF; // 1) need send twice for CRC16 datasheet says it should receive CRC16 not sure if we need to or how to check on that.
                          // 2) Read Written Byte also use this command, just send it once

UI8 EPROM_WRITE_VALUE [] =   { 0x00, 0x00, 0xFF, 0xFF, 0xD7, 0x14, 0x9A, 0x1E, 0x06, 0x32, 0xFF, 0xFF, 0x10, 0x17, 0x3C, 0x49, 0x06, 0x0D, 0x15, 0x2F, 0x03, 0x05, 0x08, 0x1B, 0x04, 0x00, 0x00}; //values we need to write to the eprom
UI8 CONFIG_BAUD_RATE = 0x88; //set the baud rate to be 115.2kbps

UI8 responseCode; //response code from the 1wire thing


// Runs on startup.
void initialize_pwr(void)
{
    // TODO: enable the battery charger
    
    /*
        The following sequence is from DS24808 datasheet for WRITE EPROM SEQUENCE
    */
    
    //TODO: hit the multiplexer to switch the uart to talk to pwr circuit
    
    sendUARTData(CONFIG_BAUD_RATE); // config the baud rate at first time it powers up
    while(!UARTDataReady());
    
    sendUARTData(SET_VPP_DURATION);
    while(!UARTDataReady()); //wait for response
    
    //response code should be 28
    /* TODO: Checking response code ?*/
    /*
    responseCode = readUARTData();
    while(responseCode != 0x28)
    {
        sendUARTData(SET_VPP_DURATION);
        while(!UARTDataReady());
        //response code should be 28
        responseCode = readUARTData();
    }
    */
    
    sendUARTData(RESET_PULSE);
    while(!UARTDataReady());
    
    //response code should be CD or ED
    /* TODO: Checking response code ?*/
    /*
     responseCode = readUARTData();
     while(responseCode != CD && responseCode != ED)
     {
     sendUARTData(RESET_PULSE);
     while(!UARTDataReady());
     //response code should be CD or ED
     responseCode = readUARTData();
     }
     */
    sendUARTData(DATA_MODE);//no response for this one
    
    sendUARTData(SKIP_ROM_COMMAND);
    while(!UARTDataReady()); // response code is "as sent"
    
    sendUARTData(WRITE_MEMORY_COMMAND);
    while(!UARTDataReady()); // response code is "as sent"

    sendUARTData(ADDRESS_TA1_WRITING);//starting address for TA1
    while(!UARTDataReady()); // response code is "as sent"
    
    sendUARTData(ADDRESS_TA2_WRITING); //TA2 always 0x00
    while(!UARTDataReady()); // response code is "as sent"
    
    int i;
    
    for(i=0 ;i<27 ; i++)
    // we have 27 values to write for the eeprom
    {
        sendUARTData(EPROM_WRITE_VALUE[i]);//the actual data we write to eprom
        while(!UARTDataReady()); // response code is "as sent"
        
        /*
         // TODO: DO WE NEED THIS?
         //CRC Checking
         sendUARTData(RECEIVE_CRC16);
         while(!UARTDataReady());
         sendUARTData(RECEIVE_CRC16);
         while(!UARTDataReady());
         */
        
        sendUARTData(COMMAND_MODE); // set it to command mode
        while(!UARTDataReady()); // response code is "as sent"
     
        sendUARTData(RESET_PULSE);
        while(!UARTDataReady()); //wait for response
        
        //response code should be CD or ED
        /* TODO: Checking response code ?*/
        /*
         responseCode = readUARTData();
         while(responseCode != CD && responseCode != ED)
         {
         sendUARTData(RESET_PULSE);
         while(!UARTDataReady());
         //response code should be CD or ED
         responseCode = readUARTData();
         }
         */
        
        /*
         // TODO: DO WE NEED THIS?
         //read writen Byte
         sendUARTData(RECEIVE_CRC16);
         while(!UARTDataReady());
        */
        sendUARTData(DATA_MODE);//no response for this one
    }//end for
    
    sendUARTData(COMMAND_MODE); // set it to command mode
    while(!UARTDataReady()); // response code is "as sent"
    
    sendUARTData(RESET_PULSE);
    while(!UARTDataReady()); //wait for response
    
    //response code should be CD or ED
    /* TODO: Checking response code ?*/
    /*
     responseCode = readUARTData();
     while(responseCode != CD && responseCode != ED)
     {
     sendUARTData(RESET_PULSE);
     while(!UARTDataReady());
     //response code should be CD or ED
     responseCode = readUARTData();
     }
     */
}

// Runs every time the scheduler allows PWR to act.
// Check the battery monitor and send it to packetizer
void pwr_routine(void)
{
    Byte byteReadFromUART[PWRBytes];
	//TODO:
	if (getUARTState() == UART_NOT_RESERVED && 1/* TODO: enough time has passed since the last time we ran*/){
		//start UART collecting from the battery monitor thang 1wire thang
        sendUARTData(RESET_PULSE);
        while(!UARTDataReady()); //wait for response
        //response code should be CD or ED
        /* TODO: Checking response code ?*/
        /*
         responseCode = readUARTData();
         while(responseCode != CD && responseCode != ED)
         {
         sendUARTData(RESET_PULSE);
         while(!UARTDataReady());
         //response code should be CD or ED
         responseCode = readUARTData();
         }
         */
        sendUARTData(SKIP_ROM_COMMAND);
        while(!UARTDataReady()); // response code is "as sent"
        
        sendUARTData(READ_MEMORY_COMMAND);
        while(!UARTDataReady()); // response code is "as sent"
        
        sendUARTData(ADDRESS_TA1_READING);//starting address for TA1
        while(!UARTDataReady()); // response code is "as sent"
        
        sendUARTData(ADDRESS_TA2_READING); //TA2 always 0x00
        while(!UARTDataReady()); // response code is "as sent"
        
        int i;
        for(i=0; i<8; i++)
        {
            sendUARTData(0xFF); // TODO: (????)     use FF here to read the data from memory
            while(!UARTDataReady()); // response code is the data
            byteReadFromUART[i]=readUARTData();
        }
        
        sendUARTData(COMMAND_MODE); // set it to command mode
        while(!UARTDataReady()); // response code is "as sent"
        
        sendUARTData(RESET_PULSE);
        while(!UARTDataReady()); //wait for response
        // TODO: verify the reponse ?
        
        // TODO: warn COM about incoming data.
        //send the data to the COM processor.
        SPI_transmitStream(&devices.COM_Processor, byteReadFromUART, PWRBytes, true);
        
        
    	return;
	}//end  inner if
    else
    {
		return;
	}//end inner else
	
}

// Cut or add power to a subsystem to conserve or stop conserving power.
void set_subsystem_power(SubsystemsToControlPowerTo subs, SubsBool ONoff)
{
	switch(subs)
	{
		case COM :
			//cut or apply power to COM
			//  set pin which controls COM power to be SubsBool
			if (ONoff)
			{
				//set pin 
				//TODO: devices.pwrControllerCOM
			}else{
				//reset pin
			}
			break;
			
		case PLD1 :
			//cut or apply power to PLD1
			//  set pin which controls PLD1 power to be SubsBool
			if (ONoff)
			{
				//set pin 
			}else{
				//reset pin
			}
			break;
			
		case PLD2 :
			//cut or apply power to PLD2
			//  set pin which controls PLD2 power to be SubsBool
			if (ONoff)
			{
				//set pin 
			}else{
				//reset pin
			}
			break;
			
		default	  : ;
	}
}

void cut_power_from_subsystem(SubsystemsToControlPowerTo subs)
{
	set_subsystem_power(subs, subsOFF);
}

void add_power_to_subsystem(SubsystemsToControlPowerTo subs)
{
	set_subsystem_power(subs, subsON);
}

#endif
