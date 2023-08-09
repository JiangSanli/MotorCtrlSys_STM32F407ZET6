
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
#ifdef CiFenLi
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

/*  Motor2:磁分离35步进丝杆电机，导程4.8768mm，步长0.024384mm/步  */
	Motor[2].MotorNumber = 2;
	Motor[2].Status = 0,
	Motor[2].htim_x = &htim11,
	//机械参数
	Motor[2].deceleration_ratio = 1;
	Motor[2].step_angle = 1.8;
	Motor[2].mircro_steps = 8;
	Motor[2].MaxSpeedInRads= 25;
	//设定默认速度参数，以下为实测优化后结果，可以通过参数控制模式修改
	Motor[2].StartupSpeedInRads = 2;
	Motor[2].DesiredSpeedInRads = 4;
	Motor[2].accelerationRate = 2000;
	Motor[2].decelerationRate = 1000;
#endif
#ifdef JiaYangZhen
/*  Motor1:RZ步进电机模块的R轴电机  */
	Motor[1].MotorNumber = 1;
	Motor[1].Status = 0,
	Motor[1].htim_x = &htim10,
	//机械参数
	Motor[1].deceleration_ratio = 1;
	Motor[1].step_angle = 1.8;
	Motor[1].mircro_steps = 16;
	Motor[1].MaxSpeedInRads= 25;
	//设定默认速度参数，以下为实测优化后结果，可以通过参数控制模式修改
	Motor[1].StartupSpeedInRads = 0.6;
	Motor[1].DesiredSpeedInRads = 8;
	Motor[1].accelerationRate = 20000;
	Motor[1].decelerationRate = 20000;

/*  Motor2: 加样针水平方向步进电机，4细分800步每圈，编码器为1000P/R */
	Motor[2].MotorNumber = 2;
	Motor[2].Status = 0,
	Motor[2].htim_x = &htim11,
	//机械参数
	Motor[2].deceleration_ratio = 2;
	Motor[2].step_angle = 1.8;
	Motor[2].mircro_steps = 16;
	Motor[2].MaxSpeedInRads= 25;
	//Motor[2].Encoder_PulsePerRad = 1000;
	//设定默认速度参数，以下为实测优化后结果，可以通过参数控制模式修改
	Motor[2].StartupSpeedInRads = 0.4;
	Motor[2].DesiredSpeedInRads = 1.5;
	Motor[2].accelerationRate = 12000;
	Motor[2].decelerationRate = 12000;

/*  Motor3: 加样针垂直方向步进电机,4细分800步每圈，编码器为1000P/R  */
	Motor[3].MotorNumber = 3;
	Motor[3].Status = 0,
	Motor[3].htim_x = &htim13,
	//机械参数
	Motor[3].deceleration_ratio = 1;
	Motor[3].step_angle = 1.8;
	Motor[3].mircro_steps = 16;
	Motor[3].MaxSpeedInRads= 25;
	//Motor[2].Encoder_PulsePerRad = 1000;
	//设定默认速度参数，以下为实测优化后结果，可以通过参数控制模式修改
	Motor[3].StartupSpeedInRads = 1;
	Motor[3].DesiredSpeedInRads = 5;
	Motor[3].accelerationRate = 10000;
	Motor[3].decelerationRate = 10000;
#endif

#ifdef DuoTongDao
	/*  Motor2: 多通道垂直方向28步进电机，编码器为1000P/R */
		Motor[2].MotorNumber = 2;
		Motor[2].Status = 0,
		Motor[2].htim_x = &htim11,
		//机械参数
		Motor[2].deceleration_ratio = 1;
		Motor[2].step_angle = 1.8;
		Motor[2].mircro_steps = 32;
		Motor[2].MaxSpeedInRads= 6;
		//Motor[2].Encoder_PulsePerRad = 1000;
		//设定默认速度参数，以下为实测优化后结果，可以通过参数控制模式修改
		Motor[2].StartupSpeedInRads = 2;
		Motor[2].DesiredSpeedInRads = 4.5;
		Motor[2].accelerationRate = 20000;
		Motor[2].decelerationRate = 20000;

	/*  Motor3: 水平方向步进电机  */
		Motor[3].MotorNumber = 3;
		Motor[3].Status = 0,
		Motor[3].htim_x = &htim13,
		//机械参数
		Motor[3].deceleration_ratio = 1;
		Motor[3].step_angle = 1.8;
		Motor[3].mircro_steps = 32;
		Motor[3].MaxSpeedInRads= 6;
		//设定默认速度参数，以下为实测优化后结果，可以通过参数控制模式修改
		Motor[3].StartupSpeedInRads = 2;
		Motor[3].DesiredSpeedInRads = 5;
		Motor[3].accelerationRate = 60000;
		Motor[3].decelerationRate = 60000;

	/*  Motor5 : 试剂条暂存电机   */
		Motor[5].MotorNumber = 5;
		Motor[5].Status = 0,
		Motor[5].htim_x = &htim6,
		//机械参数
		Motor[5].deceleration_ratio = 20;	//实际减速比为100，方便指令控制改为20
		Motor[5].step_angle = 18;
		Motor[5].mircro_steps = 1;
		Motor[5].MaxSpeedInRads= 3;
		//设定默认速度参数，以下为实测优化后结果，可以通过参数控制模式修改
		Motor[5].StartupSpeedInRads = 1.5;
		Motor[5].DesiredSpeedInRads = 1.8;
		Motor[5].accelerationRate = 8000;
		Motor[5].decelerationRate = 8000;

	/*  Motor6 : 推杆旋转电机   */
		Motor[6].MotorNumber = 6;
		Motor[6].Status = 0,
		Motor[6].htim_x = &htim7,
		//机械参数
		Motor[6].deceleration_ratio = 20;	//实际减速比为100，方便指令控制改为20
		Motor[6].step_angle = 18;
		Motor[6].mircro_steps = 1;
		Motor[6].MaxSpeedInRads= 3;
		//设定默认速度参数，以下为实测优化后结果，可以通过参数控制模式修改
		Motor[6].StartupSpeedInRads = 1.6;
		Motor[6].DesiredSpeedInRads = 2;
		Motor[6].accelerationRate = 8000;
		Motor[6].decelerationRate = 8000;
