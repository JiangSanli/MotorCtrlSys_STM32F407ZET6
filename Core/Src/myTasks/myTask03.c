
/*
 * messageTask - 接收上位机发送的协议并解析
 * 更新日志：
 * 2022.07.26 - 新建
 * 2022.08.01 - 更新位置控制算法，使用实时位置数据作为控制参数
 */

#include "main.h"
#include "cmsis_os.h"
#include "adc.h"
#include "can.h"
#include "dac.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "stdio.h"
#include "MotorCtrl.h"
#include "ScheduleTable.h"
#include "FDC2112.h"
#include <PressureSensor.h>
#include <pid.h>

uint8_t myTask03_Status ;

#ifdef  CiFenLi
#define CiFenLi_KeepStatic_time 1000

void StartTask03(void *argument)
{
	osDelay(10);
	printf("myTask03 starts! \r\n");

	Motor_Data_Init();
	Turntable_Position_Init();
	osDelay(100);
	if ( 0b00001011 == ALL_Motors_Init(0b00001011) ){
		printf("Motors Initialization Completed! \r\n");
		myTask03_Status = INITPASSSTATE;
	}
	else{
		myTask03_Status = INITFAILSTATE;
	}

	for(;;)
	{
		osDelay(1);
		switch (myTask03_Status)
		{
		case INITPASSSTATE:
			myTask03_Status = 0;
			break;

		case 0:
			osDelay(10);
			MotorMove_position(&Motor[1],TPMark[9]) ;
			osDelay(2000);
			printf("Please Put Bottle IN!--->THEN press KEY0\r\n");
			if (Motor[1].Status == 0){myTask03_Status=1;}
			break;

		case 1:
			if(KEY0_Pressed())
			{
				osDelay(20);
				if(KEY0_Pressed())
				{
					osDelay(20);
					while (KEY0_Pressed()){osDelay(1);}
					myTask03_Status = 2;
					printf("Key0 pressed!\r\n");
				}
			}
			break;

		case 2:
			MotorMove_position(&Motor[1],TPMark[4]) ;
			osDelay(1000);
			if (Motor[1].Status == 0){myTask03_Status=3;}
			break;

		case 3:
			Motor4_SuckInMode(500);
			osDelay(1000);
			Motor4_PushOutMode(500);
			osDelay(1000);
			myTask03_Status=4;
			break;

		case 4:
			if (Motor[4].Status == 0){myTask03_Status=5;}
			osDelay(10);
			break;

		case 5:
			DC_Motor_ON(&Motor[6],'A',85);
			osDelay(2000);
			DC_Motor_OFF(&Motor[6],'A');
			osDelay(1000);
			myTask03_Status = 6;
			break;

		case 6:
			MotorMove_position(&Motor[1],TPMark[5]) ;
			osDelay(CiFenLi_KeepStatic_time);
			if (Motor[1].Status == 0){myTask03_Status=7;}
			break;

		case 7:
			MotorMove_position(&Motor[1],TPMark[10]) ;
			osDelay(CiFenLi_KeepStatic_time);
			if (Motor[1].Status == 0){myTask03_Status=8;}
			break;

		case 8:
			MotorMove_position(&Motor[1],TPMark[1]) ;
			osDelay(CiFenLi_KeepStatic_time);
			if (Motor[1].Status == 0){myTask03_Status=9;}
			break;

		case 9:
			OUT4_ON();
			osDelay(50);
			DC_Motor_ON(&Motor[7],'A',20);
			MotorMove_position(&Motor[2],7300) ;
			osDelay(2000);
			if (Motor[2].Status == 0){myTask03_Status=10;}
			break;

		case 10:
			DC_Motor_OFF(&Motor[7],'A');
			osDelay(50);
			OUT4_OFF();
			MotorMove_position(&Motor[2],-20) ;
			osDelay(CiFenLi_KeepStatic_time);
			if (Motor[2].Status == 0){myTask03_Status=2;}
			break;

		case INITFAILSTATE:
			printf("[WRONG]All Motors Initialization FAILED!Please Check!\r\n");
			osDelay(10000);

			break;
		}
	}

}
#endif


