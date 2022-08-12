
#include "main.h"
#include "cmsis_os.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "stdio.h"
#include "MotorCtrl.h"
#include "stdlib.h"

struct MotorDefine Motor[10];

void Motor_Data_Init(void)
{
/*  Motor1:磁分离42步进电机，传动比2：5  */
	Motor[1].MotorNumber = 1;
	Motor[1].Status = 0,
	Motor[1].htim_x = &htim10,
	//机械参数
	Motor[1].deceleration_ratio = 2.5;
	Motor[1].step_angle = 1.8;
	Motor[1].mircro_steps = 8;
	Motor[1].MaxSpeedInRads= 25;
	//设定默认速度参数，以下为实测优化后结果，可以通过参数控制模式修改
	Motor[1].StartupSpeedInRads = 1;
	Motor[1].DesiredSpeedInRads = 2;
	Motor[1].accelerationRate = 2000;
	Motor[1].decelerationRate = 1000;
#ifdef CiFenLi
/*  Motor2:磁分离35步进丝杆电机，导程4.8768mm，步长0.024384mm/步  */
	Motor[2].MotorNumber = 2;
	Motor[2].Status = 0,
	Motor[2].htim_x = &htim11,
	//机械参数
	Motor[2].deceleration_ratio = 1;
	Motor[2].step_angle = 1.8;
	Motor[2].mircro_steps = 4;
	Motor[2].MaxSpeedInRads= 25;
	//设定默认速度参数，以下为实测优化后结果，可以通过参数控制模式修改
	Motor[2].StartupSpeedInRads = 3;
	Motor[2].DesiredSpeedInRads = 6;
	Motor[2].accelerationRate = 2000;
	Motor[2].decelerationRate = 1000;
#endif
#ifdef JiaYangZhen
/*  Motor2: 加样针水平方向步进电机，4细分800步每圈，编码器为1000P/R */
	Motor[2].MotorNumber = 2;
	Motor[2].Status = 0,
	Motor[2].htim_x = &htim11,
	//机械参数
	Motor[2].deceleration_ratio = 1;
	Motor[2].step_angle = 1.8;
	Motor[2].mircro_steps = 4;
	Motor[2].MaxSpeedInRads= 25;
	Motor[2].Encoder_PulsePerRad = 1000;
	//设定默认速度参数，以下为实测优化后结果，可以通过参数控制模式修改
	Motor[2].StartupSpeedInRads = 1;
	Motor[2].DesiredSpeedInRads = 6;
	Motor[2].accelerationRate = 3000;
	Motor[2].decelerationRate = 2500;

/*  Motor3: 加样针垂直方向步进电机,4细分800步每圈，编码器为1000P/R  */
	Motor[3].MotorNumber = 3;
	Motor[3].Status = 0,
	Motor[3].htim_x = &htim13,
	//机械参数
	Motor[3].deceleration_ratio = 1;
	Motor[3].step_angle = 1.8;
	Motor[3].mircro_steps = 4;
	Motor[3].MaxSpeedInRads= 25;
	Motor[2].Encoder_PulsePerRad = 1000;
	//设定默认速度参数，以下为实测优化后结果，可以通过参数控制模式修改
	Motor[3].StartupSpeedInRads = 1;
	Motor[3].DesiredSpeedInRads = 5;
	Motor[3].accelerationRate = 3600;
	Motor[3].decelerationRate = 3200;
#endif

/*  Motor4 : 柱塞泵，负责注液（也可以抽液），最大排量1000uL，总行程10rads（2000步），每步0.5uL  */
	Motor[4].MotorNumber = 4;
	Motor[4].Status = 0,
	Motor[4].htim_x = &htim14,
	//机械参数
	Motor[4].deceleration_ratio = 1;
	Motor[4].step_angle = 1.8;
	Motor[4].mircro_steps = 4;
	Motor[4].MaxSpeedInRads= 25;
	//设定默认速度参数，以下为实测优化后结果，可以通过参数控制模式修改
	Motor[4].StartupSpeedInRads = 2.5;
	Motor[4].DesiredSpeedInRads = 5;
	Motor[4].accelerationRate = 2000;
	Motor[4].decelerationRate = 1000;

/*  Motor5 : 微流控5V小电机-遥感电机   */
	Motor[5].MotorNumber = 5;
	Motor[5].Status = 0,
	Motor[5].htim_x = &htim6,
	//机械参数
	Motor[5].deceleration_ratio = 10;
	Motor[5].step_angle = 18;
	Motor[5].mircro_steps = 1;
	Motor[5].MaxSpeedInRads= 25;
	//设定默认速度参数，以下为实测优化后结果，可以通过参数控制模式修改
	Motor[5].StartupSpeedInRads = 1;
	Motor[5].DesiredSpeedInRads = 5;
	Motor[5].accelerationRate = 2000;
	Motor[5].decelerationRate = 1000;

/*  Motor6 : 微流控5V小电机-旋转电机   */
	Motor[6].MotorNumber = 6;
	Motor[6].Status = 0,
	Motor[6].htim_x = &htim7,
	//机械参数
	Motor[6].deceleration_ratio = 1;
	Motor[6].step_angle = 18;
	Motor[6].mircro_steps = 1;
	Motor[6].MaxSpeedInRads= 25;
	//设定默认速度参数，以下为实测优化后结果，可以通过参数控制模式修改
	Motor[6].StartupSpeedInRads = 2.5;
	Motor[6].DesiredSpeedInRads = 10;
	Motor[6].accelerationRate = 2000;
	Motor[6].decelerationRate = 1000;
}

