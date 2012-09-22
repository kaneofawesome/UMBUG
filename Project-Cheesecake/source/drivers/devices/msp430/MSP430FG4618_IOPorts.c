//////////////////////////////////////////////////////////////////
//                                                              //
//    representation of the processor                           //
//    last edited by: Kane Anderson                             //
//    date: March 8, 2012                                    	//
//																//
//	  Software representations of digital inputs and outputs	//
//	  and serial comms (or whatever other pins)					//
//                                                              //
//////////////////////////////////////////////////////////////////

#include "./MSP430FG4618_IOPorts.h"

// global variable ///////////////////////////////////////////////

MSP430FG4618 msp430;

// initialize function ///////////////////////////////////////////

void initialize_msp430_IO_ports(void)
{
	// PORT_1																		Pin#		CDH					COM
	P1DIR = 0x00; // 0000 0000
	initializeDigitalInput (	&msp430.PORT_1.digitalInput[0],			&P1IN,		0	);	// 	87		|					| CS in from SPI_1
	initializeDigitalInput (	&msp430.PORT_1.digitalInput[1],			&P1IN,		1	);	// 	86		|					|
	initializeDigitalInput (	&msp430.PORT_1.digitalInput[2],			&P1IN,		2	);	//  85		|					|
	initializeDigitalInput (	&msp430.PORT_1.digitalInput[3],			&P1IN,		3	);	//  84		|					|
	initializeDigitalInput (	&msp430.PORT_1.digitalInput[4],			&P1IN,		4	);	//  83		|					|
	initializeDigitalInput (	&msp430.PORT_1.digitalInput[5],			&P1IN,		5	);	//  82		|					|
	initializeDigitalInput (	&msp430.PORT_1.digitalInput[6],			&P1IN,		6	);	//  81		|					|
	initializeDigitalInput (	&msp430.PORT_1.digitalInput[7],			&P1IN,		7	);	//  80		|					|
	
	// PORT_2																		Pin#		CDH					COM
	P2DIR = 0x10; // 0001 0000
	initializeDigitalInput (	&msp430.PORT_2.digitalInput[0],			&P2IN,		0	);	// 	79		| digitalMUXIn0		|
	initializeDigitalInput (	&msp430.PORT_2.digitalInput[1],			&P2IN,		1	);	// 	78		| digitalMUXIn1		|
	initializeDigitalInput (	&msp430.PORT_2.digitalInput[2],			&P2IN,		2	);	// 	77		| digitalMUXIn2		|
	initializeDigitalInput (	&msp430.PORT_2.digitalInput[3],			&P2IN,		3	);	// 	76		|					|
	initializeSerialOutput (	&msp430.PORT_2.serialOutput,			&P2OUT,		4	);	// 	75		|					|
	initializeSerialInput  (	&msp430.PORT_2.serialInput,				&P2IN,		5	);	// 	74		|					|
	initializeDigitalInput (	&msp430.PORT_2.digitalInput[4],			&P2IN,		6	);	// 	73		|					|
	initializeDigitalInput (	&msp430.PORT_2.digitalInput[5],			&P2IN,		7	);	// 	72		|					|
	
	// PORT_3																		Pin#		CDH					COM
	#if CDH_PROCESSOR_COMPILE
		P3DIR = 0x0A; // 0000 1010
		initializeSerialInput  (	&msp430.PORT_3.serialInput[0],		&P3IN,		0	);	// 	71		| 					| 
		initializeSerialOutput (	&msp430.PORT_3.serialOutput[0],		&P3OUT,		1	);	// 	70		| SPI_1_MOSI		| SPI_1_MOSI
		initializeSerialInput  (	&msp430.PORT_3.serialInput[0],		&P3IN,		2	);	// 	69		| SPI_1_MISO		| SPI_1_MISO
		initializeSerialOutput (	&msp430.PORT_3.serialOutput[1],		&P3OUT,		3	);	// 	68		| SPI_1_CLK			| SPI_1_CLK
		initializeDigitalInput (	&msp430.PORT_3.digitalInput[0],		&P3IN,		4	);	// 	67		|					|
		initializeDigitalInput (	&msp430.PORT_3.digitalInput[1],		&P3IN,		5	);	//  66		|					| testInput on radio
		initializeDigitalInput (	&msp430.PORT_3.digitalInput[2],		&P3IN,		6	);	// 	65		|					|
		initializeDigitalInput (	&msp430.PORT_3.digitalInput[3],		&P3IN,		7	);	// 	64		|					|
		
	#elif COM_PROCESSOR_COMPILE
		P3DIR = 0x05; // 0000 0101
		initializeSerialOutput (	&msp430.PORT_3.serialOutput[0],		&P3OUT,		0	);	// 	71		| 					| 
		initializeSerialInput  (	&msp430.PORT_3.serialInput[0],		&P3IN,		1	);	// 	70		| SPI_1_MOSI		| SPI_1_MOSI
		initializeSerialOutput (	&msp430.PORT_3.serialOutput[1],		&P3OUT,		2	);	// 	69		| SPI_1_MISO		| SPI_1_MISO
		initializeSerialInput  (	&msp430.PORT_3.serialInput[1],		&P3IN,		3	);	// 	68		| SPI_1_CLK			| SPI_1_CLK
		initializeDigitalInput (	&msp430.PORT_3.digitalInput[0],		&P3IN,		4	);	// 	67		|					|
		initializeDigitalInput (	&msp430.PORT_3.digitalInput[1],		&P3IN,		5	);	//  66		|					| testInput on radio
		initializeDigitalInput (	&msp430.PORT_3.digitalInput[2],		&P3IN,		6	);	// 	65		|					|
		initializeDigitalInput (	&msp430.PORT_3.digitalInput[3],		&P3IN,		7	);	// 	64		|					|
	#endif
	
	// PORT_4																		Pin#		CDH					COM
	P4DIR = 0x4D; // 0100 1101
	initializeSerialOutput (	&msp430.PORT_4.serialOutput[0],			&P4OUT,		0	);	//  63		|					|
	initializeSerialInput  (	&msp430.PORT_4.serialInput[0],			&P4IN,		1	);	//  62		|					|
	initializeSerialOutput (	&msp430.PORT_4.serialOutput[1],			&P4OUT,		2	);	//  51		|					|
	initializeSerialOutput (	&msp430.PORT_4.serialOutput[2],			&P4OUT,		3	);	//  50		|					|
	initializeSerialInput  (	&msp430.PORT_4.serialInput[1],			&P4IN,		4	);	//  49		|					|
	initializeSerialInput  (	&msp430.PORT_4.serialInput[2],			&P4IN,		5	);	//  48		|					|
	initializeSerialOutput (	&msp430.PORT_4.serialOutput[3],			&P4OUT,		6	);	//  47		|					|
	initializeSerialInput  (	&msp430.PORT_4.serialInput[3],			&P4IN,		7	);	//  46		|					|
	
	// PORT_5																					Pin#		CDH					COM
	P5DIR = 0x02; // 0000 0010
	initializeAnalogInput  (	&msp430.PORT_5.analogInput,				&P5IN,		0	);	// 	13		|					| in from radio
	initializeDigitalOutput(	&msp430.PORT_5.digitalOutput,			&P5OUT,		1	);	// 	12		|					| 
	initializeDigitalInput (	&msp430.PORT_5.digitalInput[0],			&P5IN,		2	);	// 	53		|					| 
	initializeDigitalInput (	&msp430.PORT_5.digitalInput[1],			&P5IN,		3	);	// 	54		|					| 
	initializeDigitalInput (	&msp430.PORT_5.digitalInput[2],			&P5IN,		4	);	// 	55		|					| 
	initializeDigitalInput (	&msp430.PORT_5.digitalInput[3],			&P5IN,		5	);	// 	56		|					| 
	initializeDigitalInput (	&msp430.PORT_5.digitalInput[4],			&P5IN,		6	);	// 	57		|					| 
	initializeDigitalInput (	&msp430.PORT_5.digitalInput[5],			&P5IN,		7	);	// 	58		|					| 
	
	// PORT_6																					Pin#		CDH					COM
	P6DIR = 0X40; // 0100 0000
	initializeAnalogInput  (	&msp430.PORT_6.analogInput[0],			&P6IN,		0	);	//  95		| analogMUXIn0		|
	initializeAnalogInput  (	&msp430.PORT_6.analogInput[1],			&P6IN,		1	);	//  96		| analogMUXIn1		|
	initializeAnalogInput  (	&msp430.PORT_6.analogInput[2],			&P6IN,		2	);	//  97		| analogMUXIn2		|
	initializeAnalogInput  (	&msp430.PORT_6.analogInput[3],			&P6IN,		3	);	// 	2		| temperature sensor| 
	initializeAnalogInput  (	&msp430.PORT_6.analogInput[4],			&P6IN,		4	);	// 	3		|					| 
	initializeAnalogInput  (	&msp430.PORT_6.analogInput[5],			&P6IN,		5	);	// 	4		|					| 
	initializeAnalogOutput (	&msp430.PORT_6.analogOutput,			&P6OUT,		6	);	//  5		| unused			| out to radio
	initializeAnalogInput  (	&msp430.PORT_6.analogInput[6],			&P6IN,		7	);	// 	6		|					| 
	
	// PORT_7																					Pin#		CDH					COM
	#if CDH_PROCESSOR_COMPILE
		P7DIR = 0xF3; // 1111 0011
		initializeDigitalOutput(	&msp430.PORT_7.digitalOutput[0],	&P7OUT,		0	);	// 	45		|					| x
		initializeDigitalOutput(	&msp430.PORT_7.digitalOutput[1],	&P7OUT,		1	);	// 	44		|					| x
		initializeDigitalInput (	&msp430.PORT_7.digitalInput,		&P7IN,		2	);	// 	43		|					| x
		initializeDigitalOutput(	&msp430.PORT_7.digitalOutput[1],	&P7OUT,		3	);	// 	42		|					| x
		initializeDigitalOutput(	&msp430.PORT_7.digitalOutput[0],	&P7OUT,		4	);	// 	41		|					| x
		initializeDigitalOutput(	&msp430.PORT_7.digitalOutput[1],	&P7OUT,		5	);	// 	40		|	COM_SPI_CS		| x
		initializeDigitalOutput(	&msp430.PORT_7.digitalOutput[2],	&P7OUT,		6	);	// 	39		|					| x
		initializeDigitalOutput(	&msp430.PORT_7.digitalOutput[3],	&P7OUT,		7	);	// 	38		|					| x
	
	#elif COM_PROCESSOR_COMPILE
		P7DIR = 0xF3; // 1111 0011
		initializeSerialInput  (	&msp430.PORT_7.serialInput[0],		&P7IN,		0	);	// 	45		| x					| 
		initializeSerialOutput (	&msp430.PORT_7.serialOutput[0],		&P7OUT,		1	);	// 	44		| x					| SPI_2_MOSI
		initializeSerialInput  (	&msp430.PORT_7.serialInput[1],		&P7IN,		2	);	// 	43		| x					| SPI_2_MISO
		initializeSerialOutput (	&msp430.PORT_7.serialOutput[1],		&P7OUT,		3	);	// 	42		| x					| SPI_2_CLK
		initializeDigitalOutput(	&msp430.PORT_7.digitalOutput[0],	&P7OUT,		4	);	// 	41		| x					| 
		initializeDigitalOutput(	&msp430.PORT_7.digitalOutput[1],	&P7OUT,		5	);	// 	40		| x					| 
		initializeDigitalOutput(	&msp430.PORT_7.digitalOutput[2],	&P7OUT,		6	);	// 	39		| x					| 
		initializeDigitalOutput(	&msp430.PORT_7.digitalOutput[3],	&P7OUT,		7	);	// 	38		| x					|
	#endif 
	
	// PORT_8																					Pin#		CDH					COM
	P8DIR = 0xFF; // 1111 1111
	initializeDigitalOutput(	&msp430.PORT_8.digitalOutput[0],		&P8OUT,		0	);	// 	37		|					| 
	initializeDigitalOutput(	&msp430.PORT_8.digitalOutput[1],		&P8OUT,		1	);	// 	36		| MUX select 0		| 
	initializeDigitalOutput(	&msp430.PORT_8.digitalOutput[2],		&P8OUT,		2	);	// 	35		| MUX select 1		| 
	initializeDigitalOutput(	&msp430.PORT_8.digitalOutput[3],		&P8OUT,		3	);	// 	34		| MUX select 2		| 
	initializeDigitalOutput(	&msp430.PORT_8.digitalOutput[4],		&P8OUT,		4	);	// 	33		| digitalMUXOut0	| 
	initializeDigitalOutput(	&msp430.PORT_8.digitalOutput[5],		&P8OUT,		5	);	// 	32		| digitalMUXOut1	| 
	initializeDigitalOutput(	&msp430.PORT_8.digitalOutput[6],		&P8OUT,		6	);	// 	31		| digitalMUXOut2	| 
	initializeDigitalOutput(	&msp430.PORT_8.digitalOutput[7],		&P8OUT,		7	);	//  30		| Torquers X 1&3    |
	
	// PORT_9																					Pin#		CDH					COM
	P9DIR = 0xFF; // 1111 1111
	initializeDigitalOutput(	&msp430.PORT_9.digitalOutput[0],		&P9OUT,		0	);	//  29		|					|
	initializeDigitalOutput(	&msp430.PORT_9.digitalOutput[1],		&P9OUT,		1	);	//  28		|					|
	initializeDigitalOutput(	&msp430.PORT_9.digitalOutput[2],		&P9OUT,		2	);	//  27		|					|
	initializeDigitalOutput(	&msp430.PORT_9.digitalOutput[3],		&P9OUT,		3	);	//  26		|					|
	initializeDigitalOutput(	&msp430.PORT_9.digitalOutput[4],		&P9OUT,		4	);	//  25		| heater control    |
	initializeDigitalOutput(	&msp430.PORT_9.digitalOutput[5],		&P9OUT,		5	);	//  24		|					|
	initializeDigitalOutput(	&msp430.PORT_9.digitalOutput[6],		&P9OUT,		6	);	//  23		|					|
	initializeDigitalOutput(	&msp430.PORT_9.digitalOutput[7],		&P9OUT,		7	);	//  22		|					|
	
	// PORT_10																					Pin#		CDH					COM
	P10DIR = 0x3F; // 0011 1111
	initializeDigitalOutput(	&msp430.PORT_10.digitalOutput[0],		&P10OUT,	0	);	//  21		| 					| 
	initializeDigitalOutput(	&msp430.PORT_10.digitalOutput[1],		&P10OUT,	1	);	//  20		| 					| 
	initializeDigitalOutput(	&msp430.PORT_10.digitalOutput[2],		&P10OUT,	2	);	//  19		| 					| 
	initializeDigitalOutput(	&msp430.PORT_10.digitalOutput[3],		&P10OUT,	3	);	//  18		|					| SD card enable
	initializeDigitalOutput(	&msp430.PORT_10.digitalOutput[4],		&P10OUT,	4	);	// 	17		| RTC chip enable	|
	initializeDigitalOutput(	&msp430.PORT_10.digitalOutput[5],		&P10OUT,	5	);	// 	16		| watchdog WDI		|
	initializeAnalogInput  (	&msp430.PORT_10.analogInput[0],			&P10IN,		6	);	//  15		| 					| 
	initializeAnalogInput  (	&msp430.PORT_10.analogInput[1],			&P10IN,		7	);	//  14		| 					| 
	
	// configuring Analog to Digital conversion -------------------------------------
	initialize_analogToDigitalConverter();
	
	// configuring Digital to Analog conversion -------------------------------------
	initialize_digitalToAnalogConverter();
	
}




