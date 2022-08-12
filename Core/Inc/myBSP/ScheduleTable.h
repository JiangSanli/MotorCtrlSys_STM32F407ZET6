
#ifndef __SCHEDULETABLE_H__
#define __SCHEDULETABLE_H__

#include "main.h"
#include "MotorCtrl.h"
#include "stdio.h"
#include "string.h"

//struct turntable {		// 定义转盘参数的结构体
//	int32_t		position;		// 减速比
//
//};
//
//extern struct MotorDefine turntable[14];

extern uint32_t TPMark[14];

void Turntable_Position_Init(void);

#endif