#endif

/*  Motor4 : 柱塞泵，负责注液（也可以抽液），最大排量1000uL，总行程10rads（2000步），每步0.5uL  */
		Motor[4].MotorNumber = 4;
		Motor[4].Status = 0,
		Motor[4].htim_x = &htim14,
		//机械参数
		Motor[4].deceleration_ratio = 1;
		Motor[4].step_angle = 1.8;
		Motor[4].mircro_steps = 16;
		Motor[4].MaxSpeedInRads= 13;
		//设定默认速度参数，以下为实测优化后结果，可以通过参数控制模式修改
		Motor[4].StartupSpeedInRads = 5;
		Motor[4].DesiredSpeedInRads = 10;
		Motor[4].accelerationRate = 20000;
		Motor[4].decelerationRate = 10000;

#ifdef JiaYangZhen
/*  Motor7 : 加样针24V直流电机  A相-抽出液体0.6L/min */
	Motor[7].MotorNumber = 7;
	Motor[7].Status = 0,
	Motor[7].htim_x = &htim12,

	//设定默认的PWM控制频率，设置占空比来控制直流电机输出
	Motor[7].StepperSpeedTMR = 400 ;  			// PWM控制直流电机频率：100KHz/100=1KHz
	Motor[7].NumberofSteps_StopAccel = 100 ; 	// 此参数在直流电机应用下，定义为占空比
	Motor[7].AccelerationTimeTMR = Motor[7].StepperSpeedTMR ; 	// 此参数在直流电机应用下，定义实际高电平的TMR计时器个数

/*  Motor8 : 加样针24V直流电机  A相针内壁清洗  B相针外壁清洗  */
	Motor[8].MotorNumber = 8;
	Motor[8].Status = 0,
	Motor[8].htim_x = &htim12,

	//设定默认的PWM控制频率，设置占空比来控制直流电机输出
	Motor[8].StepperSpeedTMR = 400 ;  			// PWM控制直流电机频率：100KHz/100=1KHz
	Motor[8].NumberofSteps_StopAccel = 100 ; 	// 此参数在直流电机应用下，定义为占空比
	Motor[8].AccelerationTimeTMR = Motor[8].StepperSpeedTMR ; 	// 此参数在直流电机应用下，定义实际高电平的TMR计时器个数
#endif

#ifdef QuanxiePVctrl
/*  Motor7 : 加样针24V直流电机  A相-抽出液体0.6L/min */
	Motor[7].MotorNumber = 7;
	Motor[7].Status = 0,
	Motor[7].htim_x = &htim12,

	//设定默认的PWM控制频率，设置占空比来控制直流电机输出
	Motor[7].StepperSpeedTMR = 400 ;  			// PWM控制直流电机频率：100KHz/100=1KHz
	Motor[7].NumberofSteps_StopAccel = 100 ; 	// 此参数在直流电机应用下，定义为占空比
	Motor[7].AccelerationTimeTMR = Motor[7].StepperSpeedTMR ; 	// 此参数在直流电机应用下，定义实际高电平的TMR计时器个数
	Motor[7].DecelerationTimeTMR = 100 ; // 定义为看空比设置最大值

/*  Motor8 : 加样针24V直流电机  A相针内壁清洗  B相针外壁清洗  */
	Motor[8].MotorNumber = 8;
	Motor[8].Status = 0,
	Motor[8].htim_x = &htim12,

	//设定默认的PWM控制频率，设置占空比来控制直流电机输出
	Motor[8].StepperSpeedTMR = 10000 ;  		// PWM控制直流电机频率：100KHz/100=1KHz
	Motor[8].NumberofSteps_StopAccel = 10000 ; 	// 此参数在直流电机应用下，定义为占空比
	Motor[8].AccelerationTimeTMR = Motor[8].StepperSpeedTMR ; 	// 此参数在直流电机应用下，定义实际高电平的TMR计时器个数
	Motor[8].DecelerationTimeTMR = 10000 ; // 定义为看空比设置最大值
#endif