void print_MotorInformation(struct MotorDefine *a)
{
	printf("********************\r\n");
	printf("MotorNumber:%d\r\n",a->MotorNumber);
	printf("deceleration_ratio:%.2f\r\n",a->deceleration_ratio);
	printf("step_angle:%.2f\r\n",a->step_angle);
	printf("mircro_steps:%ld\r\n",a->mircro_steps);
	printf("MaxSpeedInRads:%.2f\r\n",a->MaxSpeedInRads);
	printf("StartupSpeedInRads:%.2f\r\n",a->StartupSpeedInRads);
	printf("DesiredSpeedInRads:%.2f\r\n",a->DesiredSpeedInRads);
	printf("accelerationRate:%ld\r\n",a->accelerationRate);
	printf("decelerationRate:%ld\r\n",a->decelerationRate);
	printf("MotorDirection:%d\r\n",a->MotorDirection);
	printf("NumberofRads:%.2f\r\n",a->NumberofRads);
	printf("StepPosition:%ld\r\n",a->StepPosition);
	printf("Status:%d\r\n",a->Status);
	printf("TargetPosition:%ld\r\n",a->TargetPosition);
	printf("htim_x:%p\r\n",&a->htim_x);
	printf("StepsInOneCircle:%ld\r\n",a->StepsInOneCircle);
	printf("StartupSpeedInHz:%ld\r\n",a->StartupSpeedInHz);
	printf("ActualSpeedInHz:%ld\r\n",a->ActualSpeedInHz);
	printf("DesiredSpeedInHz:%ld\r\n",a->DesiredSpeedInHz);
	printf("StepperSpeedTMR:%ld\r\n",a->StepperSpeedTMR);
	printf("NumberofSteps:%ld\r\n",a->NumberofSteps);
	printf("NumberofSteps_StopAccel:%ld\r\n",a->NumberofSteps_StopAccel);
	printf("NumberofSteps_BeginDecel:%ld\r\n",a->NumberofSteps_BeginDecel);
	printf("AccelerationTimeTMR:%ld\r\n",a->AccelerationTimeTMR);
	printf("DecelerationTimeTMR:%ld\r\n",a->DecelerationTimeTMR);
	printf("********************\r\n");
}


void ALL_Motors_Disable(void)
{
	Motor1_Disable();	Motor2_Disable();	Motor3_Disable();	Motor4_Disable();
	VM5_Disable_A();	VM5_Disable_B();	VM6_Disable_A();	VM6_Disable_B();
	VM7_Disable_A();	VM7_Disable_B();	VM8_Disable_A();	VM8_Disable_B();
	Motorpluse1_Low();	Motorpluse2_Low();	Motorpluse3_Low();	Motorpluse4_Low();
	VM5_IN1_L();	VM5_IN2_L();	VM5_IN3_L();	VM5_IN4_L();
	VM6_IN1_L();	VM6_IN2_L();	VM6_IN3_L();	VM6_IN4_L();
	VM7_IN1_L();	VM7_IN2_L();	VM7_IN3_L();	VM7_IN4_L();
	VM8_IN1_L();	VM8_IN2_L();	VM8_IN3_L();	VM8_IN4_L();
	//printf("[Warning]All Motors Disabled!\r\n");
}

