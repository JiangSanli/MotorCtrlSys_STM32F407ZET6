
#include "main.h"
#include "cmsis_os.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "stdio.h"
#include "MotorCtrl.h"
#include "stdlib.h"
#include "ScheduleTable.h"

// Cifenli 转盘角度对应步数表
uint32_t TPMark[14] ={0};
void Turntable_Position_Init(void)
{
	// micro_steps=8
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

// L298N驱动细分表，max:1/8 microSteps
int Motor6_MicroSteps[32][3] = {
		{1 , 100 , 0},
		{2 , 98 , 20},
		{3 , 92 , 38},
		{4 , 83 , 56},
		{5 , 71 , 71},
		{6 , 56 , 83},
		{7 , 38 , 92},
		{8 , 20 , 98},

		{9 , 0 , 100},
		{10 , -20 , 98},
		{11 , -38 , 92},
		{12 , -56 , 83},
		{13 , -71 , 71},
		{14 , -83 , 56},
		{15 , -92 , 38},
		{16 , -98 , 20},

		{17 , -100 , 0},
		{18 , -98 , -20},
		{19 , -92 , -38},
		{20 , -83 , -56},
		{21 , -71 , -71},
		{22 , -56 , -83},
		{23 , -38 , -92},
		{24 , -20 , -98},

		{25 , 0 , -100},
		{26 , 20 , -98},
		{27 , 38 , -92},
		{28 , 56 , -83},
		{29 , 71 , -71},
		{30 , 83 , -56},
		{31 , 92 , -38},
		{32 , 98 , -20},
};

uint16_t Motor6_MicroSteps_Increment ;
void Motor6_MicroSteps_Table_Init(void)
{
	Motor6_MicroSteps_Increment = 8/Motor[6].mircro_steps ;
}

// DuoTongDao Z轴8格试剂条位置
#define VP_gap  8192
#define VP_first_place 3488
uint32_t VPMark[8] ={0};
void Vertical_Position_Init(void)
{
	// micro_steps=16
	VPMark[0] = VP_first_place;	//位置1，最上方格口对齐
	VPMark[1] = VPMark[0] + VP_gap;
	//VPMark[2] = VPMark[1] + VP_gap;
	VPMark[2] = 20224;
	VPMark[3] = VPMark[2] + VP_gap;
	VPMark[4] = VPMark[3] + VP_gap;
	VPMark[5] = VPMark[4] + VP_gap;
	VPMark[6] = VPMark[5] + VP_gap;
	VPMark[7] = VPMark[6] + VP_gap;
}



