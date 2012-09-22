//////////////////////////////////////////////////////////////////
//                                                              //
//    Drivers main file                                         //
//    last edited by: Kane Anderson                             //
//    date: April 06, 2012                                      //
//                                                              //
//////////////////////////////////////////////////////////////////

#include "Drivers.h"

// global variable ///////////////////////////////////////////////
AllDevices devices;

//////////////////////////////////////////////////////////////////

void drivers_initialize(void)
{
	initialize_msp430_IO_ports();
	
	// refer to the msp430 spreadsheet on google docs for
	// where to put your pins... when you use up a pin,
	// comment beside the pin to say what it is used for.
	
	// system watchdog ///////////////////////////////////////////
	
	devices.systemWatchdog.WDI						= &msp430.PORT_10.digitalOutput[5];
	watchdog_initialize(&devices.systemWatchdog);
		
	// system clock //////////////////////////////////////////////
	#if RTC_CONNECTED
		// RTC
		devices.realTimeClock.SPI.channel			= SPI_CHANNEL_1;
		devices.realTimeClock.SPI.chipSelect.out	= &msp430.PORT_10.digitalOutput[4];
		devices.realTimeClock.SPI.CLK.out			= &msp430.PORT_3.serialOutput[1];
		devices.realTimeClock.SPI.MISO.in			= &msp430.PORT_3.serialInput[0];
		devices.realTimeClock.SPI.MOSI.out			= &msp430.PORT_3.serialOutput[0];
		devices.realTimeClock.SPI.type				= SPI_TYPE_Master;
		devices.realTimeClock.SPI.activeHigh		= true;
		devices.realTimeClock.SPI.controlRegister0	= 0x29;	// 0010 1001
		devices.realTimeClock.SPI.controlRegister1	= 0x80; // 1000 0000
		devices.realTimeClock.SPI.bitRateRegister0	= 0x20; // 0010 0000
		devices.realTimeClock.SPI.bitRateRegister1	= 0x00; // 0000 0000
		realTimeClock_initialize(&devices.realTimeClock);
	#endif

	#if CDH_PROCESSOR_COMPILE
		
		// COM
		devices.COM_Processor.channel				= SPI_CHANNEL_1;
		
		devices.COM_Processor.chipSelect.out		= &msp430.PORT_7.digitalOutput[1];
		devices.COM_Processor.CLK.out				= &msp430.PORT_3.serialOutput[1];
		devices.COM_Processor.MISO.in				= &msp430.PORT_3.serialInput[0];
		devices.COM_Processor.MOSI.out				= &msp430.PORT_3.serialOutput[0];
		devices.COM_Processor.type					= SPI_TYPE_Master;
		devices.COM_Processor.activeHigh			= false;
		devices.COM_Processor.controlRegister0		= 0x29; // 0010 0001
		devices.COM_Processor.controlRegister1		= 0x80; // 1000 0000
		devices.COM_Processor.bitRateRegister0		= 0x20; // 0010 0000
		devices.COM_Processor.bitRateRegister1		= 0x00; // 0000 0000		
		
	#endif
	
	#if COM_PROCESSOR_COMPILE
		
		// CDH
		devices.CDH_Processor.channel				= SPI_CHANNEL_1;
		devices.CDH_Processor.chipSelect.in			= &msp430.PORT_1.digitalInput[0];
		devices.CDH_Processor.CLK.in				= &msp430.PORT_3.serialInput[1];
		devices.CDH_Processor.MISO.out				= &msp430.PORT_3.serialOutput[1];
		devices.CDH_Processor.MOSI.in				= &msp430.PORT_3.serialInput[0];
		devices.CDH_Processor.type					= SPI_TYPE_Slave;
		devices.CDH_Processor.activeHigh			= false;
		devices.CDH_Processor.controlRegister0		= 0x21; // 0010 0001
		devices.CDH_Processor.controlRegister1		= 0x80; // 1000 0000
		devices.CDH_Processor.bitRateRegister0		= 0x20; // 0010 0000
		devices.CDH_Processor.bitRateRegister1		= 0x00; // 0000 0000
		
		// radio	
		devices.radio.microphone					= &msp430.PORT_6.analogOutput;
		
	#endif
	
	#if SD_CONNECTED
		
		// SD CARD
		devices.sdCard.power						= &msp430.PORT_10.digitalOutput[1]; // pin 20
		devices.sdCard.SPI.channel					= SPI_CHANNEL_2;
		devices.sdCard.SPI.CLK.out					= 
		devices.sdCard.SPI.chipSelect.out			= &msp430.PORT_8.digitalOutput[0];
		devices.sdCard.SPI.type						= SPI_TYPE_Master;
		devices.sdCard.SPI.activeHigh				= false;
		devices.sdCard.SPI.controlRegister0			= 0xA9; // 1010 1001
		devices.sdCard.SPI.controlRegister1			= 0x80; // 1000 0000
		devices.sdCard.SPI.bitRateRegister0			= 0x20; // 0010 0000
		devices.sdCard.SPI.bitRateRegister1			= 0x00; // 0000 0000
		setDigitalOutput(devices.sdCard.SPI.chipSelect.out);
		clearDigitalOutput(devices.sdCard.power);
	
	#endif
	
	
	// TEST SPI FRAMEWORK ONLY ///////////////////////////////////
	
	
	#if CDH_PROCESSOR_COMPILE
		//devices.pwrControllerCOM.output		    = &msp430.PORT_8.digitalOutput[3];
		//devices.pwrControllerPLD2.output	    = &msp430.PORT_8.digitalOutput[4];
		//devices.pwrControllerPLD1.output	    = &msp430.PORT_8.digitalOutput[5];
		//devices.test_SPI_device.chipSelect.out	= &msp430.PORT_10.digitalOutput[4];
		//devices.test_SPI_device.channel			= SPI_CHANNEL_1;
		//devices.test_SPI_device.type			= SPI_TYPE_Master;
		//devices.test_SPI_device.activeHigh		= true;		devices.test_SPI_device.chipSelect.out		= &msp430.PORT_10.digitalOutput[4];


		//devices.test_SPI_device.channel				= SPI_CHANNEL_1;
		//devices.test_SPI_device.type				= SPI_TYPE_Master;
		//devices.test_SPI_device.activeHigh			= true;
		//devices.test_SPI_device.controlRegister0	= 0xA9;
		//devices.test_SPI_device.controlRegister1	= 0x80;
		//devices.test_SPI_device.bitRateRegister0	= 0x04;
		//devices.test_SPI_device.bitRateRegister1	= 0x00;
		
		devices.tardigradeTemperatureSensor.voltageInput = &msp430.PORT_6.analogInput[3];
		devices.HeaterForTardigrades.voltageOutput       = &msp430.PORT_9.digitalOutput[4];
		devices.TorqueRod1.voltageOutput				 = &msp430.PORT_8.digitalOutput[7]; // TODO: Do these need enable pins for multiplexing ??
		devices.TorqueRod2.voltageOutput				 = &msp430.PORT_8.digitalOutput[5]; // TODO: RECHECK ALL OF THESE TORQUER CONNECTIONS
		devices.TorqueRod3.voltageOutput				 = &msp430.PORT_8.digitalOutput[0];
		devices.TorqueRod4.voltageOutput				 = &msp430.PORT_7.digitalOutput[3];
		devices.TorqueRod5.voltageOutput				 = &msp430.PORT_7.digitalOutput[0];
		devices.TorqueRod6.voltageOutput				 = &msp430.PORT_4.serialOutput[3]; // TODO: wut !? serial ??
	#else
		//devices.test_SPI_device.chipSelect.in		= &msp430.PORT_1.digitalInput[5];
		//devices.test_SPI_device.channel				= SPI_CHANNEL_1;
		//devices.test_SPI_device.type				= SPI_TYPE_Slave;
		//devices.test_SPI_device.activeHigh			= true;
		//devices.test_SPI_device.controlRegister0	= 0xA1;
		//devices.test_SPI_device.controlRegister1	= 0x80;
		//devices.test_SPI_device.bitRateRegister0	= 0x04;
		//devices.test_SPI_device.bitRateRegister1	= 0x00;
	#endif
	
	//initialize_SPI(&devices.test_SPI_device);

	
	// system status LED /////////////////////////////////////////
	
	devices.systemStatusLED					= &msp430.PORT_5.digitalOutput;
	
	// operating mode to fully active ////////////////////////////
	
	// correct me if I'm wrong but I think this enters low power mode 4
	//_bic_SR_register(LPM4_bits);
	
	// smclk clock setup /////////////////////////////////////////
	
	FLL_CTL0 |= DCOPLUS + XTS_FLL;
	FLL_CTL1 &= ~(SELS + SELM0 + SMCLKOFF + FLL_DIV0 + FLL_DIV1);
	FLL_CTL1 |= XT2OFF + SELM1;
	
	// System Clock Frequency Integrator 0 ///////////////////////
	
	//SCFI0 &= ~(FLLD0 + FLLD1);
	
	#if CDH_PROCESSOR_COMPILE
		SCFI0 |= FN_8; //FLL_DIV_1 |
	#endif
	
	#if COM_PROCESSOR_COMPILE
		SCFI0 |= FN_8; //FLL_DIV_1 |
	#endif
	
	SCFI0 &= ~(FLLD0 + FLLD1);
	
	// System Clock Frequency Control ////////////////////////////
	
	SCFQCTL = SCFQ_1M; //modulation is enabled, frequency set to 1MHz // TODO: merge had this at SCFQ_2M.
	_BIC_SR(SCG0);	//enable FLL
	 
	//DCOCTL = CALDCO_8MHZ;       // DCO frequency set to 1 MHz
	//BCSCTL1 = CALBC1_8MHZ;      // DCO range set to 1 MHz
	 
	// Digital to analog conversion //////////////////////////////
	#if COM_PROCESSOR_COMPILE
		// TODO UNCOMMENT AFTER TEST OUTPUT DONE
//		devices.radio.microphone				= &msp430.PORT_6.analogOutput; // TODO: merge commented out
//		devices.test_AtoD						= &msp430.PORT_5.analogInput; // TODO: merge commented out
		//devices.testPSK							= &msp430.PORT_6.analogOutput;
		devices.craigsTest						= &msp430.PORT_10.digitalOutput[0];
		devices.craigsTest2						= &msp430.PORT_5.digitalInput[5];
		
	#endif
	
	// for debug purposes
	// TODO REMOVE
	devices.tardigradeTemperatureSensor.voltageInput		= &msp430.PORT_6.analogInput[5]; // P6.5, pin #4
	
	
	
	// master multiplexer select lines... used for all multiplexed I/O
	//devices.multiplexerSelectLines.S0		= &msp430.PORT_8.digitalOutput[1];
	//devices.multiplexerSelectLines.S1		= &msp430.PORT_8.digitalOutput[2];
	//devices.multiplexerSelectLines.S2		= &msp430.PORT_8.digitalOutput[3];
	
	
}

//////////////////////////////////////////////////////////////////


