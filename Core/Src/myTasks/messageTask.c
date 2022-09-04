
/*
 * messageTask - 接收上位机发送的协议并解析
 * 更新日志：
 * 2022.07.26 - 新建
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

struct MotorDefine Motor_Temp ;

void deal_buffer_motorCtrl_data(struct MotorDefine *a)
{
	a->MotorNumber = USART5_RX_BUF[1];

	if ( USART5_RX_BUF[3] & 0b10000000 )  // 0x80
	{
		a->MotorDirection = 1 ;
	}
	else if (USART5_RX_BUF[3] & 0b01000000)	// 0x40
	{
		a->MotorDirection = 0 ;
	}

	a->DesiredSpeedInRads =  (float)USART5_RX_BUF[4] / 10;
	a->NumberofRads = (float)USART5_RX_BUF[5] + (float)USART5_RX_BUF[6] / 100 ;
	a->StartupSpeedInRads = (float)USART5_RX_BUF[7] / 10 ;
	a->accelerationRate = USART5_RX_BUF[8] * 100 ;
	a->decelerationRate = USART5_RX_BUF[9] * 100 ;

	printf("\r\nInput Information:\r\n");
	printf("  MotorNumber:%d  MotorDirection:%d\r\n  DesiredSpeedInRads:%.2f\r\n  NumberofRads:%.2f\r\n  StartupSpeedInRads:%.2f\r\n  accelerationRate:%ld /Hz\r\n  decelerationRate:%ld /Hz\r\n"
	,a->MotorNumber,a->MotorDirection,a->DesiredSpeedInRads,a->NumberofRads,a->StartupSpeedInRads,a->accelerationRate,a->decelerationRate);
}


void deal_buffer_motorCtrl_position(struct MotorDefine *a)
{
	a->MotorNumber = USART5_RX_BUF[1];
	if ( USART5_RX_BUF[4] == 1){
		a->TargetPosition = USART5_RX_BUF[7] + USART5_RX_BUF[6] * 16*16 + USART5_RX_BUF[5] * 16*16*16*16 ;
	}
	else if ( USART5_RX_BUF[4] == 0){
		a->TargetPosition = - (USART5_RX_BUF[7] + USART5_RX_BUF[6] * 16*16 + USART5_RX_BUF[5] * 16*16*16*16) ;
	}
	printf("\r\nInput Information: Motor%d goes to TargetPosition:%ld\r\n",a->MotorNumber,a->TargetPosition);
}

void deal_buffer_motorCtrl_reset(struct MotorDefine *a)
{
	a->MotorNumber = USART5_RX_BUF[1];

	printf("\r\nInput Information: Reset Motor%d\r\n",a->MotorNumber);
}

void StartmessageTask(void *argument)
{
	osDelay(20);

	uint8_t len = 0;

	printf("messageTask starts! \r\n");

	for(;;)
	{
		osDelay(1);

	    if(USART_RX_STA&0x8000)
		{
	    	len=USART_RX_STA&0x3fff;

			switch ( USART5_RX_BUF[2] )
			{

			case 0b10000000: 					// 电机控制-位置模式 ，16进制0x80
				deal_buffer_motorCtrl_position(&Motor_Temp);
				if (USART5_RX_BUF[3] & 0b00000001){	// 不带编码器模式
					MotorMove_position(&Motor_Temp,Motor_Temp.TargetPosition);
				}
#ifdef JiaYangZhen_EncoderMode
				else if (USART5_RX_BUF[3] & 0b00000010){	// 带编码器模式
					MotorMove_position_Enocder(&Motor_Temp,Motor_Temp.TargetPosition);
				}
#endif
				USART_RX_STA=0;
			break;

			case 0b01000000:  					// 电机控制-参数模式 ，16进制0x40
				deal_buffer_motorCtrl_data(&Motor_Temp);
				MotorMove_steps(&Motor_Temp);
				USART_RX_STA=0;
			break;

			case 0b00100000:  					// 电机控制-复位 ，16进制0x20
				deal_buffer_motorCtrl_reset(&Motor_Temp);
				Motor_Reset(&Motor_Temp);
				USART_RX_STA=0;
			break;

			case 0b00000001: 					// 打印回传接收到的协议数据 ， 16进制0x01
				HAL_UART_Transmit_IT(&huart5, USART5_RX_BUF,len);
				while(__HAL_UART_GET_FLAG(&huart5,UART_FLAG_TC)!=SET);
				USART_RX_STA=0;
			break;

			}

		}
	}
}