#ifdef WeiLiuKong
/*  Motor5 : 微流控5V小电机-摇杆电机,水平圆周运动   */
	Motor[5].MotorNumber = 5;
	Motor[5].Status = 0,
	Motor[5].htim_x = &htim6,
	//机械参数
	Motor[5].deceleration_ratio = 10;
	Motor[5].step_angle = 18;
	Motor[5].mircro_steps = 1;
	Motor[5].MaxSpeedInRads= 100;
	//设定默认速度参数，以下为实测优化后结果，可以通过参数控制模式修改
	Motor[5].StartupSpeedInRads = 2;
	Motor[5].DesiredSpeedInRads = 5;
	Motor[5].accelerationRate = 6000;
	Motor[5].decelerationRate = 6000;

/*  Motor6 : 微流控5V小电机-直线电机，水平横向运动   */
	Motor[6].MotorNumber = 6;
	Motor[6].Status = 0,
	Motor[6].htim_x = &htim7,
	//机械参数
	Motor[6].deceleration_ratio = 1;
	Motor[6].step_angle = 18;
	Motor[6].mircro_steps = 8;
	Motor[6].MaxSpeedInRads= 60;
	//设定默认速度参数，以下为实测优化后结果，可以通过参数控制模式修改
	Motor[6].StartupSpeedInRads = 5;
	Motor[6].DesiredSpeedInRads = 25;
	Motor[6].accelerationRate = 12000;
	Motor[6].decelerationRate = 12000;
#endif

#ifdef CiFenLi
/*  Motor6 : 磁分离5V摇匀直流电机  */
	Motor[6].MotorNumber = 6;
	Motor[6].Status = 0,
	Motor[6].htim_x = &htim12,

	//设定默认的PWM控制频率，设置占空比来控制直流电机输出
	Motor[6].StepperSpeedTMR = 400 ;  			// PWM控制直流电机频率：100KHz/400=250Hz
	Motor[6].NumberofSteps_StopAccel = 100 ; 	// 此参数在直流电机应用下，定义为占空比
	Motor[6].AccelerationTimeTMR = Motor[6].StepperSpeedTMR ; // 此参数在直流电机应用下，定义实际高电平的TMR计时器个数

/*  Motor7 : 磁分离24V洗液直流电机  */
	Motor[7].MotorNumber = 7;
	Motor[7].Status = 0,
	Motor[7].htim_x = &htim12,

	//设定默认的PWM控制频率，设置占空比来控制直流电机输出
	Motor[7].StepperSpeedTMR = 400 ;  			// PWM控制直流电机频率：100KHz/400=250Hz
	Motor[7].NumberofSteps_StopAccel = 100 ; 	// 此参数在直流电机应用下，定义为占空比
	Motor[7].AccelerationTimeTMR = Motor[7].StepperSpeedTMR ; 	// 此参数在直流电机应用下，定义实际高电平的TMR计时器个数
#endif

#ifdef L298N_StepMotorCtrl
/*  Motor6 : 微流控5V小电机-旋转电机，垂直上下运动  理想速度：20rads/s 导程0.5mm/rad 行进速度:10mm/s */
	Motor[6].MotorNumber = 6;
	Motor[6].Status = 0;
	Motor[6].htim_x = &htim7;
	//机械参数
	Motor[6].deceleration_ratio = 25;
	Motor[6].step_angle = 18;
	Motor[6].mircro_steps = 8;
	Motor[6].MaxSpeedInRads= 100;
	//设定默认速度参数，以下为实测优化后结果，可以通过参数控制模式修改
	Motor[6].StartupSpeedInRads = 5;
	Motor[6].DesiredSpeedInRads = 20;
	Motor[6].accelerationRate = 20000;
	Motor[6].decelerationRate = 20000;
#endif
}



void Motor5_AB(void) // 电机5状态1
{VM5_IN1_H();	VM5_IN2_L();	VM5_IN3_H()	;	VM5_IN4_L();}
void Motor5_aB(void) // 电机5状态2
{VM5_IN1_L();	VM5_IN2_H();	VM5_IN3_H()	;	VM5_IN4_L();}
void Motor5_ab(void) // 电机5状态3
{VM5_IN1_L();	VM5_IN2_H();	VM5_IN3_L()	;	VM5_IN4_H();}
void Motor5_Ab(void) // 电机5状态4
{VM5_IN1_H();	VM5_IN2_L();	VM5_IN3_L()	;	VM5_IN4_H();}
void Motor5_Release(void) // 电机5释放锁定
{VM5_IN1_L();	VM5_IN2_L();	VM5_IN3_L()	;	VM5_IN4_L();}

void Motor6_AB(void) // 电机6状态1
{VM6_IN1_H();	VM6_IN2_L();	VM6_IN3_H()	;	VM6_IN4_L();}
void Motor6_aB(void) // 电机6状态2
{VM6_IN1_L();	VM6_IN2_H();	VM6_IN3_H()	;	VM6_IN4_L();}
void Motor6_ab(void) // 电机6状态3
{VM6_IN1_L();	VM6_IN2_H();	VM6_IN3_L()	;	VM6_IN4_H();}
void Motor6_Ab(void) // 电机6状态4
{VM6_IN1_H();	VM6_IN2_L();	VM6_IN3_L()	;	VM6_IN4_H();}
void Motor6_A(void)
{VM6_IN1_H();	VM6_IN2_L();}
void Motor6_a(void)
{VM6_IN1_L();	VM6_IN2_H();}
void Motor6_B(void)
{VM6_IN3_H();	VM6_IN4_L();}
void Motor6_b(void)
{VM6_IN3_L();	VM6_IN4_H();}
void Motor6_A_release(void)
{VM6_IN1_L();	VM6_IN2_L();}
void Motor6_B_release(void)
{VM6_IN3_L();	VM6_IN4_L();}
void Motor6_Release(void) // 电机6释放锁定
{VM6_IN1_L();	VM6_IN2_L();	VM6_IN3_L()	;	VM6_IN4_L();}

