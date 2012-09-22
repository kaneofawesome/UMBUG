//******************************************************************************
//  Power Management Application ( source file) 
//
// Description: Monitors the power levels of each subsystem 
//
//******************************************************************************
 
// Kane commented it out because the file doesn't exist
//#include <Power_Management.h>
#include <msp430fg4618.h>
//#include <Power_Switching_Function.h>
 
// To be defined after consulting with Mathew or Kane
#define MIN_POWER        // todo
#define MID_POWER        // todo
#define MAX_POWER        // todo   
 
void powermanagement()
{
	/*
  int battery_state = 0;
  int charge_level = 0;
 
  //
 
  for(;;)
  {
    battery_state = fg_read_relativestate();
 
    if(charge_level < MIN_POWER)
    {
        // shut down 
    }
 
    else if(charge_level < MID_POWER)
    {
        // shut down some components
    }
 
    else if (charge_level < MAX_POWER)
    {
        // everything runs as normal
    }
 
    }
 
  
  }
 
 	*/
}
 

 
void pm_verify()
{
 // to be dealt with  in ISR defined in the batter_charger.c
}

