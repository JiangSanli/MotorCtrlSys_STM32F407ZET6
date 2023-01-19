
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
	if ( 0b00001110 == ALL_Motors_Init(0b00001110) ){
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
			if (Motor[2].Status == 0){
				MotorMove_position(&Motor[2],82*16);	//1312试剂盒位置
				Motor4_SuckInMode(10);
				myTask03_Status = 11;
			}
			osDelay(10);
			break;

		case 11:
			if ( (Motor[2].Status == 0) && (Motor[4].Status == 0) ){
				DetectionTask_STATE = Cap0_Sample_State;
				//使用IO液面检测模块
//				Follow_state = 1;
//				Motor3_Nreset_direction;
				printf("---Enter Liquid following mode---\r\n");
				Motor[3].Status = 1;
				HAL_TIM_Base_Start_IT(Motor[3].htim_x);
				myTask03_Status = 12;
			}
			osDelay(10);
			break;

		case 12:
			for (uint32_t t=1 ; Follow_state == 2 ; t++ ){
				osDelay(1);
				if(t > 50){
					Motor4_SuckInMode(230);
					myTask03_Status = 13;
					break;
				}
			}
//			if (Motor[3].Status == 0){
//				DetectionTask_STATE = INITPASSSTATE;
//				Motor4_SuckInMode(200);
//				myTask03_Status = 13;
//			}
			osDelay(10);
			break;

		case 13:
			if (Motor[4].Status == 0){
				HAL_TIM_Base_Stop_IT(Motor[3].htim_x);
				Motor[3].Status = 0;
				DetectionTask_STATE = INITPASSSTATE;
				printf("---Close Liquid following mode---\r\n");
				osDelay(200);
				MotorMove_position(&Motor[3],-40);
				myTask03_Status = 14;
			}
			osDelay(10);
			break;

		case 14:
			if (Motor[3].Status == 0){
				MotorMove_position(&Motor[2],134*16); 	// 2144第一个反应杯位置
				myTask03_Status = 15;
			}
			osDelay(10);
			break;

		case 15:
			if (Motor[2].Status == 0){
				MotorMove_position(&Motor[3],144*16);
				myTask03_Status = 16;
			}
			osDelay(10);
			break;

		case 16:
			if (Motor[3].Status == 0){
				Motor4_PushOutMode(230);
				osDelay(2000);
				myTask03_Status = 17;
			}
			osDelay(10);
			break;

		case 17:
			if (Motor[3].Status == 0){
				MotorMove_position(&Motor[3],-40);
				myTask03_Status = 118;
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
			DetectionTask_STATE = 70;
			printf("---Capture Cap Value Begin---\r\n");
//			Motor[3].Status = 1;
//			HAL_TIM_Base_Start_IT(Motor[3].htim_x);
			myTask03_Status = INITPASSSTATE;
			break;

		case 30:
			OUT1_ON();	// 加样针外壁清洗排除液体电磁阀
			OUT2_ON();	// 加样针外壁清洗注入液体电磁阀
			OUT5_ON();	// 柱塞泵加入液体电磁阀
//			HAL_TIM_Base_Stop_IT(Motor[3].htim_x);
//			Motor[3].Status = 0;
//			DetectionTask_STATE = INITPASSSTATE;
//			printf("---Checking following mode Over!---\r\n");
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

		case 10:	//	KEY0： 灌注液体 吸液200uL-注液200uL，过程中不进行延时和读数
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

		case 20:	//	KEY1： 直接读书10秒，不进行洗液和注液
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

		case 30:	//	KEY2： 正常流程- 吸液200uL-开始计数-注液200uL-持续7秒后输出结果
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
void StartTask03(void *argument)
{
	osDelay(10);
	printf("myTask03 starts! \r\n");

	Motor_Data_Init();
	Vertical_Position_Init();
	osDelay(100);
	if ( 0b00000110 == ALL_Motors_Init(0b00000110) ){
		printf("Motors Initialization Completed! \r\n");
		myTask03_Status = INITPASSSTATE;
	}
	else{
		myTask03_Status = INITFAILSTATE;
	}
	VM5_Enable_A();	VM5_Enable_B();
	VM6_Enable_A();	VM6_Enable_B();
	uint8_t motor2_next_state = 10;
	uint8_t motor3_next_state = 20;

//	Motor2_Enable();
//	Motor3_Enable();
//	myTask03_Status = INITPASSSTATE;

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
					myTask03_Status = motor2_next_state;
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
					myTask03_Status = motor3_next_state;
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
			if (Motor[2].Status == 0){
				MotorMove_position(&Motor[2],VPMark[0]);
				motor2_next_state = 11;
				myTask03_Status=INITPASSSTATE;
			}
			break;

		case 11:
			if (Motor[2].Status == 0){
				MotorMove_position(&Motor[2],VPMark[2]);
				motor2_next_state = 12;
				myTask03_Status=INITPASSSTATE;
			}
			break;

		case 12:
			if (Motor[2].Status == 0){
				MotorMove_position(&Motor[2],-16);
				motor2_next_state = 10 ;
				myTask03_Status=INITPASSSTATE;
			}
			break;

		case 20:
			if (Motor[3].Status == 0){
				MotorMove_position(&Motor[3],19200); //刚好推进试剂储藏处
				motor3_next_state = 21 ;
				myTask03_Status=INITPASSSTATE;
			}
			break;

		case 21:
			if (Motor[3].Status == 0){
				MotorMove_position(&Motor[3],-16);
				motor3_next_state = 20 ;
				myTask03_Status=INITPASSSTATE;
			}
			break;

		case 30:
			if (Motor[3].Status == 0){
				MotorMove_position(&Motor[3],61680);
				motor3_next_state = 22 ;
				myTask03_Status=INITPASSSTATE;
			}
			break;





		case INITFAILSTATE:
			printf("[WRONG]Motors Initialization FAILED!Please Check!\r\n");
			osDelay(10000);
			break;
		}
	}
}




#endif




