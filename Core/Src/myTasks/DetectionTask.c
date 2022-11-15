
/*
 * DetectionTask - 用于液面检测和跟随
 * 更新日志：
 * 2022.08.08 - 新建
 * 2022.09	-	支持I2C电容检测芯片FDC2112进行液面检测
 * 2022.09 	-	支持CH297模块
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

#ifndef DushuModule
uint8_t init_Calibration_Value(uint8_t index)
{
	Calibration_Value[index] = 0;
	float temp_value = 0;
	for (uint8_t i=1 ; i<=100 ; i++){
		temp_value = Cap_Calculate(index);
		HAL_Delay(1);
		if (temp_value < 100000000){	// 如果Cap_Calculate返回inf，则表示读取I2C失败
			Calibration_Value[index] = Calibration_Value[index] + temp_value;
		}
		else{
			printf("[WRONG]init_Calibration_Value FAILED!\r\n");
			return INITFAILSTATE ;
		}
	}
	Calibration_Value[index] = Calibration_Value[index] / 100 ;
	printf("CapDetect_Calibration_Value Initialization Completed! Calibration_Value[%d]:%.2f\r\n",index,Calibration_Value[index]);
	return INITPASSSTATE ;
}

float get_Calibrated_Value(uint8_t index)  // 读取5次取平均
{
	float Cap_temp_Value = 0;
	float temp_value = 0;
	for (uint8_t i=1 ; i<=3 ; i++){
		temp_value = Cap_Calculate(index);
		HAL_Delay(1);
		if (temp_value < 100000000){	// 如果Cap_Calculate返回inf，则表示读取I2C失败
			Cap_temp_Value = Cap_temp_Value + temp_value;
		}
		else{
			printf("[WRONG]Cap_Value Capture FAILED!\r\n");
			return 0 ;
		}
	}
	Cap_temp_Value = Cap_temp_Value / 3 ;
	return ( Cap_temp_Value - Calibration_Value[index] ) ;
}

void StartDetectionTask(void *argument)
{
	osDelay(50);
	printf("DetectionTask starts! \r\n");

	Init_DoubleChannel_FDC2212();
	osDelay(100);
	//DetectionTask_STATE = init_Calibration_Value(0);
	osDelay(100);
	DetectionTask_STATE = INITPASSSTATE;

	for(;;)
	{
		osDelay(1);
		switch (DetectionTask_STATE)
		{
		case 0:
			if ( myTask03_Status == INITPASSSTATE){
				Motor4_SuckInMode(10);
				DetectionTask_STATE = 1;
			}
			osDelay(10);
			break;

		case 1:
			if( Motor[4].Status == 0 ){
				Init_DoubleChannel_FDC2212();
				osDelay(300);
				DetectionTask_STATE = init_Calibration_Value(0);
			}
			osDelay(10);
			break;

		case INITPASSSTATE:
			osDelay(100);

			break;

		case 70:
//			Init_DoubleChannel_FDC2212();
//			osDelay(100);
//			init_Calibration_Value(0);
//			osDelay(100);
//			DetectionTask_STATE = INITPASSSTATE;
			init_Calibration_Value(1);
			osDelay(200);
			DetectionTask_STATE = 71;
			break;

		case 71:
//			Cap_Value_Calibrated[0] = get_Calibrated_Value(0);
//			printf("%.2f\n",Cap_Value_Calibrated[0]);
//			osDelay(10);
			Cap_Value_Calibrated[1] = get_Calibrated_Value(1);
			printf("%.2f\r\n",Cap_Value_Calibrated[1]);
			osDelay(200);

			if(KEY2_Pressed()){
				DetectionTask_STATE = INITPASSSTATE;
			}
			break;

		case Cap0_Sample_State:
			Cap_Value_Calibrated[0] = get_Calibrated_Value(0);
			if (Cap_Value_Calibrated[0] < 0.05){
				Motor3_Nreset_direction;
				Motor[3].StepperSpeedTMR = 33 ;
				Follow_state = 1;
			}
			else if ( (Cap_Value_Calibrated[0] > 0.05) && (Cap_Value_Calibrated[0] <= 0.15) ){
				Motor3_Nreset_direction;
				Motor[3].StepperSpeedTMR = 200 ;
				Follow_state = 1;
			}
			else if ( (Cap_Value_Calibrated[0] > 0.15) && (Cap_Value_Calibrated[0] <= 0.4) ){
				Follow_state = 2;
			}
			else {
				Motor3_reset_direction;
				Motor[3].StepperSpeedTMR = 200 - 100*(Cap_Value_Calibrated[0]-0.4) ;
				Follow_state = 3;
			}
			//osDelay(1000);
			break;

		case INITFAILSTATE:
			printf("[WRONG]init_Calibration_Value FAILED,reCalibrating...\r\n");
			osDelay(5000);
			DetectionTask_STATE = init_Calibration_Value(0);

		}

	}

}

#else

uint8_t CH297_SampleTime[] = "T5\r\n" ;
uint8_t CH297_Start[] = "S\r\n" ;
uint8_t CH297_End[] = "E\r\n" ;
uint8_t CH297_ResolutionTime[] = "C17\r\n" ;

void CH297_Module_Init(void)
{
	HAL_UART_Transmit(&huart5, CH297_SampleTime , sizeof(CH297_SampleTime)-1, 1000);
	osDelay(30);
	HAL_UART_Transmit(&huart5, CH297_SampleTime , sizeof(CH297_SampleTime)-1, 1000);
	osDelay(30);
	HAL_UART_Transmit(&huart5, CH297_ResolutionTime , sizeof(CH297_ResolutionTime)-1, 1000);
	osDelay(30);
	HAL_UART_Transmit(&huart5, CH297_ResolutionTime , sizeof(CH297_ResolutionTime)-1, 1000);
}

void CH297_Module_START(void)
{
	HAL_UART_Transmit(&huart5, CH297_Start , sizeof(CH297_End)-1, 1000);
}

void CH297_Module_STOP(void)
{
	HAL_UART_Transmit(&huart5, CH297_End , sizeof(CH297_End)-1, 1000);
}

void StartDetectionTask(void *argument)
{
	osDelay(50);
	printf("DetectionTask starts! \r\n");
	osDelay(300);
	CH297_Module_STOP();
	osDelay(100);
	CH297_Module_STOP();
	osDelay(100);
	CH297_Module_Init();
	osDelay(100);
	printf("CH345 Init Completed! \r\n");
	DetectionTask_STATE = INITPASSSTATE ;

	for(;;)
	{
		osDelay(1);
		switch (DetectionTask_STATE)
		{
		case INITPASSSTATE:
			osDelay(1000);
			break;

		case 10:
			CH297_Module_START();
			DetectionTask_STATE = INITPASSSTATE;
			break;

		case 20:
			CH297_Module_START();
			osDelay(7310);
			DetectionTask_STATE = 21;
			break;

		case 21:
			CH297_Module_STOP();
			osDelay(100);
			printf("-1\n");
			DetectionTask_STATE = INITPASSSTATE;
			break;

		case 30:
			CH297_Module_STOP();
			DetectionTask_STATE = INITPASSSTATE;
			break;

		case INITFAILSTATE:
			printf("[WRONG]init_Calibration_Value FAILED,reCalibrating...\r\n");
			osDelay(3000);
		}
	}
}
#endif