#ifdef JiaYangZhen
#ifdef RZ_stepmotor
void StartTask03(void *argument)
{
	osDelay(10);
	printf("myTask03 starts! \r\n");

	Motor_Data_Init();
	osDelay(100);
	if ( 0b00000101 == ALL_Motors_Init(0b00000101) ){
		printf("Motors Initialization Completed! \r\n");
		myTask03_Status = INITPASSSTATE;
	}
	else{
		myTask03_Status = INITFAILSTATE;
	}

	for(;;)
	{
		osDelay(1);
		switch (myTask03_Status)
		{
		case INITPASSSTATE:
			osDelay(10);
			if(KEY0_Pressed())
			{
				osDelay(20);
				if(KEY0_Pressed())
				{
					osDelay(20);
					while (KEY0_Pressed()){osDelay(1);}
					myTask03_Status = 10;
					printf("Key0 pressed!\r\n");
				}
			}
			if(KEY1_Pressed())
			{
				osDelay(20);
				if(KEY1_Pressed())
				{
					osDelay(20);
					while (KEY1_Pressed()){osDelay(1);}
					myTask03_Status = 20;
					printf("Key1 pressed!\r\n");
				}
			}
			if(KEY2_Pressed())
			{
				osDelay(20);
				if(KEY2_Pressed())
				{
					osDelay(20);
					while (KEY2_Pressed()){osDelay(1);}
					myTask03_Status = 30;
					printf("Key2 pressed!\r\n");
				}
			}
			break;

//		case 9:
//			if ( Motor[3].Status == 0 ){
//				MotorMove_position(&Motor[3],1300);
//				myTask03_Status = 10;
//			}
//			osDelay(10);
//			break;

		case 10:
			if ( Motor[1].Status == 0 ){
				MotorMove_position(&Motor[1],5000);
				myTask03_Status = 11;
			}
			osDelay(10);
			break;

		case 11:
			if ( Motor[1].Status == 0 ){
				MotorMove_position(&Motor[1],1024);
				myTask03_Status = 12;
			}
			osDelay(10);
			break;

		case 12:
			if ( Motor[1].Status == 0 ){
				osDelay(2000);
				MotorMove_position(&Motor[1],5000);
				myTask03_Status = 13;
			}
			osDelay(10);
			break;
//
//		case 13:
//			if ( Motor[3].Status == 0 ){
//				MotorMove_position(&Motor[3],-40);
//				myTask03_Status = 10;
//			}
//			osDelay(10);
//			break;

		case 13:
			if ( Motor[1].Status == 0 ){
				MotorMove_position(&Motor[1],0);
				myTask03_Status = 14;
			}
			osDelay(10);
			break;

		case 14:
			if ( Motor[1].Status == 0 ){
				osDelay(800);
				MotorMove_position(&Motor[1],1024);
				osDelay(2000);
				myTask03_Status = 10;
			}
			osDelay(10);
			break;
		}
	}
}
#else
void StartTask03(void *argument)
{
	osDelay(10);
	printf("myTask03 starts! \r\n");

	Motor_Data_Init();
	osDelay(100);
	if ( 0b00001100 == ALL_Motors_Init(0b00001100) ){
		printf("Motors Initialization Completed! \r\n");
		myTask03_Status = INITPASSSTATE;
	}
	else{
		myTask03_Status = INITFAILSTATE;
	}

	Motor2_Enable();
	Motor3_Enable();
	Motor4_Enable();
	//myTask03_Status = INITPASSSTATE;

	for(;;)
	{
		osDelay(1);
		switch (myTask03_Status)
		{
		case INITPASSSTATE:
			osDelay(10);
			if(KEY0_Pressed())
			{
				osDelay(20);
				if(KEY0_Pressed())
				{
					osDelay(20);
					while (KEY0_Pressed()){osDelay(1);}
					myTask03_Status = 10;
					printf("Key0 pressed!\r\n");
				}
			}
			if(KEY1_Pressed())
			{
				osDelay(20);
				if(KEY1_Pressed())
				{
					osDelay(20);
					while (KEY1_Pressed()){osDelay(1);}
					myTask03_Status = 20;
					printf("Key1 pressed!\r\n");
				}
			}
			if(KEY2_Pressed())
			{
				osDelay(20);
				if(KEY2_Pressed())
				{
					osDelay(20);
					while (KEY2_Pressed()){osDelay(1);}
					myTask03_Status = 30;
					printf("Key2 pressed!\r\n");
				}
			}
			break;

		case 10:
			if ( (Motor[3].Status == 0) && (Motor[4].Status == 0) ){
				MotorMove_position(&Motor[3],108*16);
				myTask03_Status = 11;
			}
			osDelay(10);
			break;

		case 11:
			if ( (Motor[3].Status == 0) && (Motor[4].Status == 0) ){
				Motor4_SuckInMode(100);
				myTask03_Status = 12;
			}
			osDelay(10);
			break;

		case 12:
			if ( (Motor[3].Status == 0) && (Motor[4].Status == 0) ){
				osDelay(2000);
				myTask03_Status = 13;
			}
			osDelay(10);
			break;

		case 13:
			if ( (Motor[3].Status == 0) && (Motor[4].Status == 0) ){
				MotorMove_position(&Motor[3],-2*16);
				myTask03_Status = 14;
			}
			osDelay(10);
			break;

		case 14:
			if ( (Motor[3].Status == 0) && (Motor[4].Status == 0) ){
				MotorMove_position(&Motor[4],0);
				myTask03_Status = INITPASSSTATE;
			}
			osDelay(10);
			break;


		case 118:
			if ( (Motor[3].Status == 0) && (Motor[2].Status == 0) ){
				MotorMove_position(&Motor[2],478*16);   // 清洗柱位置
				myTask03_Status = 119;
			}
			osDelay(10);
			break;

		case 119:
			if ( Motor[2].Status == 0 ){
				MotorMove_position(&Motor[3],331*16);
				myTask03_Status = 120;
			}
			osDelay(10);
			break;

		case 120:
			if ( Motor[3].Status == 0 ){
				OUT1_ON();	// 加样针外壁清洗排除液体电磁阀
				OUT2_ON();	// 加样针外壁清洗注入液体电磁阀
				OUT5_ON();	// 柱塞泵加入液体电磁阀
				osDelay(500);
				DC_Motor_ON(&Motor[7],'A',100);
				osDelay(1000);
				DC_Motor_ON(&Motor[8],'A',30);
				DC_Motor_ON(&Motor[8],'B',30);
				osDelay(5000);
				myTask03_Status = 121;
			}
			osDelay(10);
			break;

		case 121:
			DC_Motor_OFF(&Motor[8],'A');
			DC_Motor_OFF(&Motor[8],'B');
			osDelay(2000);
			DC_Motor_OFF(&Motor[7],'A');
			osDelay(500);
			OUT1_OFF();
			OUT2_OFF();
			OUT5_OFF();
			myTask03_Status = 122;
			break;

		case 122:
			MotorMove_position(&Motor[3],-40);
			myTask03_Status = 123;
			break;

		case 123:
			if ( Motor[3].Status == 0 ){
				MotorMove_position(&Motor[2],-40);	//待确认
				myTask03_Status = 10;
			}
			osDelay(10);
			break;



		case 20:
			myTask03_Status = INITPASSSTATE;
			break;

		case 30:
			OUT1_ON();	// 加样针外壁清洗排除液体电磁阀
			OUT2_ON();	// 加样针外壁清洗注入液体电磁阀
			OUT5_ON();	// 柱塞泵加入液体电磁阀
			myTask03_Status = INITPASSSTATE;
			break;


		case INITFAILSTATE:
			printf("[WRONG]Motors Initialization FAILED!Please Check!\r\n");
			osDelay(10000);
			break;
		}
	}

}
#endif
#endif

