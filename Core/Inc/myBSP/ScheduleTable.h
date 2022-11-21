
#ifndef __SCHEDULETABLE_H__
#define __SCHEDULETABLE_H__

#include "main.h"
#include "MotorCtrl.h"
#include "stdio.h"
#include "string.h"


extern uint32_t TPMark[14];

extern int Motor6_MicroSteps[32][3];
extern uint16_t Motor6_MicroSteps_Increment ;

void Turntable_Position_Init(void);
void Motor6_MicroSteps_Table_Init(void);

#endif