void Motor7_AB(void) // 电机7状态1
{VM7_IN1_H();	VM7_IN2_L();	VM7_IN3_H()	;	VM7_IN4_L();}
void Motor7_aB(void) // 电机7状态2
{VM7_IN1_L();	VM7_IN2_H();	VM7_IN3_H()	;	VM7_IN4_L();}
void Motor7_ab(void) // 电机7状态3
{VM7_IN1_L();	VM7_IN2_H();	VM7_IN3_L()	;	VM7_IN4_H();}
void Motor7_Ab(void) // 电机7状态4
{VM7_IN1_H();	VM7_IN2_L();	VM7_IN3_L()	;	VM7_IN4_H();}
void Motor7_Release(void) // 电机7释放锁定
{VM7_IN1_L();	VM7_IN2_L();	VM7_IN3_L()	;	VM7_IN4_L();}

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
}



/*** 电机使能和复位找0点初始化，输入参数为8bits，低位为1表示初始化电机1，例如：Motor_Num = 5(00000101),初始化电机1&3 ***/
uint8_t ALL_Motors_Init(uint8_t Motor_Num)
{
	uint8_t Motor_Init_Result = 0 ;
	printf("Reseting Motors:0x%x ...\r\n",Motor_Num);
#ifdef JiaYangZhen
	if ( Motor_Num & 0b00000001 ){
		Motor1_Enable();
		if ( Motor_Reset(&Motor[1]) ){
			Motor_Init_Result = Motor_Init_Result | 0b00000001 ;
		}
	}
	HAL_Delay(MotorInitDelay);
	if ( Motor_Num & 0b00000100 ){
		Motor3_Enable();
		if ( Motor_Reset(&Motor[3]) ){
			Motor_Init_Result = Motor_Init_Result | 0b00000100 ;
		}
	}
	HAL_Delay(MotorInitDelay);
	if ( Motor_Num & 0b00000010 ){
		Motor2_Enable();
		if ( Motor_Reset(&Motor[2]) ){
			Motor_Init_Result = Motor_Init_Result | 0b00000010 ;
		}
	}
#else
	HAL_Delay(MotorInitDelay);
	if ( Motor_Num & 0b00000100 ){
		Motor3_Enable();
		if ( Motor_Reset(&Motor[3]) ){
			Motor_Init_Result = Motor_Init_Result | 0b00000100 ;
		}
	}
	HAL_Delay(MotorInitDelay);
	if ( Motor_Num & 0b00000010 ){
		Motor2_Enable();
		if ( Motor_Reset(&Motor[2]) ){
			Motor_Init_Result = Motor_Init_Result | 0b00000010 ;
		}
	}
	if ( Motor_Num & 0b00000001 ){
		Motor1_Enable();
		if ( Motor_Reset(&Motor[1]) ){
			Motor_Init_Result = Motor_Init_Result | 0b00000001 ;
		}
	}
#endif

	HAL_Delay(MotorInitDelay);
	if ( Motor_Num & 0b00001000 ){
		Motor4_Enable();
		if ( Motor_Reset(&Motor[4]) ){
			Motor_Init_Result = Motor_Init_Result | 0b00001000 ;
		}
	}
	HAL_Delay(MotorInitDelay);
	if ( Motor_Num & 0b00010000 ){
		VM5_Enable_A();	VM5_Enable_B();
		if ( Motor_Reset(&Motor[5]) ){
			Motor_Init_Result = Motor_Init_Result | 0b00010000 ;
		}
	}
	HAL_Delay(MotorInitDelay);
	if ( Motor_Num & 0b00100000 ){
		VM6_Enable_A();	VM6_Enable_B();
		if ( Motor_Reset(&Motor[6]) ){
			Motor_Init_Result = Motor_Init_Result | 0b00100000 ;
		}
	}
	HAL_Delay(MotorInitDelay);
	if ( Motor_Num & 0b01000000 ){
		VM7_Enable_A();	VM7_Enable_B();
		if ( Motor_Reset(&Motor[7]) ){
			Motor_Init_Result = Motor_Init_Result | 0b01000000 ;
		}
	}
	HAL_Delay(MotorInitDelay);
	if ( Motor_Num & 0b10000000 ){
		VM8_Enable_A();	VM8_Enable_B();
		if ( Motor_Reset(&Motor[8]) ){
			Motor_Init_Result = Motor_Init_Result | 0b10000000 ;
		}
	}
	HAL_Delay(MotorInitDelay);
	printf("Reseting Motors Result:0x%x ...\r\n",Motor_Init_Result);
	return Motor_Init_Result;
}