#ifdef WeiLiuKong
void StartTask03(void *argument)
{
	osDelay(10);
	printf("myTask03 starts! \r\n");

	Motor_Data_Init();
	osDelay(100);
	if ( 0b00110000 == ALL_Motors_Init(0b00110000) ){
		printf("Motors Initialization Completed! \r\n");
		myTask03_Status = INITPASSSTATE;
	}
	else{
		myTask03_Status = INITFAILSTATE;
	}

	for(;;)
	{
		osDelay(1);
		switch (myTask03_Status)
		{
		case INITPASSSTATE:
			osDelay(10);
			if(KEY0_Pressed())
			{
				osDelay(20);
				if(KEY0_Pressed())
				{
					osDelay(20);
					while (KEY0_Pressed()){osDelay(1);}
					myTask03_Status = 10;
					printf("Key0 pressed!\r\n");
				}
			}
			if(KEY1_Pressed())
			{
				osDelay(20);
				if(KEY1_Pressed())
				{
					osDelay(20);
					while (KEY1_Pressed()){osDelay(1);}
					myTask03_Status = 20;
					printf("Key1 pressed!\r\n");
				}
			}
			if(KEY2_Pressed())
			{
				osDelay(20);
				if(KEY2_Pressed())
				{
					osDelay(20);
					while (KEY2_Pressed()){osDelay(1);}
					myTask03_Status = 30;
					printf("Key2 pressed!\r\n");
				}
			}
			break;

		case 10:
			if ( Motor[5].Status == 0 ){
				Motor[5].NumberofRads = 20;
				MotorMove_steps(&Motor[5]);
				myTask03_Status = 11;
			}
			osDelay(10);
			break;

		case 11:
			if ( Motor[5].Status == 0 ){
				Motor_Reset(&Motor[5]);
				myTask03_Status = 12;
			}
			osDelay(10);
			break;

		case 12:
			if ( Motor[5].Status == 0 ){
				MotorMove_position(&Motor[5],69);
				myTask03_Status = INITPASSSTATE;
			}
			osDelay(10);
			break;

		case 20:
			if ( Motor[6].Status == 0 ){
				MotorMove_position(&Motor[6],640);
				myTask03_Status = INITPASSSTATE;
			}
			osDelay(10);
			break;

		case 30:
			if ( Motor[6].Status == 0 ){
				MotorMove_position(&Motor[6],-5);
				myTask03_Status = INITPASSSTATE;
			}
			osDelay(10);
			break;





		case INITFAILSTATE:
			printf("[WRONG]Motors Initialization FAILED!Please Check!\r\n");
			osDelay(10000);
			break;
		}
	}

}
#endif