#ifdef CiFenLi
uint8_t ALL_Motors_Init(void)  // 所有电机初始化
{
	Motor1_Enable();	Motor2_Enable();	Motor3_Enable();	Motor4_Enable();
	VM5_Enable_A();	VM5_Enable_B();
	VM6_Enable_A();	VM6_Enable_B();
	VM7_Enable_A();	VM7_Enable_B();
	VM8_Enable_A();	VM8_Enable_B();
	osDelay(200);
	uint8_t InitState = 0 ;
	uint8_t ResetResult1 = 0;
	uint8_t ResetResult2 = 0;
	uint8_t ResetResult4 = 0;
	while(1)
	{
		switch (InitState)
		{
			case 0:
				ResetResult4 = Motor_Reset(&Motor[4]);
				osDelay(MotorInitDelay1);
				if (ResetResult4){
					InitState = 1 ;
				}
				else{
					InitState = INITFAILSTATE ;
				}
				break ;

			case 1:
				ResetResult2 = Motor_Reset(&Motor[2]);
				osDelay(MotorInitDelay1);
				if (ResetResult2){
					InitState = 2 ;
				}
				else{
					InitState = INITFAILSTATE ;
				}
				break ;

			case 2:
				ResetResult1 = Motor_Reset(&Motor[1]);
				osDelay(MotorInitDelay1);
				if (ResetResult1){
					InitState = INITPASSSTATE ;
				}
				else{
					InitState = INITFAILSTATE ;
				}
				break ;

			case INITPASSSTATE:
				printf("All Motors Initialization Completed!\r\n");
				return INITPASSSTATE;
				break ;

			case INITFAILSTATE :
				printf("[WRONG]All Motors Initialization FAILED! False Code(1-n):%d%d%d\r\n",ResetResult1,ResetResult2,ResetResult4);
				return INITFAILSTATE;
				break ;

		}
	}
	return INITFAILSTATE;
}
#endif

#ifdef JiaYangZhen
uint8_t ALL_Motors_Init(void)  // 电机初始化，找到0位并把电机位置设为0
{
	Motor1_Enable();	Motor2_Enable();	Motor3_Enable();	Motor4_Enable();
	VM5_Enable_A();	VM5_Enable_B();
	VM6_Enable_A();	VM6_Enable_B();
	VM7_Enable_A();	VM7_Enable_B();
	VM8_Enable_A();	VM8_Enable_B();
	osDelay(200);
	uint8_t InitState = 0 ;
	uint8_t ResetResult2 = 0;
	uint8_t ResetResult3 = 0;
	while(1)
	{
		switch (InitState)
		{
			case 0:
				ResetResult3 = Motor_Reset(&Motor[3]);
				osDelay(MotorInitDelay1);
				if (ResetResult3){
					InitState = 1 ;
				}
				else{
					InitState = INITFAILSTATE ;
				}
				break ;

			case 1:
				ResetResult2 = Motor_Reset(&Motor[2]);
				osDelay(MotorInitDelay1);
				if (ResetResult2){
					InitState = INITPASSSTATE ;
				}
				else{
					InitState = INITFAILSTATE ;
				}
				break ;


			case INITPASSSTATE:
				printf("All Motors Initialization Completed!\r\n");
				return INITPASSSTATE;
				break ;

			case INITFAILSTATE :
				printf("[WRONG]All Motors Initialization FAILED! False Code(1-n):%d%d\r\n",ResetResult2,ResetResult3);
				return INITFAILSTATE;
				break ;
			}
		}
	return INITFAILSTATE;
}
#endif

uint32_t AccelDecelTimeCompute(uint32_t AccelDecelRate)  //根据输入的加减速率，计算加减速计时器的TMR
{
	uint32_t temp_AccelDecelTimeTMR;
	if(AccelDecelRate > MOTORTIM_TMR)
	{
		printf("[WRONG]AccelDecel Rate Oversize!\r\n"); //如果加减速超过MOTORTIM_TMR（100000Hz/s），判断过快报错
		return 10000;  // 返回一个较大的加速度增量10kHz
	}
	temp_AccelDecelTimeTMR = MOTORTIM_TMR / AccelDecelRate ;  // 计算对应的加减速计时器TMR
	return temp_AccelDecelTimeTMR;
}

void AccelDecel(uint32_t AccelDecelState,struct MotorDefine *a)
{
	switch (AccelDecelState)
	{
	case 0:

	break;

	case ACCEL: // accelerate
		a->ActualSpeedInHz ++ ;
		if (a->ActualSpeedInHz >= a->DesiredSpeedInHz)
		{
			a->ActualSpeedInHz = a->DesiredSpeedInHz;
			AccelDecelState = 0;
		}
		a->StepperSpeedTMR = MOTORTIM_TMR / a->ActualSpeedInHz;
	break;

	case DECEL: // decelerate
		a->ActualSpeedInHz -- ;
		if (a->ActualSpeedInHz <= a->StartupSpeedInHz)
		{
			a->ActualSpeedInHz = a->StartupSpeedInHz;
			AccelDecelState = 0;
		}
		a->StepperSpeedTMR = MOTORTIM_TMR / a->ActualSpeedInHz;
	}
}

void MotorDirection_SetUp(struct MotorDefine *a)
{
	if (a->MotorNumber == 1){
		if(a->MotorDirection == 1){
			Motor1_Nreset_direction;
		}
		else{
			Motor1_reset_direction;
		}
	}
	else if (a->MotorNumber == 2){
		if(a->MotorDirection == 1){
			Motor2_Nreset_direction;
		}
		else{
			Motor2_reset_direction;
		}
	}
	else if (a->MotorNumber == 3){
		if(a->MotorDirection == 1){
			Motor3_Nreset_direction;
		}
		else{
			Motor3_reset_direction;
		}
	}
	else if (a->MotorNumber == 4){
		if(a->MotorDirection == 1){
			Motor4_Nreset_direction;
		}
		else{
			Motor4_reset_direction;
		}
	}
}

