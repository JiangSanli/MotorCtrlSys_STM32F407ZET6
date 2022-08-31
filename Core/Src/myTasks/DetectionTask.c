
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

float Cap_Value[2] ;    		// 直接读出并转换的电容值
float Cap_Value_Calibrated[2] ;	// 校准后的电容值，正常状态下为0
float Calibration_Value[2] ;	// 校准值，为常规状态下的电容值均值，计算绝对电容值需要减去该值
uint8_t Follow_state ;

uint8_t DetectionTask_STATE ;
//float Diff_Cap ;

uint8_t init_Calibration_Value(uint8_t index)
{
	Calibration_Value[index] = 0;
	float temp_value = 0;
	uint8_t i=0;
	for (i=1 ; i<=10 ; i++){
		temp_value = Cap_Calculate(index);
		HAL_Delay(I2C_Read_Delay);
		if (temp_value){	// 如果Cap_Calculate返回0，则表示读取I2C失败
			Calibration_Value[index] = Calibration_Value[index] + temp_value;
			//printf("temp_value:%.2f\r\n",temp_value);
		}
		else{
			printf("[WRONG]init_Calibration_Value FAILED!\r\n");
			return INITFAILSTATE ;
		}
	}
	Calibration_Value[index] = Calibration_Value[index] / 10 ;
	printf("init_Calibration_Value Completed! Calibration_Value[%d]:%.2f\r\n",index,Calibration_Value[index]);
	return INITPASSSTATE ;
}

float get_Calibrated_Value(uint8_t index)
{
	Cap_Value[index] = Cap_Calculate(index);
	return ( Cap_Value[index] - Calibration_Value[index] ) ;
}

void StartDetectionTask(void *argument)
{
	osDelay(50);
	printf("DetectionTask starts! \r\n");

	Init_DoubleChannel_FDC2212();
	osDelay(100);

	DetectionTask_STATE = init_Calibration_Value(0);
	osDelay(100);

	for(;;)
	{
		osDelay(1);
		switch (DetectionTask_STATE)
		{
		case INITPASSSTATE:
			osDelay(10);
			if(KEY1_Pressed())
			{
				osDelay(20);
				if(KEY1_Pressed())
				{
					osDelay(20);
					while (KEY1_Pressed()){osDelay(1);}
					DetectionTask_STATE = Cap0_Sample_State;
					printf("Key1 pressed!\r\n");
				}
			}
			break;

		case Cap0_Sample_State:
			Cap_Value_Calibrated[0] = get_Calibrated_Value(0);
			if (Cap_Value_Calibrated[0] < 2){
				Motor3_Nreset_direction;
				Motor[3].StepperSpeedTMR = 33 ;
				Follow_state = 1;
			}
			else if ( (Cap_Value_Calibrated[0] > 2) && (Cap_Value_Calibrated[0] <= 3) ){
				Follow_state = 2;
			}
			else {
				Motor3_reset_direction;
				Motor[3].StepperSpeedTMR = 50 - 7*(Cap_Value_Calibrated[0]-3) ;
				Follow_state = 3;
			}
			//printf("follow:%d\r\n",Follow_state);
			//printf("Cap_Value_Calibrated[0]:%.2f \r\n",Cap_Value_Calibrated[0]);
			//osDelay(2);

			break;

		case INITFAILSTATE:
			printf("[WRONG]init_Calibration_Value FAILED,reCalibrating...\r\n");
			osDelay(3000);
			DetectionTask_STATE = init_Calibration_Value(0);

		}

	}

}



