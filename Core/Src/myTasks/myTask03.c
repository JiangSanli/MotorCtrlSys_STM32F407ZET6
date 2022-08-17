
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
	//myTask03_Status = ALL_Motors_Init();
	osDelay(300);

	uint32_t Encoder3_counter ;
	uint8_t Direction_Encoder3 ;
	uint32_t Encoder2_counter ;
	uint8_t Direction_Encoder2 ;

	//微流控设备暂无光电传感器等0位标志，上电时认为初始位置为0为
	Motor[5].StepPosition = 0 ;
	Motor[6].StepPosition = 0 ;

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
			MotorMove_position_Enocder(&Motor[2],2800) ;
			osDelay(2000);
			if (Motor[2].Status == 0){myTask03_Status = 2;}
			break;

		case 2:
			osDelay(100);
			MotorMove_position_Enocder(&Motor[3],1800) ;
			osDelay(1500);
			if (Motor[3].Status == 0){myTask03_Status = 3;}
			break;

		case 3:
			MotorMove_position_Enocder(&Motor[3],300) ;
			osDelay(1500);
			if (Motor[3].Status == 0){myTask03_Status = 4;}
			break;

		case 4:
			osDelay(100);
			MotorMove_position_Enocder(&Motor[2],300) ;
			osDelay(2000);
			if (Motor[2].Status == 0){myTask03_Status = 1;}
			break;

		case 22:
			osDelay(2000);
			Encoder2_counter = __HAL_TIM_GET_COUNTER(&htim4);
			Direction_Encoder2 = __HAL_TIM_IS_TIM_COUNTING_DOWN(&htim4);
			Encoder3_counter = __HAL_TIM_GET_COUNTER(&htim3);
			Direction_Encoder3 = __HAL_TIM_IS_TIM_COUNTING_DOWN(&htim3);
			printf("***Encoder2_counter = %ld , Direction_Encoder2 = %d  Motor[2].StepPosition : %ld***\r\n",Encoder2_counter,Direction_Encoder2,Motor[2].StepPosition);
			printf("***Encoder3_counter = %ld , Direction_Encoder3 = %d  Motor[3].StepPosition : %ld***\r\n",Encoder3_counter,Direction_Encoder3,Motor[3].StepPosition);

			break;

		case INITFAILSTATE:
			printf("[WRONG]All Motors Initialization FAILED!Please Check!\r\n");
			osDelay(10000);

			break;
		}
	}

}
#endif