uint32_t AccelDecelTimeCompute(uint32_t AccelDecelRate)  //根据输入的加减速率，计算加减速计时器的TMR
{
	uint32_t temp_AccelDecelTimeTMR;
	if(AccelDecelRate > MOTORTIM_TMR){
		printf("[WRONG]AccelDecel Rate Oversize!\r\n"); //如果加减速超过MOTORTIM_TMR（100000Hz/s），判断过快报错
		return 10000;  // 返回一个较大的加速度增量10kHz
	}
	temp_AccelDecelTimeTMR = MOTORTIM_TMR / AccelDecelRate ;  // 计算对应的加减速计时器TMR
	return temp_AccelDecelTimeTMR;
}

void AccelDecel(uint32_t AccelDecelState,struct MotorDefine *a)
{
	switch (AccelDecelState){
	case 0:
	break;

	case ACCEL: // accelerate
		a->ActualSpeedInHz ++ ;
		if (a->ActualSpeedInHz >= a->DesiredSpeedInHz){
			a->ActualSpeedInHz = a->DesiredSpeedInHz;
			AccelDecelState = 0;
		}
		a->StepperSpeedTMR = MOTORTIM_TMR / a->ActualSpeedInHz;
	break;

	case DECEL: // decelerate
		a->ActualSpeedInHz -- ;
		if (a->ActualSpeedInHz <= a->StartupSpeedInHz){
			a->ActualSpeedInHz = a->StartupSpeedInHz;
			AccelDecelState = 0;
		}
		a->StepperSpeedTMR = MOTORTIM_TMR / a->ActualSpeedInHz;
	}
}

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
	else  // 如果行进距离不能完成完整的加减速曲线，则前1/3加速，后1/3减速
	{
		a->NumberofSteps_StopAccel = a->NumberofSteps /3*2 ;
		a->NumberofSteps_BeginDecel = a->NumberofSteps /3 ;
	}
	if ( a->MotorNumber == 4 ){		// 电机4柱塞泵，防止注液时挂液，取消减速使电机高速注液
		a->NumberofSteps_BeginDecel = 0 ;
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
		Motor[temp->MotorNumber].Status = 0 ;
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
	Motor[temp->MotorNumber].NumberofSteps = Motor[temp->MotorNumber].NumberofSteps + 5*Motor[temp->MotorNumber].mircro_steps;
	HAL_TIM_Base_Start_IT(Motor[temp->MotorNumber].htim_x);
}

