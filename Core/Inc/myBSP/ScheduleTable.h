
#ifndef __SCHEDULETABLE_H__
#define __SCHEDULETABLE_H__

#include "main.h"
#include "MotorCtrl.h"
#include "stdio.h"
#include "string.h"


extern uint32_t TPMark[14];
extern uint32_t VPMark[8];

extern int Motor6_MicroSteps[32][3];
extern uint16_t Motor6_MicroSteps_Increment ;
extern struct DuoTongDao_SetPositionData data_V0 ;

void Turntable_Position_Init(void);
void Motor6_MicroSteps_Table_Init(void);
void DuoTongDao_Position_Init(void);
struct DuoTongDao_SetPositionData {
	uint32_t Position_motor6_PushRod_reset;		// 电机6行进到高位复位位置
	uint32_t Position_motor6_PushRod_push;		// 电机6准备推进位置

	uint32_t Position_motor5_internal;			// 电机5内部准备推进位置
	uint32_t Position_motor5_external;			// 电机5外部接收试剂位置

	uint32_t Position_motor3_external;			// 电机3外部准备推进位置
	uint32_t Position_motor3_storage;			// 电机3推进试剂条到存储位置
	uint32_t Position_motor3_detect;			// 电机3推进试剂条到检测预备位置
	uint32_t Position_motor3_reset;				// 电机3内部推出试剂条位置
};


#endif