void Motor5_AB(void) // 电机5状态1
{VM5_IN1_H();	VM5_IN2_L();	VM5_IN3_H()	;	VM5_IN4_L();}
void Motor5_aB(void) // 电机5状态2
{VM5_IN1_L();	VM5_IN2_H();	VM5_IN3_H()	;	VM5_IN4_L();}
void Motor5_ab(void) // 电机6状态3
{VM5_IN1_L();	VM5_IN2_H();	VM5_IN3_L()	;	VM5_IN4_H();}
void Motor5_Ab(void) // 电机6状态4
{VM5_IN1_H();	VM5_IN2_L();	VM5_IN3_L()	;	VM5_IN4_H();}

void Motor6_AB(void) // 电机6状态1
{VM6_IN1_H();	VM6_IN2_L();	VM6_IN3_H()	;	VM6_IN4_L();}
void Motor6_aB(void) // 电机6状态2
{VM6_IN1_L();	VM6_IN2_H();	VM6_IN3_H()	;	VM6_IN4_L();}
void Motor6_ab(void) // 电机6状态3
{VM6_IN1_L();	VM6_IN2_H();	VM6_IN3_L()	;	VM6_IN4_H();}
void Motor6_Ab(void) // 电机6状态4
{VM6_IN1_H();	VM6_IN2_L();	VM6_IN3_L()	;	VM6_IN4_H();}

void Motor_AccelDecel_waveCalculate(struct MotorDefine *a)
{
	uint32_t DesiredNumberofSteptoAccel ;
	uint32_t DesiredNumberofSteptoDecel ;
	float DesiredAccellTimeInSeconds ;
	float DesiredDecellTimeInSeconds ;

	a->AccelerationTimeTMR = AccelDecelTimeCompute(a->accelerationRate);
	a->DecelerationTimeTMR = AccelDecelTimeCompute(a->decelerationRate);

	DesiredAccellTimeInSeconds = ((float)a->DesiredSpeedInHz-a->StartupSpeedInHz) / a->accelerationRate;
	DesiredDecellTimeInSeconds = ((float)a->DesiredSpeedInHz-a->StartupSpeedInHz) / a->decelerationRate;
	DesiredNumberofSteptoAccel =  DesiredAccellTimeInSeconds * (a->DesiredSpeedInHz-a->StartupSpeedInHz) /2 + a->StartupSpeedInHz*DesiredAccellTimeInSeconds; //对速度曲线求积分，理论计算完成加速需要的步数
	DesiredNumberofSteptoDecel =  DesiredDecellTimeInSeconds * (a->DesiredSpeedInHz-a->StartupSpeedInHz) /2 + a->StartupSpeedInHz*DesiredDecellTimeInSeconds ; //对速度曲线求积分，理论计算完成减速需要的步数

	if ( (DesiredNumberofSteptoAccel + DesiredNumberofSteptoDecel) <= a->NumberofSteps ) //如果加减速需要的步数和，小于总步数，则进行完整加减速
	{
		a->NumberofSteps_StopAccel = a->NumberofSteps - DesiredNumberofSteptoAccel ;
		a->NumberofSteps_BeginDecel =  DesiredNumberofSteptoDecel ;
	}
	else  // 如果行进距离不能完成完整的加减速曲线，则前1/3加速，后2/3减速
	{
		a->NumberofSteps_StopAccel = a->NumberofSteps /3*2 ;
		a->NumberofSteps_BeginDecel = a->NumberofSteps /3*2 ;
	}
}


