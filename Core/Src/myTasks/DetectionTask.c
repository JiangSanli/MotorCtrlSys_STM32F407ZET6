
/*
 * DetectionTask - 用于液面检测和跟随
 * 更新日志：
 * 2022.08.08 - 新建
 *
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



void StartDetectionTask(void *argument)
{
	osDelay(50);
	printf("DetectionTask starts! \r\n");

	uint8_t DetectionTask_STATE = 0;
	Init_DoubleChannel_FDC2212();
	osDelay(100);

	uint16_t FDC2112_RegBuffer ;
	float Cap_Value0 ;
	float Cap_Value1 ;
	float Calibration_Cap ;

	for(;;)
	{
		osDelay(1);
		switch (DetectionTask_STATE)
		{
		case 0:
			osDelay(10);
			if(KEY1_Pressed())
			{
				osDelay(20);
				if(KEY1_Pressed())
				{
					osDelay(20);
					while (KEY1_Pressed()){osDelay(1);}
					DetectionTask_STATE = 20;
					printf("Key0 pressed!\r\n");
				}
			}
			break;

		case 10:
			FDC2112_RegBuffer = FDC2112_Read_Reg_I2C(0x0C);
			osDelay(200);
			DetectionTask_STATE = 0;
			printf("***FDC2112_RegBuffer:0x%x\r\n",FDC2112_RegBuffer);
			break;

		case 20:
			Cap_Value0 = Cap_Calculate(0);
			osDelay(2);
			Cap_Value1 = Cap_Calculate(1);
			Calibration_Cap = Cap_Value0 - Cap_Value1;
			printf("***Cap_Value0 = %.2f    Cap_Value1 = %.2f --->  Calibration_Cap = %.2f  ***\r\n",Cap_Value0,Cap_Value1,Calibration_Cap);
			osDelay(200);
			//DetectionTask_STATE = 0;
			break;

		}
	}

}
