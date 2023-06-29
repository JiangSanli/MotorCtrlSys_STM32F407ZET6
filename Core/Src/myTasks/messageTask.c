
/*
 * messageTask - 接收上位机发送的协议并解析
 * 更新日志：
 * 2022.07.26 - 新建
 * 2022.08	-	支持步进电机控制、直流电机PWM控制协议
 * 2022.09	-	支持CH298 PMT读数模块的协议解析
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
#include "string.h"
#include "pid.h"

#ifndef DushuModule
#ifndef QuanxiePVctrl

struct  MotorDefine Motor_Temp ;
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

	//a->DesiredSpeedInRads =  (float)USART5_RX_BUF[4] / 10;
	a->DesiredSpeedInRads =  (float)USART5_RX_BUF[4] ;
	a->NumberofRads = (float)USART5_RX_BUF[5] + (float)USART5_RX_BUF[6] / 100 ;
	//a->StartupSpeedInRads = (float)USART5_RX_BUF[7] / 10 ;
	a->StartupSpeedInRads =  (float)USART5_RX_BUF[7] ;
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

void deal_buffer_DCmotorCtrl(struct MotorDefine *a)
{
	a->MotorNumber = USART5_RX_BUF[1];
	a->NumberofSteps_StopAccel = USART5_RX_BUF[6];
	if (USART5_RX_BUF[4] == 0x00 ){
		printf("\r\nInput Information: DC Motor%d STOP! \r\n",a->MotorNumber);
	}
	else{
		printf("\r\nInput Information: DC Motor%d Run,Duty Cycle: %ld percent\r\n",a->MotorNumber,a->NumberofSteps_StopAccel);
	}
}

void StartmessageTask(void *argument)
{
	osDelay(20);
	uint8_t len = 0;
	printf("messageTask starts! \r\n");

	for(;;){
		osDelay(1);
	    if(USART_RX_STA&0x8000)
		{
	    	len=USART_RX_STA&0x3fff;

			switch ( USART5_RX_BUF[2] )
			{
			/***   电机控制-位置模式 ，16进制0x80  ***/
			case 0b10000000:
				deal_buffer_motorCtrl_position(&Motor_Temp);
				if (USART5_RX_BUF[3] & 0b00000001){			// 不带编码器模式
					MotorMove_position(&Motor_Temp,Motor_Temp.TargetPosition);
				}
#ifdef JiaYangZhen_EncoderMode
				else if (USART5_RX_BUF[3] & 0b00000010){	// 带编码器模式
					MotorMove_position_Enocder(&Motor_Temp,Motor_Temp.TargetPosition);
				}
#endif
				USART_RX_STA=0;
			break;

			/***   电机控制-参数模式 ，16进制0x40  ***/
			case 0b01000000:
				deal_buffer_motorCtrl_data(&Motor_Temp);
				MotorMove_steps(&Motor_Temp);
				USART_RX_STA=0;
			break;

			/***   电机控制-复位 ，16进制0x20  ***/
			case 0b00100000:
				deal_buffer_motorCtrl_reset(&Motor_Temp);
				Motor_Reset(&Motor_Temp);
				USART_RX_STA=0;
			break;

			/***   直流电机控制 0x10  ***/
			case 0b00010000:
				deal_buffer_DCmotorCtrl(&Motor_Temp);
				if (USART5_RX_BUF[4] == 0x00 ){
					if( USART5_RX_BUF[5] == 0x02 ){
						DC_Motor_OFF(&Motor_Temp,'A');
					}
					else if( USART5_RX_BUF[5] == 0x01 ){
						DC_Motor_OFF(&Motor_Temp,'B');
					}
				}
				else{
					if( USART5_RX_BUF[5] == 0x02 ){
						DC_Motor_ON(&Motor_Temp,'A',USART5_RX_BUF[6]);
					}
					else if( USART5_RX_BUF[5] == 0x01 ){
						DC_Motor_ON(&Motor_Temp,'B',USART5_RX_BUF[6]);
					}
				}
				USART_RX_STA=0;
			break;

			/***   打印回传接收到的协议数据  0x01  ***/
			case 0b00000001:
				HAL_UART_Transmit_IT(&huart5, USART5_RX_BUF,len);
				while(__HAL_UART_GET_FLAG(&huart5,UART_FLAG_TC)!=SET);
				USART_RX_STA=0;
			break;

			}
		}
	}
}
#endif
#endif

#ifdef DushuModule
void StartmessageTask(void *argument)
{
	osDelay(20);
	uint32_t med32 = 0;
	printf("messageTask starts! \r\n");

	for(;;){
		osDelay(1);
	    if(USART_RX_STA&0x8000){
	    	med32 = ((USART5_RX_BUF[1] << 24) | (USART5_RX_BUF[2] << 16) | (USART5_RX_BUF[3] << 8) | (USART5_RX_BUF[4]));
	    	printf("%ld\n", med32);
	    	USART_RX_STA=0;
		}
	}
}
#endif


