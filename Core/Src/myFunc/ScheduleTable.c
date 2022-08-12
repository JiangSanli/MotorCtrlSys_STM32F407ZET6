
#include "main.h"
#include "cmsis_os.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "stdio.h"
#include "MotorCtrl.h"
#include "stdlib.h"
#include "ScheduleTable.h"

////定义电机的数组结构体
//struct MotorDefine turntable[14];

uint32_t TPMark[14] ={0};

void Turntable_Position_Init(void)
{
	TPMark[0] = 5;
	TPMark[1] = 296;
	TPMark[2] = 575;
	TPMark[3] = 850;
	TPMark[4] = 1145;
	TPMark[5] = 1422;
	TPMark[6] = 1707;
	TPMark[7] = 1994;
	TPMark[8] = 2296;
	TPMark[9] = 2582;
	TPMark[10] = 2872;
	TPMark[11] = 3158;
	TPMark[12] = 3444;
	TPMark[13] = 3725;
}