/*            *****************    0x40-0b01000000 电机参数控制模式 ：  ******************
根据协议，通过USART5进行出串口通讯，输入步进电机的【编号、方向、速度、距离、启动速度、加减速频率】电机运动参数
***特别注意： 调试模式如果增加打印信息，在连续执行函数时，会造成10-20ms的延时，***/
void MotorMove_steps(struct MotorDefine *temp)
{
	if (Motor[temp->MotorNumber].Status == 1){
		printf("[WRONG] Motor Moved Failed,Motor%d is busy!\r\n",Motor[temp->MotorNumber].MotorNumber);
		return ;
	}
	else {
		Motor[temp->MotorNumber].Status = 1 ;
	}

	temp->deceleration_ratio = Motor[temp->MotorNumber].deceleration_ratio ;
	temp->step_angle = Motor[temp->MotorNumber].step_angle ;
	temp->mircro_steps = Motor[temp->MotorNumber].mircro_steps ;
	temp->MaxSpeedInRads = Motor[temp->MotorNumber].MaxSpeedInRads ;
	temp->htim_x = Motor[temp->MotorNumber].htim_x ;

	if(temp->DesiredSpeedInRads > temp->MaxSpeedInRads)  // 判断电机设置速度是否超过最大转速
	{
		printf("[WRONG] Setup Speed faster than max speed:%.2f rad/s !\r\n",temp->MaxSpeedInRads);
		return ;
	}

	// 计算： 单圈步数、启动速度、目标速度、行进步数、加减速时间
	temp->StepsInOneCircle = (360 / temp->step_angle) * temp->deceleration_ratio * temp->mircro_steps;
	temp->StartupSpeedInHz = temp->StepsInOneCircle * temp->StartupSpeedInRads ;
	temp->ActualSpeedInHz = temp->StartupSpeedInHz;						// 设定初始实际频率为启动频率
	temp->DesiredSpeedInHz = temp->StepsInOneCircle * temp->DesiredSpeedInRads ;
	temp->StepperSpeedTMR = MOTORTIM_TMR / temp->ActualSpeedInHz;
	temp->NumberofSteps = temp->NumberofRads * temp->StepsInOneCircle ;

	Motor_AccelDecel_waveCalculate(temp);  // 计算电机加减速曲线

	Motor[temp->MotorNumber].StepsInOneCircle = temp->StepsInOneCircle ;
	Motor[temp->MotorNumber].StartupSpeedInHz = temp->StartupSpeedInHz ;
	Motor[temp->MotorNumber].ActualSpeedInHz = temp->ActualSpeedInHz ;
	Motor[temp->MotorNumber].DesiredSpeedInHz = temp->DesiredSpeedInHz ;
	Motor[temp->MotorNumber].StepperSpeedTMR = temp->StepperSpeedTMR ;
	Motor[temp->MotorNumber].NumberofSteps = temp->NumberofSteps ;
	Motor[temp->MotorNumber].MotorDirection = temp->MotorDirection ;
	Motor[temp->MotorNumber].NumberofSteps_StopAccel = temp->NumberofSteps_StopAccel ;
	Motor[temp->MotorNumber].NumberofSteps_BeginDecel = temp->NumberofSteps_BeginDecel ;
	Motor[temp->MotorNumber].AccelerationTimeTMR = temp->AccelerationTimeTMR ;
	Motor[temp->MotorNumber].DecelerationTimeTMR = temp->DecelerationTimeTMR ;
	Motor[temp->MotorNumber].TargetPosition = -16777200 ; //暂时设置目标位置为无法达到的值，参数控制模式用步进数控制中断停止

	MotorDirection_SetUp(&Motor[temp->MotorNumber]) ;
	//print_MotorInformation(&Motor[temp->MotorNumber]);
	HAL_TIM_Base_Start_IT(Motor[temp->MotorNumber].htim_x);
}

