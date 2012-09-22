//////////////////////////////////////////////////////////////////
//                                                              //
//    Application header                                        //
//    last edited by: Kane Anderson                             //
//    date: November 22, 2011                                   //
//                                                              //
//////////////////////////////////////////////////////////////////

#ifndef APPLICATION_H
#define APPLICATION_H

//////////////////////////////////

#include "../system/System.h"

#include "ApplicationConfig.h"

#if CDH_PROCESSOR_COMPILE
#include "./CDH/CDHApplication.h"
#endif


//////////////////////////////////

void application_initialize(void);
void application_main(void);

#endif
