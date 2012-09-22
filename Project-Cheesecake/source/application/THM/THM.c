#include "THM.h"

#if CDH_PROCESSOR_COMPILE

#define THMBytes 2

bool currentlyApplyingHeat = false;
UI16 thmThresholdLOW = 0x23; //TODO: set as a proper value //5.000 degrees C // 2.4834 Volts
UI16 thmThresholdHIGH = 0x50; //TODO: set as a proper value //10.000 degrees C // 2.5223 Volts

UI16 getThermalSensorReading(void){
	UI16 sensorValue = 0x00;
	
	sensorValue = thermocouple_read(&devices.tardigradeTemperatureSensor); // read the termistor's value
	
	return(sensorValue);
}

void startHeating(void){
	startHeater(&devices.HeaterForTardigrades);
}

void stopHeating(void){
	stopHeater(&devices.HeaterForTardigrades);
}

void sendTHMToPacketizer(UI16 value){
	Byte bytesToSend[THMBytes];
	
	bytesToSend[0] = (int)((value >> 8) & 0xFF);
	bytesToSend[1] = (int)(value & 0xFF);
	
	Packetize(PKT_THERMAL_READINGS, bytesToSend, THMBytes);
}

void thm_routine(void)
{
  UI16 currentTemp = 0x00;
  
  if (getUARTState() == UART_POWER)
  {
  	if (0 /*TODO: we are done sending the data*/)
  	{
  		setUARTState(UART_NOT_RESERVED);
  	}
  }
  
  if (0 /*TODO: enough time has passed since the last time we ran*/)
  {
    currentTemp = getThermalSensorReading();
    if (!currentlyApplyingHeat)
    {
      if (currentTemp <= thmThresholdLOW)
      {
	    currentlyApplyingHeat = true;
	    startHeating();
      }
    }
    else
    {
      if (currentTemp >= thmThresholdHIGH)
      {
	    currentlyApplyingHeat = false;
	    stopHeating();
	    if (getUARTState() == UART_NOT_RESERVED)
	    {
	      sendTHMToPacketizer(currentTemp); //send the data to the packetizer to be timestamped
	    }
      }
    }
  }
}



#endif
