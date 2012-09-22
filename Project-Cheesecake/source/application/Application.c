//////////////////////////////////////////////////////////////////
//                                                              //
//    Application source                                        //
//    last edited by:  Kane Anderson                            //
//    date: January 17, 2012                                    //
//                                                              //
//////////////////////////////////////////////////////////////////

#include "Application.h"
#include "CDH/CDHApplication.h"
#include "COM/COMApplication.h"
#include <stdio.h>

//////////////////////////////////

void application_initialize(void)
{
	// TODO
}

void application_main(void)
{
	// note:
	// CDH_PROCESSOR_COMPILE and COM_PROCESSOR_COMPILE
	// are #defined in ApplicationConfig.h
	
	#if CDH_PROCESSOR_COMPILE
		CDH_application_main();
	#endif

	#if COM_PROCESSOR_COMPILE
		COM_application_main();
	#endif
}

//////////////////////////////////