#ifdef	QuanxiePVctrl
float Char_to_Float(char *str)
{
    float n = 0.0;
    float tmp = 10.0;
    int flag = 0;
    assert(str);
    if(*str == '-')
    {
        flag = 1;
        str++;
    }
    while(*str >= '0' && *str <= '9')
    {
        n = n*10 + (*str - '0');
        str++;
    }
    if(*str == '.')
    {
        str++;
        while(*str >= '0' && *str <= '9')
        {
            n = n + (*str -'0')/tmp;;
            tmp = tmp * 10;
            str++;
        }
    }
    if(flag == 1)
    {
        n = -n;
    }
    return n;
}

float uint8_to_Float(uint8_t *buf)
{
    float n = 0.0;
    float tmp = 10.0;
    int flag = 0;
    if(*buf == 0x2D)
    {
        flag = 1;
        buf++;
    }
    while(*buf >= 0x30 && *buf <= 0x39)
    {
        n = n*10 + (*buf - 0x30);
        buf++;
    }
    if(*buf == 0x2E)
    {
        buf++;
        while(*buf >= 0x30 && *buf <= 0x39)
        {
            n = n + (*buf - 0x30)/tmp;;
            tmp = tmp * 10;
            buf++;
        }
    }
    if(flag == 1)
    {
        n = -n;
    }
    return n;
}

float SetValue_Update ;
void Get_Char_SetValue(char *str , uint8_t len)
{
	char temp[10] = {0};
	uint8_t a=0;
	uint8_t b=0;
	for(uint8_t i=0 ; i<len ; i++){
		if(str[i] == 'v'){
			a = i+2 ;
		}
		else if(str[i] == ','){
			b = i-1 ;
			break;
		}
	}
	if ( a && b){
		for(uint8_t j=0 ; j<(b-a+1) ; j++){
			temp[j] = str[a+j] ;
		}
		SetValue_Update = Char_to_Float(temp) ;
	}
}

float pid_Update[3];
void Get_Char_p_i_d(char *str , uint8_t len)
{
	char temp_p[10] = {0};
	char temp_i[10] = {0};
	char temp_d[10] = {0};
	uint8_t num_p,num_i,num_d;
	num_p=num_i=num_d=0;
	uint8_t num_p_end,num_i_end,num_d_end;
	num_p_end=num_i_end=num_d_end=0;

	for(uint8_t i=0 ; i<len ; i++){
		if(str[i] == 'p'){
			num_p = i+2 ;
		}
		if (num_p && (str[i] == ',')){
			num_p_end = i-1 ;
		}
	}
	for(uint8_t i=0 ; i<len ; i++){
		if(str[i] == 'i'){
			num_i = i+2 ;
		}
		if (num_i && (str[i] == ',')){
			num_i_end = i-1 ;
		}
	}
	for(uint8_t i=0 ; i<len ; i++){
		if(str[i] == 'd'){
			num_d = i+2 ;
		}
		if (num_d && (str[i] == ',')){
			num_d_end = i-1 ;
		}
	}

	if ( num_p && num_p_end){
		for(uint8_t j=0 ; j<(num_p_end-num_p+1) ; j++){
			temp_p[j] = str[num_p+j] ;
		}
		pid_Update[0]=Char_to_Float(temp_p);
	}
	if ( num_i && num_i_end){
		for(uint8_t j=0 ; j<(num_i_end-num_i+1) ; j++){
			temp_i[j] = str[num_i+j] ;
		}
		pid_Update[1]=Char_to_Float(temp_i);
	}
	if ( num_d && num_d_end){
		for(uint8_t j=0 ; j<(num_d_end-num_d+1) ; j++){
			temp_d[j] = str[num_d+j] ;
		}
		pid_Update[2]=Char_to_Float(temp_d);
	}
}




void StartmessageTask(void *argument)
{
	osDelay(20);
	uint8_t rx5_len = 0;

	printf("messageTask starts! \r\n");


	for(;;){
		osDelay(10);

	    if(USART_RX_STA&0x8000)
		{
	    	rx5_len = USART_RX_STA&0x3fff;
	    	Get_Char_SetValue(USART5_RX_BUF,rx5_len);
	    	Get_Char_p_i_d(USART5_RX_BUF,rx5_len);
	    	printf("SetValue_Update: %.4f \r\n",SetValue_Update);
	    	printf("pid_Update:  P=%.4f  I=%.4f  D=%.4f \r\n",pid_Update[0],pid_Update[1],pid_Update[2]);
	    	PID_Clear(&pid1);
	    	PID_Init(&pid1,pid_Update[0],pid_Update[1],pid_Update[2],10000,10000);
	    	USART_RX_STA = 0;

		}
	}
}
#endif



