//******************************************************************************
// Power Switching Function for Ultra-Low-Power MSP430
//
//  Description: This header file provides the  power switching function for battery management 
//
//        Mohamed Temam Nasri
//		  05/31/2012 	
//******************************************************************************
 
// prevent multiple instances of the same file
#ifndef __POWER_SWITCHING_H__
#define __POWER_SWITCHING_H__
 
//#include <msp430xxxx.h>

 

 

 
 
/************************************************************ 
 * Functions
 ************************************************************/
 
/**
 * Initializes and enables the power switching functions 
 *
 * IN: void
 * OUT: void
 */
void pwr_initialize(void);
 
/**
 * Switches power to the science control on
 *
 * IN: void
 * OUT: void
 */
void pwr_PLD1on(void);
 
/**
 * Switches power on to payload1 
 *
 * IN: void
 * OUT: void
 */
 void pwr_PLD1off(void);
 
/**
 * Switches power off to payload1
 *
 * IN: void
 * OUT: void
 */
void pwr_PLD2on(void);
 
/**
 * Switches power on to payload2
 *
 * IN: void
 * OUT: void
 */
 void pwr_PLD2off(void);
 
/**
 * Switches power off to payload2
 *
 * IN: void
 * OUT: void
 */
void pwr_COMon(void);
 
/**
 * Switches power on to COM subsystem
 *
 * IN: void
 * OUT: void
 */
 void pwr_COMoff(void);
 
/**
 * Switches power off to COM subsystem
 *
 * IN: void
 * OUT: void
 */
void psn_THMon(void);
 
/**
 * Switches power on to the thermal subsystem
 *
 * IN: void
 * OUT: void
 */
 void psn_THMoff(void);
 
/**
 * Switches power off to the thermal subsystem
 *
 * IN: void
 * OUT: void
 */

#endif // __POWER_SWTICHING_H__