void MotorMove_position_lowspeed(struct MotorDefine *temp  , int32_t targer_position , float low_speed )
{
	if (Motor[temp->MotorNumber].Status == 1){
		printf("[WRONG] Position Set Failed,Motor%d is busy!\r\n",Motor[temp->MotorNumber].MotorNumber);
		return ;
	}
	else {
		Motor[temp->MotorNumber].Status = 1 ;
	}

	Motor[temp->MotorNumber].StepsInOneCircle = (360 / Motor[temp->MotorNumber].step_angle) * Motor[temp->MotorNumber].deceleration_ratio * Motor[temp->MotorNumber].mircro_steps;
	//Motor[temp->MotorNumber].StartupSpeedInHz = Motor[temp->MotorNumber].StepsInOneCircle * Motor[temp->MotorNumber].StartupSpeedInRads ;
	//Motor[temp->MotorNumber].ActualSpeedInHz = Motor[temp->MotorNumber].StartupSpeedInHz;
	Motor[temp->MotorNumber].ActualSpeedInHz = Motor[temp->MotorNumber].StepsInOneCircle * low_speed;
	//Motor[temp->MotorNumber].DesiredSpeedInHz = Motor[temp->MotorNumber].StepsInOneCircle * Motor[temp->MotorNumber].DesiredSpeedInRads ;
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

	//Motor_AccelDecel_waveCalculate(&Motor[temp->MotorNumber]);  // 计算电机加减速曲线
	Motor[temp->MotorNumber].NumberofSteps_StopAccel = Motor[temp->MotorNumber].NumberofSteps;
	Motor[temp->MotorNumber].NumberofSteps_BeginDecel = 0;

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

void MotorRun_LowSpeed(struct MotorDefine *temp)
{
	if (Motor[temp->MotorNumber].Status == 1){
		printf("[WRONG]MotorRun_LowSpeed Failed,Motor%d is busy!\r\n",Motor[temp->MotorNumber].MotorNumber);
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

	// 计算： 单圈步数、启动速度、目标速度、行进步数、加减速时间
	temp->StepsInOneCircle = (360 / temp->step_angle) * temp->deceleration_ratio * temp->mircro_steps;
	temp->StartupSpeedInHz = temp->StepsInOneCircle * temp->StartupSpeedInRads ;
	temp->StepperSpeedTMR = MOTORTIM_TMR / temp->StartupSpeedInHz;
	temp->NumberofSteps = temp->NumberofRads * temp->StepsInOneCircle ;

	//不进行加减速，电机保持最小速度运行
	Motor[temp->MotorNumber].NumberofSteps_StopAccel = temp->NumberofSteps;
	Motor[temp->MotorNumber].NumberofSteps_BeginDecel = 0;

	Motor[temp->MotorNumber].StepsInOneCircle = temp->StepsInOneCircle ;
	Motor[temp->MotorNumber].StartupSpeedInHz = temp->StartupSpeedInHz ;
	Motor[temp->MotorNumber].StepperSpeedTMR = temp->StepperSpeedTMR ;
	Motor[temp->MotorNumber].NumberofSteps = temp->NumberofSteps ;
	Motor[temp->MotorNumber].MotorDirection = temp->MotorDirection ;
	Motor[temp->MotorNumber].AccelerationTimeTMR = 10000 ;
	Motor[temp->MotorNumber].DecelerationTimeTMR = 10000 ;
	Motor[temp->MotorNumber].TargetPosition = -16777200 ; //暂时设置目标位置为无法达到的值，参数控制模式用步进数控制中断停止

	MotorDirection_SetUp(&Motor[temp->MotorNumber]) ;
	HAL_TIM_Base_Start_IT(Motor[temp->MotorNumber].htim_x);
}


/*            *****************    0x20-0b00100000 电机复位 ：  ****************** */
// 根据协议，通过USART5进行出串口通讯，输入步进电机的 【地址】 即可，使用程序优化配置好的电机参数对电机进行复位（需要配合0位开关）
// 返回值： SUCCESS-1-完成，正在运行  FAIL-0
// 方案：控制电机运动上限圈数为10转，过程中如果触发0位信号则停止运动。如果电机初始位置已经触发0位信号，则反方向运动一小段时间，再找0位
uint8_t Motor_Reset(struct MotorDefine *temp)
{
	if (Motor[temp->MotorNumber].Status == 1){
		printf("[WRONG] Reset Failed,Motor%d is busy!\r\n",temp->MotorNumber);
		return FAIL;
	}
	*temp = Motor[temp->MotorNumber];

	temp->NumberofRads = 30;

	if (temp->MotorNumber == 1){
		if ( Motor1_reset_OPTstatus ){
			temp->MotorDirection = 1 ;
			MotorRun_LowSpeed(temp);
			HAL_Delay(MotorResetDelay);
			for(uint32_t i=0 ; Motor1_reset_OPTstatus ; i++){
				if(i>500) {
					printf("[WRONG] Overtime! Reset Motor%d Failed!\r\n",temp->MotorNumber);
					Motor[temp->MotorNumber].NumberofSteps = 2;
					return FAIL;
				}
				else {HAL_Delay(1);}
			}
			Motor[temp->MotorNumber].NumberofSteps = 2;
		}
		HAL_Delay(MotorResetDelay);
		if (Motor1_Nreset_OPTstatus){
			temp->MotorDirection = 0 ;
			MotorRun_LowSpeed(temp);
			for(uint32_t i=0 ; Motor1_Nreset_OPTstatus ; i++){
				if(i>5000) {
					printf("[WRONG] Overtime! Reset Motor%d Failed!\r\n",temp->MotorNumber);
					Motor[temp->MotorNumber].NumberofSteps = 2;
					return FAIL;
				}
				else {HAL_Delay(1);}
			}
			Motor[temp->MotorNumber].NumberofSteps = 2;
			return SUCCESS;
		}
	}

	if (temp->MotorNumber == 2){
		if ( Motor2_reset_OPTstatus ){
			temp->MotorDirection = 1 ;
			MotorRun_LowSpeed(temp);
			HAL_Delay(MotorResetDelay);
			for(uint32_t i=0 ; Motor2_reset_OPTstatus ; i++){
				if(i>500) {
					printf("[WRONG] Overtime! Reset Motor%d Failed!\r\n",temp->MotorNumber);
					Motor[temp->MotorNumber].NumberofSteps = 2;
					return FAIL;
				}
				else {HAL_Delay(1);}
			}
			Motor[temp->MotorNumber].NumberofSteps = 2;
		}
		HAL_Delay(MotorResetDelay);
		if (Motor2_Nreset_OPTstatus){
			temp->MotorDirection = 0 ;
			MotorRun_LowSpeed(temp);
			for(uint32_t i=0 ; Motor2_Nreset_OPTstatus ; i++){
				if(i>5000) {
					printf("[WRONG]Overtime! Reset Motor%d Failed!\r\n",temp->MotorNumber);
					Motor[temp->MotorNumber].NumberofSteps = 2;
					return FAIL;
				}
				else {HAL_Delay(1);}
			}
			Motor[temp->MotorNumber].NumberofSteps = 2;
			return SUCCESS;
		}
	}

	if (temp->MotorNumber == 3){
		if ( Motor3_reset_OPTstatus ){
			temp->MotorDirection = 1 ;
			MotorRun_LowSpeed(temp);
			HAL_Delay(MotorResetDelay);
			HAL_Delay(MotorResetDelay);
			for(uint32_t i=0 ; Motor3_reset_OPTstatus ; i++){
				if(i>500) {
					printf("[WRONG] Overtime! Reset Motor%d Failed!\r\n",temp->MotorNumber);
					Motor[temp->MotorNumber].NumberofSteps = 2;
					return FAIL;
				}
				else {HAL_Delay(1);}
			}
			Motor[temp->MotorNumber].NumberofSteps = 2;
		}
		HAL_Delay(MotorResetDelay);
		if (Motor3_Nreset_OPTstatus){
			temp->MotorDirection = 0 ;
			MotorRun_LowSpeed(temp);
			for(uint32_t i=0 ; Motor3_Nreset_OPTstatus ; i++){
				if(i>4000) {
					printf("[WRONG] Overtime! Reset Motor%d Failed!\r\n",temp->MotorNumber);
					Motor[temp->MotorNumber].NumberofSteps = 2;
					return FAIL;
				}
				else {HAL_Delay(1);}
			}
			Motor[temp->MotorNumber].NumberofSteps = 2;
			return SUCCESS;
		}
	}

	if (temp->MotorNumber == 4){
		if ( Motor4_reset_OPTstatus ){
			temp->MotorDirection = 1 ;
			temp->NumberofRads = 10 ;
			MotorMove_steps(temp);
			HAL_Delay(MotorResetDelay);
			for(uint32_t i=0 ; Motor4_reset_OPTstatus ; i++){
				if(i>500) {
					printf("[WRONG] Overtime! Reset Motor%d Failed!\r\n",temp->MotorNumber);
					Motor[temp->MotorNumber].NumberofSteps = 2;
					return FAIL;
				}
				else {HAL_Delay(1);}
			}
			Motor[temp->MotorNumber].NumberofSteps = 2;
		}
		HAL_Delay(MotorResetDelay);
		if (Motor4_Nreset_OPTstatus){
			temp->MotorDirection = 0 ;
			temp->NumberofRads = 10 ;
			MotorMove_steps(temp);
			for(uint32_t i=0 ; Motor4_Nreset_OPTstatus ; i++){
				if(i>8000) {
					printf("[WRONG] Overtime! Reset Motor%d Failed!\r\n",temp->MotorNumber);
					Motor[temp->MotorNumber].NumberofSteps = 2;
					return FAIL;
				}
				else {HAL_Delay(1);}
			}
			Motor[temp->MotorNumber].NumberofSteps = 2;
			return SUCCESS;
		}
	}

	if (temp->MotorNumber == 5){
		if ( Motor5_reset_OPTstatus ){
			temp->MotorDirection = 1 ;
			MotorRun_LowSpeed(temp);
			HAL_Delay(MotorResetDelay);
			for(uint32_t i=0 ; Motor5_reset_OPTstatus ; i++){
				if(i>500) {
					printf("[WRONG1]Overtime! Reset Motor%d Failed!\r\n",temp->MotorNumber);
					Motor[temp->MotorNumber].NumberofSteps = 2;
					return FAIL;
				}
				else {HAL_Delay(1);}
			}
			Motor[temp->MotorNumber].NumberofSteps = 2;
		}
		HAL_Delay(MotorResetDelay);
		if (Motor5_Nreset_OPTstatus){
			temp->MotorDirection = 0 ;
			MotorRun_LowSpeed(temp);
			for(uint32_t i=0 ; Motor5_Nreset_OPTstatus ; i++){
				if(i>5000) {
					printf("[WRONG2]Overtime! Reset Motor%d Failed!\r\n",temp->MotorNumber);
					Motor[temp->MotorNumber].NumberofSteps = 2;
					return FAIL;
				}
				else {HAL_Delay(1);}
			}
			Motor[temp->MotorNumber].NumberofSteps = 2;
			return SUCCESS;
		}
	}

	if (temp->MotorNumber == 6){
		if ( Motor6_reset_OPTstatus ){
			temp->MotorDirection = 1 ;
			temp->NumberofRads = 10 ;
			MotorRun_LowSpeed(temp);
			HAL_Delay(MotorResetDelay);
			for(uint32_t i=0 ; Motor6_reset_OPTstatus ; i++){
				if(i>500) {
					printf("[WRONG]1Overtime! Reset Motor%d Failed!\r\n",temp->MotorNumber);
					Motor[temp->MotorNumber].NumberofSteps = 2;
					return FAIL;
				}
				else {HAL_Delay(1);}
			}
			Motor[temp->MotorNumber].NumberofSteps = 2;
		}
		HAL_Delay(MotorResetDelay);
		if (Motor6_Nreset_OPTstatus){
			temp->MotorDirection = 0 ;
			temp->NumberofRads = 50 ;
			MotorRun_LowSpeed(temp);
			for(uint32_t i=0 ; Motor6_Nreset_OPTstatus ; i++){
				if(i>5000) {
					printf("[WRONG]2Overtime! Reset Motor%d Failed!\r\n",temp->MotorNumber);
					Motor[temp->MotorNumber].NumberofSteps = 2;
					return FAIL;
				}
				else {HAL_Delay(1);}
			}
			Motor[temp->MotorNumber].NumberofSteps = 2;
			return SUCCESS;
		}
	}


	return FAIL;
}

uint8_t Motor4_SuckInMode(uint32_t x_uL)  // 电机4最大排量1000uL，总行程10rads（2000步），每步0.5uL
{
#ifdef JiaYangZhen
	OUT5_OFF();
#endif
#ifdef CiFenLi
	OUT5_ON();
	OUT6_OFF();
#endif
#ifdef DushuModule
	OUT6_ON();	//吸液电磁阀，NC
	OUT5_OFF();	//注液电磁阀，NC
#endif
	HAL_Delay(300);
	//printf("Motor4_Sucks in %lduL...\r\n", x_uL);
	int32_t target_steps = 0 ;
#ifdef CiFenLi
	target_steps = x_uL * 2 * Motor[4].mircro_steps ;
#endif
#ifdef JiaYangZhen
	target_steps = x_uL * 8 * Motor[4].mircro_steps ;
#endif
#ifdef DushuModule
	target_steps = x_uL * 8 * Motor[4].mircro_steps ;
#endif
	if(Motor[4].Status == 1){
		return FAIL;
	}
	if ( Motor[4].StepPosition != 0 ){
		MotorMove_position(&Motor[4], 0 );
	}
	for(uint32_t i = 0 ; Motor[4].Status ; i++){
		if(i<3000){
			i++;
			HAL_Delay(1);
		}
		else{
			return FAIL;
		}
	}
	MotorMove_position(&Motor[4], target_steps );

	return SUCCESS;
}

uint8_t Motor4_PushOutMode(uint32_t x_uL)
{
#ifdef JiaYangZhen
	OUT5_OFF();
#endif
#ifdef CiFenLi
	OUT5_OFF();
	OUT6_ON();
#endif
#ifdef DushuModule
	OUT6_OFF();
	OUT5_ON();
#endif
	HAL_Delay(300);
	//printf("Motor4_Pushs out uL...\r\n");
	int32_t target_position = 0 ;
#ifdef CiFenLi
	target_position = Motor[4].StepPosition - (x_uL * 2 * Motor[4].mircro_steps) ;
#endif
#ifdef JiaYangZhen
	target_position = Motor[4].StepPosition - (x_uL * 8 * Motor[4].mircro_steps) ;
#endif
#ifdef DushuModule
	target_position = Motor[4].StepPosition - (x_uL * 8 * Motor[4].mircro_steps) ;
#endif

	if(target_position < 0){
		printf("[WRONG]Push out Number Overflow!\r\n Maximum Number:%ld uL\r\n",Motor[4].StepPosition/Motor[4].mircro_steps/2);
		return FAIL;
	}
	if(Motor[4].Status == 1){
		return FAIL;
	}
	MotorMove_position(&Motor[4], target_position );

	return SUCCESS;
}

/*            *****************    0x10-0b00010000 直流电机控制模式 ：  ******************
根据协议，通过USART5进行出串口通讯，输入直流电机的【编号、AB相、占空比】参数
Status - 0x02 代表A相使能，0x01代表B相使能。同一个电机的AB相占空比一致 ***/
void DC_Motor_ON(struct MotorDefine *temp ,char x, uint32_t Duty_Cycle)
{
	if ( x == 'A' ){
		Motor[temp->MotorNumber].Status = Motor[temp->MotorNumber].Status | 0b00000010 ;
		if ( temp->MotorNumber == 6 ){
			VM6_Enable_A();
		}
		else if ( temp->MotorNumber == 7 ){
			VM7_Enable_A();
		}
		else if ( temp->MotorNumber == 8 ){
			VM8_Enable_A();
		}
	}
	else if ( x == 'B' ){
		Motor[temp->MotorNumber].Status = Motor[temp->MotorNumber].Status | 0b00000001 ;
		if ( temp->MotorNumber == 6 ){
			VM6_Enable_B();
		}
		else if ( temp->MotorNumber == 7 ){
			VM7_Enable_B();
		}
		else if ( temp->MotorNumber == 8 ){
			VM8_Enable_B();
		}
	}

	Motor[temp->MotorNumber].NumberofSteps_StopAccel = Duty_Cycle;
	Motor[temp->MotorNumber].AccelerationTimeTMR = Duty_Cycle * Motor[temp->MotorNumber].StepperSpeedTMR / Motor[temp->MotorNumber].DecelerationTimeTMR ;
	HAL_TIM_Base_Start_IT(Motor[temp->MotorNumber].htim_x);
}

void DC_Motor_OFF(struct MotorDefine *temp ,char x)
{
	if ( x == 'A' ){
		Motor[temp->MotorNumber].Status = Motor[temp->MotorNumber].Status & 0b11111101 ;
		if ( temp->MotorNumber == 6 ){
			VM6_Disable_A();
		}
		else if ( temp->MotorNumber == 7 ){
			VM7_Disable_A();
		}
		else if ( temp->MotorNumber == 8 ){
			VM8_Disable_A();
		}
	}
	else if ( x == 'B' ){
		Motor[temp->MotorNumber].Status = Motor[temp->MotorNumber].Status & 0b11111110 ;
		if ( temp->MotorNumber == 6 ){
			VM6_Disable_B();
		}
		else if ( temp->MotorNumber == 7 ){
			VM7_Disable_B();
		}
		else if ( temp->MotorNumber == 8 ){
			VM8_Disable_B();
		}
	}

	if ( Motor[6].Status | Motor[7].Status | Motor[8].Status ){;}
	else{
		HAL_TIM_Base_Stop_IT(Motor[temp->MotorNumber].htim_x);
	}
}


