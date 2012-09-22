//******************************************************************************
//  MSP-FET430x169 Device Driver Header File
//
//  Description: This header contains the common definitions for the WinCube
//				 project.
//
//  Timothy vanBeek
//  University of Manitoba
//  March 2007
//  Built with IAR Embedded Workbench Version: 4.01
//
//  Modified by Chris Nichols and Dario Schor
//  January 2008
//******************************************************************************

// prevent multiple instances of the same file
#ifndef __COMMON_H__
#define __COMMON_H__

	/************************************************************
	* Global Constants
	************************************************************/
	#define ON                  1
	#define OFF                 0
	#define TIMEOUT             1000

	#ifndef TRUE
	#define TRUE				1
	#endif

	#ifndef FALSE
	#define FALSE				0
	#endif

	#define HFXTCLK				7372800		// High Frequency External Clock freq.
	#define LFXTCLK				32768		// Low Frequency External Clock freq.

	/**
	 * Master DEBUG flag for the entire system.
	 * Turning this on will cause printing of information to standard output.
	 **/
	#define DEBUG				FALSE

#endif //__COMMON_H__