#ifdef DushuModule
void StartTask03(void *argument)
{
	osDelay(10);
	printf("myTask03 starts! \r\n");

	Motor_Data_Init();
	osDelay(100);
	if ( 0b00001000 == ALL_Motors_Init(0b00001000) ){
		printf("Motors Initialization Completed! \r\n");
		myTask03_Status = INITPASSSTATE;
	}
	else{
		myTask03_Status = INITFAILSTATE;
	}


	for(;;)
	{
		osDelay(1);
		switch (myTask03_Status)
		{
		case INITPASSSTATE:
			osDelay(10);
			if(KEY0_Pressed())
			{
				osDelay(20);
				if(KEY0_Pressed())
				{
					osDelay(20);
					while (KEY0_Pressed()){osDelay(1);}
					myTask03_Status = 10;
				}
			}
			if(KEY1_Pressed())
			{
				osDelay(20);
				if(KEY1_Pressed())
				{
					osDelay(20);
					while (KEY1_Pressed()){osDelay(1);}
					myTask03_Status = 20;
				}
			}
			if(KEY2_Pressed())
			{
				osDelay(20);
				if(KEY2_Pressed())
				{
					osDelay(20);
					while (KEY2_Pressed()){osDelay(1);}
					myTask03_Status = 30;
				}
			}
			break;

		case 10:	//	KEY0- 灌注液体 吸液uL-注液uL，过程中不进行延时和读数
			if (Motor[4].Status == 0){
				Motor4_SuckInMode(100);
				myTask03_Status = 11;
			}
			osDelay(10);
			break;
		case 11:
			if (Motor[4].Status == 0){
				Motor4_PushOutMode(100);
				myTask03_Status=INITPASSSTATE;
			}
			osDelay(10);
			break;

		case 20:	//	KEY1- 直接读书10秒，不进行洗液和注液
			printf("-7\n");
			osDelay(50);
			CH297_Module_START();
			osDelay(10800);
			myTask03_Status = 21;
			break;

		case 21:
			CH297_Module_STOP();
			osDelay(50);
			printf("-1\n");
			osDelay(10);
			myTask03_Status = INITPASSSTATE;
			break;

		case 30:	//	KEY2- 吸液200uL-开始计数-注液200uL-持续7秒后输出结果
			if (Motor[4].Status == 0){
				Motor4_SuckInMode(200);
				myTask03_Status = 31;
			}
			osDelay(10);
		case 31:
			if (Motor[4].Status == 0){
				printf("-7\n");
				osDelay(50);
				CH297_Module_START();
				myTask03_Status = 32;
			}
			osDelay(10);
			break;
		case 32:
			osDelay(490);
			Motor4_PushOutMode(200);
			myTask03_Status=33;
			break;
		case 33:
			osDelay(10000);
			//osDelay(60000);
			CH297_Module_STOP();
			osDelay(50);
			printf("-1\n");
			osDelay(10);
			myTask03_Status=INITPASSSTATE;
			break;



		case INITFAILSTATE:
			printf("[WRONG]Motors Initialization FAILED!Please Check!\r\n");
			osDelay(10000);
			break;
		}
	}

}
#endif