/*            *****************    0x80-0b10000000 电机位置控制模式 ：  ******************
根据协议，通过USART5进行出串口通讯，输入步进电机的 【地址+目标位置】 即可，使用程序本身的电机参数控制运动
***特别注意： 调试模式如果增加打印信息，在连续执行函数时，会造成10-20ms的延时，***/
void MotorMove_position(struct MotorDefine *temp  , int32_t targer_position)
{
	if (Motor[temp->MotorNumber].Status == 1){
		printf("[WRONG] Position Set Failed,Motor%d is busy!\r\n",Motor[temp->MotorNumber].MotorNumber);
		return ;
	}
	else {
		Motor[temp->MotorNumber].Status = 1 ;
	}

	Motor[temp->MotorNumber].StepsInOneCircle = (360 / Motor[temp->MotorNumber].step_angle) * Motor[temp->MotorNumber].deceleration_ratio * Motor[temp->MotorNumber].mircro_steps;
	Motor[temp->MotorNumber].StartupSpeedInHz = Motor[temp->MotorNumber].StepsInOneCircle * Motor[temp->MotorNumber].StartupSpeedInRads ;
	Motor[temp->MotorNumber].ActualSpeedInHz = Motor[temp->MotorNumber].StartupSpeedInHz;
	Motor[temp->MotorNumber].DesiredSpeedInHz = Motor[temp->MotorNumber].StepsInOneCircle * Motor[temp->MotorNumber].DesiredSpeedInRads ;
	Motor[temp->MotorNumber].StepperSpeedTMR = MOTORTIM_TMR / Motor[temp->MotorNumber].ActualSpeedInHz;

	Motor[temp->MotorNumber].TargetPosition = targer_position ;
	Motor[temp->MotorNumber].NumberofSteps = abs(Motor[temp->MotorNumber].TargetPosition  -  Motor[temp->MotorNumber].StepPosition) ;//计算总步数
	if (Motor[temp->MotorNumber].TargetPosition == Motor[temp->MotorNumber].StepPosition){
		Motor[temp->MotorNumber].Status = 0 ;
		printf("---KEEP---Motor%d Steps Position:%ld---\r\n",Motor[temp->MotorNumber].MotorNumber,Motor[temp->MotorNumber].StepPosition);
		return ;
	}
	else if (Motor[temp->MotorNumber].TargetPosition > Motor[temp->MotorNumber].StepPosition ){
		Motor[temp->MotorNumber].MotorDirection = 1 ;
	}
	else{
		Motor[temp->MotorNumber].MotorDirection = 0 ;
	}

	Motor_AccelDecel_waveCalculate(&Motor[temp->MotorNumber]);  // 计算电机加减速曲线

	if (Motor[temp->MotorNumber].MotorNumber == 1)   // Motor1为传送带形式步进电机，非丝杆直线电机，方向控制和直线电机不一样
	{
		Motor[temp->MotorNumber].NumberofSteps = Motor[temp->MotorNumber].NumberofSteps % Motor[temp->MotorNumber].StepsInOneCircle ;
		Motor[temp->MotorNumber].TargetPosition = Motor[temp->MotorNumber].TargetPosition % Motor[temp->MotorNumber].StepsInOneCircle ;
		if( Motor[temp->MotorNumber].NumberofSteps <= (Motor[temp->MotorNumber].StepsInOneCircle/2) ){  //如果计算出的步数小于半圈，则按照既定计算方向及进行
			Motor_AccelDecel_waveCalculate(&Motor[temp->MotorNumber]);
			if(Motor[temp->MotorNumber].MotorDirection == 1){
				Motor1_Nreset_direction;
			}
			else{
				Motor1_reset_direction;
			}
		}
		else{
			Motor[temp->MotorNumber].NumberofSteps = abs (Motor[temp->MotorNumber].StepsInOneCircle - Motor[temp->MotorNumber].NumberofSteps);
			Motor_AccelDecel_waveCalculate(&Motor[temp->MotorNumber]);
			if(Motor[temp->MotorNumber].MotorDirection == 1){
				Motor[temp->MotorNumber].MotorDirection = 0;
				Motor1_reset_direction;
			}
			else{
				Motor[temp->MotorNumber].MotorDirection = 1;
				Motor1_Nreset_direction;
			}
		}
	}
	else{
		MotorDirection_SetUp(&Motor[temp->MotorNumber]) ;
	}
	//位置控制情况下，允许总步数多走10步，如果仍没有到达目标位置，则判定超时失败
	Motor[temp->MotorNumber].NumberofSteps = Motor[temp->MotorNumber].NumberofSteps + 10;

	//print_MotorInformation(&Motor[temp->MotorNumber]);
	HAL_TIM_Base_Start_IT(Motor[temp->MotorNumber].htim_x);

}

#ifdef JiaYangZhen_EncoderMode
void MotorMove_position_Enocder(struct MotorDefine *temp  , int32_t targer_position_encoder)
{
	if (Motor[temp->MotorNumber].Status == 1){
		printf("[WRONG] Position Set Failed,Motor%d is busy!\r\n",Motor[temp->MotorNumber].MotorNumber);
		return ;
	}
	else {
		Motor[temp->MotorNumber].Status = 1 ;
	}

	Motor[temp->MotorNumber].StepsInOneCircle = (360 / Motor[temp->MotorNumber].step_angle) * Motor[temp->MotorNumber].deceleration_ratio * Motor[temp->MotorNumber].mircro_steps;
	Motor[temp->MotorNumber].StartupSpeedInHz = Motor[temp->MotorNumber].StepsInOneCircle * Motor[temp->MotorNumber].StartupSpeedInRads ;
	Motor[temp->MotorNumber].ActualSpeedInHz = Motor[temp->MotorNumber].StartupSpeedInHz;
	Motor[temp->MotorNumber].DesiredSpeedInHz = Motor[temp->MotorNumber].StepsInOneCircle * Motor[temp->MotorNumber].DesiredSpeedInRads ;
	Motor[temp->MotorNumber].StepperSpeedTMR = MOTORTIM_TMR / Motor[temp->MotorNumber].ActualSpeedInHz;

	Motor[temp->MotorNumber].TargetPosition = targer_position_encoder ;
	Motor[temp->MotorNumber].NumberofSteps = (abs(Motor[temp->MotorNumber].TargetPosition  -  Motor[temp->MotorNumber].StepPosition))*800/1000 ;//计算总步数
	if (Motor[temp->MotorNumber].TargetPosition == Motor[temp->MotorNumber].StepPosition){
		Motor[temp->MotorNumber].Status = 0 ;
		printf("---KEEP---Motor%d Steps Position:%ld---\r\n",Motor[temp->MotorNumber].MotorNumber,Motor[temp->MotorNumber].StepPosition);
		return ;
	}
	else if (Motor[temp->MotorNumber].TargetPosition > Motor[temp->MotorNumber].StepPosition ){
		Motor[temp->MotorNumber].MotorDirection = 1 ;
	}
	else{
		Motor[temp->MotorNumber].MotorDirection = 0 ;
	}

	Motor_AccelDecel_waveCalculate(&Motor[temp->MotorNumber]);  // 计算电机加减速曲线

	MotorDirection_SetUp(&Motor[temp->MotorNumber]) ;

	//编码器位置控制情况下，允许总步数多走10步，如果仍没有到达目标位置，则判定超时失败
	Motor[temp->MotorNumber].NumberofSteps = Motor[temp->MotorNumber].NumberofSteps + 10;
	//print_MotorInformation(&Motor[temp->MotorNumber]);
	HAL_TIM_Base_Start_IT(Motor[temp->MotorNumber].htim_x);
}
#endif

