
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


#ifdef  CiFenLi
#define CiFenLi_KeepStatic_time 1000

void StartTask03(void *argument)
{
	osDelay(10);
	uint8_t myTask03_Status ;
	printf("myTask03 starts! \r\n");

	Motor_Data_Init();
	Turntable_Position_Init();
	osDelay(300);
	myTask03_Status = ALL_Motors_Init();
	osDelay(300);

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
			printf("Please Put Bottle IN!^^^^^^THEN press KEY0\r\n");
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
			osDelay(200);
			Motor4_PushOutMode(500);
			osDelay(500);
			if (Motor[4].Status == 0){myTask03_Status=4;}
			break;

		case 4:
			DC_Motor_Move() ;
			osDelay(2000);
			DC_Motor_Stop() ;
			osDelay(1000);
			myTask03_Status = 5;
			break;

		case 5:
			MotorMove_position(&Motor[1],TPMark[5]) ;
			osDelay(CiFenLi_KeepStatic_time);
			if (Motor[1].Status == 0){myTask03_Status=6;}
			break;

		case 6:
			MotorMove_position(&Motor[1],TPMark[10]) ;
			osDelay(CiFenLi_KeepStatic_time);
			if (Motor[1].Status == 0){myTask03_Status=7;}
			break;

		case 7:
			MotorMove_position(&Motor[1],TPMark[1]) ;
			osDelay(1000);
			if (Motor[1].Status == 0){myTask03_Status=8;}
			break;

		case 8:
			MotorMove_position(&Motor[2],3800) ;
			osDelay(1000);
			if (Motor[2].Status == 0){myTask03_Status=9;}
			break;

		case 9:
			Motor5_SuckOut_ON();
			MotorMove_position(&Motor[2],7000) ;
			osDelay(2000);
			if (Motor[2].Status == 0){myTask03_Status=10;}
			break;

		case 10:
			Motor5_SuckOut_OFF();
			MotorMove_position(&Motor[2],0) ;
			osDelay(1000);
			if (Motor[2].Status == 0){myTask03_Status=0;}
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
void StartTask03(void *argument)
{
	osDelay(10);
	uint8_t myTask03_Status ;
	printf("myTask03 starts! \r\n");

	Motor_Data_Init();
	osDelay(300);
	myTask03_Status = ALL_Motors_Init();
	osDelay(300);

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
					myTask03_Status = 1;
					printf("Key0 pressed!\r\n");
				}
			}
			if(KEY2_Pressed())
			{
				osDelay(20);
				if(KEY2_Pressed())
				{
					osDelay(20);
					while (KEY2_Pressed()){osDelay(1);}
					myTask03_Status = 22;
					printf("Key2 pressed!\r\n");
				}
			}
			break;

		case 1:
			osDelay(100);
#ifdef JiaYangZhen_EncoderMode
			MotorMove_position_Enocder(&Motor[2],3100) ;
#else
			MotorMove_position(&Motor[2],2480*4) ;
#endif
			osDelay(3600);
			if (Motor[2].Status == 0){myTask03_Status = 4;}
			break;

		case 2:
			osDelay(100);
#ifdef JiaYangZhen_EncoderMode
			MotorMove_position_Enocder(&Motor[3],1800) ;
#else
			MotorMove_position(&Motor[3],1440*4) ;
#endif
			osDelay(1500);
			if (Motor[3].Status == 0){myTask03_Status = 3;}
			break;

		case 3:
#ifdef JiaYangZhen_EncoderMode
			MotorMove_position_Enocder(&Motor[3],-30) ;
#else
			MotorMove_position(&Motor[3],-80) ;
#endif
			osDelay(1500);
			if (Motor[3].Status == 0){myTask03_Status = 4;}
			break;

		case 4:
			osDelay(100);
#ifdef JiaYangZhen_EncoderMode
			MotorMove_position_Enocder(&Motor[2],-30) ;
#else
			MotorMove_position(&Motor[2],-80) ;
#endif
			osDelay(3000);
			if (Motor[2].Status == 0){myTask03_Status = 1;}
			break;

		case 22:
			DetectionTask_STATE = Cap0_Sample_State;
			printf("---Enter Liquid following mode---\r\n");
			HAL_TIM_Base_Start_IT(Motor[3].htim_x);
			myTask03_Status = 23;
			break;

		case 23:
			if(KEY2_Pressed())
			{
				osDelay(20);
				if(KEY2_Pressed())
				{
					osDelay(20);
					while (KEY2_Pressed()){osDelay(1);}
					myTask03_Status = 24;
					printf("Key2 pressed!\r\n");
				}
			}
			break;

		case 24:
			HAL_TIM_Base_Stop_IT(Motor[3].htim_x);
			DetectionTask_STATE = INITPASSSTATE;
			myTask03_Status = INITPASSSTATE;
			printf("---Close Liquid following mode---\r\n");
			break;

		case INITFAILSTATE:
			printf("[WRONG]All Motors Initialization FAILED!Please Check!\r\n");
			osDelay(10000);

			break;
		}
	}

}
#endif