#ifdef L298N_StepMotorCtrl
void StartTask03(void *argument)
{
	osDelay(10);
	printf("myTask03 starts! \r\n");

	Motor_Data_Init();
	VM5_Enable_A();	VM5_Enable_B();
	VM6_Enable_A();	VM6_Enable_B();
	Motor6_Release();
	Motor6_MicroSteps_Table_Init();
	myTask03_Status = INITPASSSTATE;

	for(;;)
	{
		osDelay(1);
		switch (myTask03_Status)
		{
		case INITPASSSTATE:
			osDelay(10);
			if(KEY0_Pressed())
			{
				osDelay(20);
				if(KEY0_Pressed())
				{
					osDelay(20);
					while (KEY0_Pressed()){osDelay(1);}
					myTask03_Status = 10;
				}
			}
			if(KEY1_Pressed())
			{
				osDelay(20);
				if(KEY1_Pressed())
				{
					osDelay(20);
					while (KEY1_Pressed()){osDelay(1);}
					myTask03_Status = 20;
				}
			}
			if(KEY2_Pressed())
			{
				osDelay(20);
				if(KEY2_Pressed())
				{
					osDelay(20);
					while (KEY2_Pressed()){osDelay(1);}
					myTask03_Status = 30;
				}
			}
			break;

		case 10:
			Start_DMA_ADC1_CH10CH11();
			myTask03_Status = INITPASSSTATE;
			break;

		case 20:
			for (uint16_t i=0 ; i<30 ; i++){
				printf("\t***ADC1 Values: %d, %d ***\r\n",get_ADC1_Current_Phase(0),get_ADC1_Current_Phase(1));
				//printf("\t***ADC1 Values: %d, %d ***\r\n",ADC_Values[0],ADC_Values[1]);
				osDelay(200);
			}
			myTask03_Status = INITPASSSTATE;
			break;

		case 30:
			STOP_DMA_ADC1_CH10CH11();
			myTask03_Status = INITPASSSTATE;
			break ;

		}
	}

}
#endif