/*            *****************    0x20-0b00100000 电机复位 ：  ****************** */
// 根据协议，通过USART5进行出串口通讯，输入步进电机的 【地址】 即可，使用程序优化配置好的电机参数对电机进行复位（需要配合0位开关）
// 返回值： SUCCESS-1-完成，正在运行  FAIL-0
// 方案：控制电机运动上限圈数为10转，过程中如果触发0位信号则停止运动。如果电机初始位置已经触发0位信号，则反方向运动一小段时间，再找0位
uint8_t Motor_Reset(struct MotorDefine *temp)
{
	if (Motor[temp->MotorNumber].Status == 1){
		printf("[WRONG] Reset Failed,Motor%d is busy!\r\n",temp->MotorNumber);
		return 1;
	}
	*temp = Motor[temp->MotorNumber];

	temp->NumberofRads = 10;

	if (temp->MotorNumber == 1){
		if ( Motor1_reset_OPTstatus ){
			temp->MotorDirection = 1 ;
			MotorMove_steps(temp);
			osDelay(MotorInitDelay);
			for(uint32_t i=0 ; Motor1_reset_OPTstatus ; i++){
				if(i>500) {
					printf("[WRONG] Overtime! Reset Motor%d Failed!\r\n",temp->MotorNumber);
					Motor[temp->MotorNumber].NumberofSteps = 2;
					return FAIL;
				}
				else {osDelay(1);}
			}
			Motor[temp->MotorNumber].NumberofSteps = 2;
		}
		osDelay(MotorInitDelay1);
		if (Motor1_Nreset_OPTstatus){
			temp->MotorDirection = 0 ;
			MotorMove_steps(temp);
			for(uint32_t i=0 ; Motor1_Nreset_OPTstatus ; i++){
				if(i>5000) {
					printf("[WRONG] Overtime! Reset Motor%d Failed!\r\n",temp->MotorNumber);
					Motor[temp->MotorNumber].NumberofSteps = 2;
					return FAIL;
				}
				else {osDelay(1);}
			}
			Motor[temp->MotorNumber].NumberofSteps = 2;
			printf("  Motor%d Reset Completed! Position:%ld\r\n",Motor[temp->MotorNumber].MotorNumber,Motor[temp->MotorNumber].StepPosition);
			return SUCCESS;
		}
	}

	if (temp->MotorNumber == 2){
		if ( Motor2_reset_OPTstatus ){
			temp->MotorDirection = 1 ;
			MotorMove_steps(temp);
			osDelay(MotorInitDelay);
			for(uint32_t i=0 ; Motor2_reset_OPTstatus ; i++){
				if(i>500) {
					printf("[WRONG] Overtime! Reset Motor%d Failed!\r\n",temp->MotorNumber);
					Motor[temp->MotorNumber].NumberofSteps = 2;
					return FAIL;
				}
				else {osDelay(1);}
			}
			Motor[temp->MotorNumber].NumberofSteps = 2;
		}
		osDelay(MotorInitDelay1);
		if (Motor2_Nreset_OPTstatus){
			temp->MotorDirection = 0 ;
			MotorMove_steps(temp);
			for(uint32_t i=0 ; Motor2_Nreset_OPTstatus ; i++){
				if(i>5000) {
					printf("[WRONG] Overtime! Reset Motor%d Failed!\r\n",temp->MotorNumber);
					Motor[temp->MotorNumber].NumberofSteps = 2;
					return FAIL;
				}
				else {osDelay(1);}
			}
			Motor[temp->MotorNumber].NumberofSteps = 2;
			printf("  Motor%d Reset Completed! Position:%ld\r\n",Motor[temp->MotorNumber].MotorNumber,Motor[temp->MotorNumber].StepPosition);
			return SUCCESS;
		}
	}

	if (temp->MotorNumber == 3){
		if ( Motor3_reset_OPTstatus ){
			temp->MotorDirection = 1 ;
			MotorMove_steps(temp);
			osDelay(MotorInitDelay);
			for(uint32_t i=0 ; Motor3_reset_OPTstatus ; i++){
				if(i>500) {
					printf("[WRONG] Overtime! Reset Motor%d Failed!\r\n",temp->MotorNumber);
					Motor[temp->MotorNumber].NumberofSteps = 2;
					return FAIL;
				}
				else {osDelay(1);}
			}
			Motor[temp->MotorNumber].NumberofSteps = 2;
		}
		osDelay(MotorInitDelay1);
		if (Motor3_Nreset_OPTstatus){
			temp->MotorDirection = 0 ;
			MotorMove_steps(temp);
			for(uint32_t i=0 ; Motor3_Nreset_OPTstatus ; i++){
				if(i>5000) {
					printf("[WRONG] Overtime! Reset Motor%d Failed!\r\n",temp->MotorNumber);
					Motor[temp->MotorNumber].NumberofSteps = 2;
					return FAIL;
				}
				else {osDelay(1);}
			}
			Motor[temp->MotorNumber].NumberofSteps = 2;
			printf("  Motor%d Reset Completed! Position:%ld\r\n",Motor[temp->MotorNumber].MotorNumber,Motor[temp->MotorNumber].StepPosition);
			return SUCCESS;
		}
	}

	if (temp->MotorNumber == 4){
		if ( Motor4_reset_OPTstatus ){
			temp->MotorDirection = 1 ;
			MotorMove_steps(temp);
			osDelay(MotorInitDelay);
			for(uint32_t i=0 ; Motor4_reset_OPTstatus ; i++){
				if(i>500) {
					printf("[WRONG] Overtime! Reset Motor%d Failed!\r\n",temp->MotorNumber);
					Motor[temp->MotorNumber].NumberofSteps = 2;
					return FAIL;
				}
				else {osDelay(1);}
			}
			Motor[temp->MotorNumber].NumberofSteps = 2;
		}
		osDelay(MotorInitDelay1);
		if (Motor4_Nreset_OPTstatus){
			temp->MotorDirection = 0 ;
			MotorMove_steps(temp);
			for(uint32_t i=0 ; Motor4_Nreset_OPTstatus ; i++){
				if(i>5000) {
					printf("[WRONG] Overtime! Reset Motor%d Failed!\r\n",temp->MotorNumber);
					Motor[temp->MotorNumber].NumberofSteps = 2;
					return FAIL;
				}
				else {osDelay(1);}
			}
			Motor[temp->MotorNumber].NumberofSteps = 2;
			printf("  Motor%d Reset Completed! Position:%ld\r\n",Motor[temp->MotorNumber].MotorNumber,Motor[temp->MotorNumber].StepPosition);
			return SUCCESS;
		}
	}
	return SUCCESS;
}

