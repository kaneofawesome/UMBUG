#ifndef ADCS_H_
#define ADCS_H_

#include <stdio.h>
#include "../ApplicationConfig.h"
#include "../../system/System.h"
#include "../../system/Log.h"
#include "../CDH/CDHApplication.h"
#include "../PWR/UART.h"

void adcs_routine(void);
void adcs_LEOP(void);

#endif /*ADCS_H_*/