#ifdef DuoTongDao

uint8_t DTD_Motors_Init(void)
{
	printf("DTD Reseting Motors:3-5-6-2 ...\r\n");

	Motor3_Enable();	// reset motor3 and goto external side
	if ( !(Motor_Reset(&Motor[3])) ){
		Motor3_Disable();
		printf("[WRONG!]Motor3 reset failed! ...\r\n");\
		return FAIL ;
	}
	HAL_Delay(200);
	MotorMove_position(&Motor[3],data_V0.Position_motor3_external);
	HAL_Delay(200);
	while(Motor[3].Status){
		HAL_Delay(100);
	}

	VM5_Enable_A();	VM5_Enable_B();	// reset motor5 and goto external side
	if ( !(Motor_Reset(&Motor[5])) ){
		VM5_Disable_A(); VM5_Disable_B();
		printf("[WRONG!]Motor5 reset failed! ...\r\n");\
		return FAIL ;
	}

	VM6_Enable_A();	VM6_Enable_B();	// reset motor6
	if ( !(Motor_Reset(&Motor[6])) ){
		VM6_Disable_A(); VM6_Disable_B();
		printf("[WRONG!]Motor6 reset failed! ...\r\n");\
		return FAIL ;
	}

	HAL_Delay(200);
	MotorMove_position(&Motor[5],data_V0.Position_motor5_external);
	HAL_Delay(200);
	while(Motor[5].Status){
		HAL_Delay(100);
	}


	Motor2_Enable();	// reset motor2 and goto top one
	if ( !(Motor_Reset(&Motor[2])) ){
		Motor2_Disable();
		printf("[WRONG!]Motor2 reset failed! ...\r\n");\
		return FAIL ;
	}
	HAL_Delay(200);
	MotorMove_position(&Motor[2],VPMark[6]);
	HAL_Delay(200);
	while(Motor[2].Status){
		HAL_Delay(100);
	}

	return SUCCESS ;
}

uint8_t DTD_All_Motors_Idle(void)
{
	osDelay(100);
	if ( (!Motor[5].Status) & (!Motor[6].Status) & (!Motor[3].Status) & (!Motor[2].Status) ){
		return 1 ;
	}
	else{
		return 0 ;
	}
}

uint8_t DTD_Motors_Standby_State(void)
{
	HAL_Delay(100);
	MotorMove_position(&Motor[3],data_V0.Position_motor3_external);
	HAL_Delay(100);
	while(Motor[3].Status){
		HAL_Delay(100);
	}

	HAL_Delay(100);
	MotorMove_position(&Motor[6],data_V0.Position_motor6_PushRod_reset);
	HAL_Delay(100);
	while(Motor[6].Status){
		HAL_Delay(100);
	}

	HAL_Delay(100);
	MotorMove_position(&Motor[5],data_V0.Position_motor5_external);
	HAL_Delay(100);
	while(Motor[5].Status){
		HAL_Delay(100);
	}
	return SUCCESS;
}

uint8_t 	DTD_StripIn_State = 0 ;
uint32_t 	DTD_CNT_i;