#ifdef CiFenLi
uint8_t Motor4_SuckInMode(uint32_t x_uL)  // 电机4最大排量1000uL，总行程10rads（2000步），每步0.5uL
{
	OUT5_ON();
	OUT6_OFF();
	osDelay(20);
	printf("Motor4_Sucks in %lduL...\r\n", x_uL);
	int32_t target_steps = x_uL * 2 * Motor[4].mircro_steps ;
	while(Motor[4].Status == 1){osDelay(1);}
	MotorMove_position(&Motor[4], 0 );
	while(Motor[4].Status == 1){osDelay(1);}
	MotorMove_position(&Motor[4], target_steps );
	while(Motor[4].Status == 1){osDelay(1);}
	osDelay(20);
	OUT5_OFF();
	OUT6_OFF();
	return SUCCESS;
}

uint8_t Motor4_PushOutMode(uint32_t x_uL)
{
	OUT5_OFF();
	OUT6_ON();
	osDelay(50);
	printf("Motor4_Pushs out uL...\r\n");
	int32_t target_position = Motor[4].StepPosition -(x_uL * 2 * Motor[4].mircro_steps) ;
	if(target_position < 0){
		printf("[WRONG]Push out Number Overflow!\r\n Maximum Number:%ld uL\r\n",Motor[4].StepPosition/Motor[4].mircro_steps/2);
		return FAIL;
	}
	while(Motor[4].Status == 1){osDelay(1);}
	MotorMove_position(&Motor[4], target_position );
	while(Motor[4].Status == 1){osDelay(1);}
	osDelay(50);
	OUT5_OFF();
	OUT6_OFF();
	return SUCCESS;
}

void Motor5_SuckOut_ON(void)
{
	OUT4_ON();
	osDelay(10);
	VM8_IN1_H();
	VM8_IN2_L();
}

void Motor5_SuckOut_OFF(void)
{
	VM8_IN1_L();
	VM8_IN2_L();
	osDelay(10);
	OUT4_OFF();
}


void DC_Motor_Move(void)
{
	VM6_IN1_H();
	VM6_IN2_L();
}

void DC_Motor_Stop(void)
{
	VM6_IN1_L();
	VM6_IN2_L();
}
#endif

