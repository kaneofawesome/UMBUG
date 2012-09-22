#ifndef PWR_H
#define PWR_H

#include <stdio.h>
#include "../../system/System.h"
#include "../CDH/CDHApplication.h"

typedef enum{
    COM,
    PLD1,
    PLD2
}SubsystemsToControlPowerTo;

typedef enum{
	subsON,
	subsOFF
}SubsBool;

void readbatterystate(Battery);
void turn_on_off_subsystems(void);
void voltage_comp(void);
void current_comp(void);

void initialize_pwr(void);
void pwr_routine(void);
void set_power_from_subsystem(SubsystemsToControlPowerTo, SubsBool);
void cut_power_from_subsystem(SubsystemsToControlPowerTo);
void add_power_to_subsystem(SubsystemsToControlPowerTo);

#endif /*PWR_H*/