void StartTask03(void *argument)
{
	osDelay(10);
	printf("myTask03 starts! \r\n");

	Motor_Data_Init();
	DuoTongDao_Position_Init();
	osDelay(300);
	if ( DTD_Motors_Init() ){
		printf("Motors Initialization Completed! \r\n");
		myTask03_Status = INITPASSSTATE;
	}
	else{
		myTask03_Status = INITFAILSTATE;
	}

//	Motor2_Enable();
//	Motor3_Enable();
//	VM5_Enable_A();	VM5_Enable_B();
//	VM6_Enable_A();	VM6_Enable_B();
//	myTask03_Status = INITPASSSTATE;

	uint8_t temp_n = 0 ;

	for(;;)
	{
		osDelay(1);
		switch (myTask03_Status)
		{
		case INITPASSSTATE:
			osDelay(10);
			if(KEY0_Pressed())
			{
				osDelay(20);
				if(KEY0_Pressed())
				{
					osDelay(20);
					while (KEY0_Pressed()){osDelay(1);}
					myTask03_Status = 10;
					printf("Key0 pressed!\r\n");
				}
			}
			if(KEY1_Pressed())
			{
				osDelay(20);
				if(KEY1_Pressed())
				{
					osDelay(20);
					while (KEY1_Pressed()){osDelay(1);}
					myTask03_Status = 20;
					printf("Key1 pressed!\r\n");
				}
			}
			if(KEY2_Pressed())
			{
				osDelay(20);
				if(KEY2_Pressed())
				{
					osDelay(20);
					while (KEY2_Pressed()){osDelay(1);}
					myTask03_Status = 130;
					printf("Key2 pressed!\r\n");
				}
			}
			break;

		case 10:
			osDelay(300);
			if (Motor[2].Status == 0){
				MotorMove_position(&Motor[2],VPMark[temp_n]);
				if(temp_n >= 7)
					temp_n =  0 ;
				else
					temp_n = temp_n +1 ;
				myTask03_Status=INITPASSSTATE;
			}
		break;

		case 20:	//行进到准备姿态，持续检测试剂条插入
			osDelay(1);
			if(DTD_All_Motors_Idle()){
				if (DTD_Motors_Standby_State()) {
					printf("DTD in Standby state,waiting strip in. \r\n");
					myTask03_Status = 21;
				}
			}
		break;

		case 21:
			osDelay(1);
			switch(DTD_StripIn_State)
			{
				case 0:
					if ( (Strip_Triggerd)&&(Strip_UnBlocked) ){
						for( DTD_CNT_i=0 ; (Strip_Triggerd)&(Strip_UnBlocked) ; DTD_CNT_i++){
							HAL_Delay(1);
						}
						if(DTD_CNT_i > 200){
							DTD_StripIn_State = 1 ;
						}
						else{
							DTD_StripIn_State = 0 ;
						}
						printf("DTD_CNT_i=%ld  ; DTD_StripIn_State=%d   \r\n ", DTD_CNT_i,DTD_StripIn_State);
					}
				break;

				case 1:
					if ( (Strip_Triggerd)&&(Strip_Blocked) ){
						for( DTD_CNT_i=0 ; (Strip_Triggerd)&(Strip_Blocked) ; DTD_CNT_i++){
							HAL_Delay(1);
						}
						if(DTD_CNT_i > 100){
							DTD_StripIn_State = 2 ;
						}
						else{
							DTD_StripIn_State = 0 ;
						}
						printf("DTD_CNT_i=%ld  ; DTD_StripIn_State=%d   \r\n ", DTD_CNT_i,DTD_StripIn_State);
					}
				break;

				case 2:
					if ( (Strip_UnTriggerd)&&(Strip_Blocked) ){
						for( DTD_CNT_i=0 ; (Strip_UnTriggerd)&(Strip_Blocked) ; DTD_CNT_i++){
							HAL_Delay(1);
							if(DTD_CNT_i > 1000){
								DTD_StripIn_State = 3 ;
								break;
							}
						}
					}
				break;

				case 3:
					printf("Strip inserted! Begin to detect... \r\n");
					DTD_StripIn_State = 0 ;
					myTask03_Status = 22;
					osDelay(500);
				break;

			}
		break;

		case 22:
			osDelay(1);
			if( DTD_All_Motors_Idle() ){
				MotorMove_position(&Motor[5],data_V0.Position_motor5_internal);
				myTask03_Status = 23;
			}
		break;

		case 23:
			osDelay(1);
			if( DTD_All_Motors_Idle() ){
				MotorMove_position(&Motor[6],data_V0.Position_motor6_PushRod_push);
				myTask03_Status = 24;
			}
		break;

		case 24:
			osDelay(1);
			if( DTD_All_Motors_Idle() ){
				osDelay(800);
				MotorMove_position(&Motor[3],data_V0.Position_motor3_storage);
				myTask03_Status = 25;
			}
		break;

		case 25:
			osDelay(1);
			if( DTD_All_Motors_Idle() ){
				osDelay(800);
				MotorMove_position(&Motor[3],data_V0.Position_motor3_detect);
				myTask03_Status = 26;
			}
		break;

		case 26:
			osDelay(1);
			if( DTD_All_Motors_Idle() ){
				osDelay(1000);
				MotorMove_position_lowspeed(&Motor[3],data_V0.Position_motor3_reset, 1);
				myTask03_Status = 27;
			}
		break;

		case 27:
			osDelay(1);
			if(DTD_All_Motors_Idle()){
				if (DTD_Motors_Standby_State()) {
					myTask03_Status = 21;
				}
			}
		break;












		case 130:	//老化测试
			myTask03_Status = INITPASSSTATE;
		break;


		case INITFAILSTATE:
			printf("[WRONG]Motors Initialization FAILED!Please Check!\r\n");
			osDelay(10000);
			break;
		}
	}
}

#endif

#ifdef QuanxiePVctrl

extern float SetValue_Update ;
extern float pid_Update[3];

void StartTask03(void *argument)
{
	osDelay(10);
	printf("myTask03 starts! \r\n");

	Motor_Data_Init();
	osDelay(100);
	if ( Init_SSCDANT250K_Pressure() ){
		printf("I2C Initialization Completed! \r\n");
		myTask03_Status = INITPASSSTATE;
	}
	else{
		myTask03_Status = INITFAILSTATE;
	}

	SetValue_Update = 82.5 ;// target
	pid_Update[0] = 80 ; 	// kp
	pid_Update[1] = 0.3 ; 	// ki
	pid_Update[2] = 20 ; 	// kd

	PID_Clear(&pid1);
	HAL_Delay(1);
	PID_Init(&pid1,pid_Update[0],pid_Update[1],pid_Update[2],10000,10000);

	for(;;)
	{
		osDelay(1);
		switch (myTask03_Status)
		{
		case INITPASSSTATE:
			osDelay(10);
			if(KEY0_Pressed()){
				osDelay(20);
				if(KEY0_Pressed())
				{
					osDelay(20);
					while (KEY0_Pressed()){osDelay(1);}
					myTask03_Status = 10;
					printf("Key0 pressed!\r\n");
				}
			}
			if(KEY1_Pressed()){
				osDelay(20);
				if(KEY1_Pressed())
				{
					osDelay(20);
					while (KEY1_Pressed()){osDelay(1);}
					myTask03_Status = 20;
					printf("Key1 pressed!\r\n");
				}
			}
			if(KEY2_Pressed()){
				osDelay(20);
				if(KEY2_Pressed())
				{
					osDelay(20);
					while (KEY2_Pressed()){osDelay(1);}
					myTask03_Status = 30;
					printf("Key2 pressed!\r\n");
				}
			}
			break;

		case 10:
			Pressure_Data_Float = Read_Pressure_Average_ntimes(3) ;
			myTask03_Status = 11;
		break;

		case 11:
			PID_SingleCalc(&pid1, SetValue_Update, Pressure_Data_Float);
			DC_Motor_ON(&Motor[8],'A',pid1.output);
			myTask03_Status = 12;
		break;

		case 12:
			//printf("%.2f,%f\r\n",Pressure_Data_Float,pid1.output);
			printf("%.2f\r\n",Pressure_Data_Float);
			myTask03_Status = 10;
		break;


		case INITFAILSTATE:
			printf("[WRONG]IIC Initialization FAILED!Please Check!\r\n");
			osDelay(10000);
			break;

		}
	}

}






#endif




