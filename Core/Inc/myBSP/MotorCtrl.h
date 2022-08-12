
#ifndef __MOTORCTRL_H__
#define __MOTORCTRL_H__

#include "main.h"

#define MOTORTIM_TMR 100000 // 设定STM32F4单片机计时器中断频率为100kHz

//#define CiFenLi  		// 磁分离电机控制，define了后则执行磁分离部分代码
#define JiaYangZhen 	// 加样针模块控制，两个42步进电机，不适用编码器控制采用编码器闭环控制
#define JiaYangZhen_EncoderMode  // 加样针模块编码器控制

struct MotorDefine {
	//电机本身机械参数-固定值
	float 	 deceleration_ratio;		// 减速比
	float    step_angle;				// 步距角
	uint32_t mircro_steps; 				// 细分数（根据不同型号和使用场景匹配）
	float    MaxSpeedInRads;			// 电机运转最高转速 rads/s
	uint32_t Encoder_PulsePerRad;		// 如果使用编码器，电机走一圈，编码器的脉冲数量

	//设定的电机编号、方向、速度、距离、加速度和减速度
	//位置控制模式只需要输入MotorNumber，StepPosition，启动速度、目标速度、加减色为默认值，方向和距离根据位置计算
	float    StartupSpeedInRads;		// 电机开始启动的转速（不能超过电机规格中空载启动频率）
	float    DesiredSpeedInRads;		// 电机速度
	uint32_t accelerationRate;			// 加速度率，单位：Hz/s
	uint32_t decelerationRate;			// 减速度率，单位：Hz/s

	uint8_t  MotorNumber;				// 被控单机编号
	uint8_t  MotorDirection;			// 方向
	float    NumberofRads;				// 电机需要运行的距离-rads

	int32_t  StepPosition;				// 电机位置步数标记，用来做位置控制,
	int32_t  TargetPosition;			// 电机目标位置
	uint8_t  Status;					// 电机运行状态标志，0-空闲  1-正在运行
	TIM_HandleTypeDef *htim_x;			// 控制电机PWM的计时器

	//结合电机速度、运行距离等输入参数，计算控制TIM计时器的参数
	uint32_t StepsInOneCircle;			// 计算出驱动电机走一圈需要的脉冲数
	uint32_t StartupSpeedInHz;			// 计算电机初始和减速结束的工作频率
	uint32_t ActualSpeedInHz;			// 计算输出的实际频率
	uint32_t DesiredSpeedInHz;			// 计算需要达到的目标速度
	uint32_t StepperSpeedTMR;			// 根据计时器中断频率1M/(49+1)，计算PWM频率，实际为中断计数
	uint32_t NumberofSteps;				// 计算电机需要走的步数
	uint32_t NumberofSteps_StopAccel;	// 计算电机停止加速的步数值
	uint32_t NumberofSteps_BeginDecel;	// 计算电机开始减速的步数值
	uint32_t AccelerationTimeTMR;		// 根据accelerationRate计算出的加减速计时器中断处理计数
	uint32_t DecelerationTimeTMR;		// 根据accelerationRate计算出的加减速计时器中断处理计数
};

extern struct MotorDefine Motor[10];

#define ACCEL 				1
#define DECEL 				2
#define MotorInitDelay  	120
#define MotorInitDelay1 	300
#define FAIL 				0
#define SUCCESS 			1
#define INITFAILSTATE 		100
#define INITPASSSTATE 		99

#define Motor1_reset_direction 		Motor1_Dir_Forward()   // 磁分离42步进电机
#define Motor1_Nreset_direction 	Motor1_Dir_Backward()
#define Motor1_reset_OPTstatus		OPT1_ON()
#define Motor1_Nreset_OPTstatus		OPT1_OFF()

#ifdef CiFenLi
#define Motor2_reset_direction 		Motor2_Dir_Forward()	// 磁分离35步进电机
#define Motor2_Nreset_direction 	Motor2_Dir_Backward()
#define Motor2_reset_OPTstatus		OPT2_OFF()
#define Motor2_Nreset_OPTstatus		OPT2_ON()
#define Motor3_reset_direction 		Motor3_Dir_Forward()
#define Motor3_Nreset_direction 	Motor3_Dir_Backward()
#define Motor3_reset_OPTstatus		OPT3_ON()
#define Motor3_Nreset_OPTstatus		OPT3_OFF()
#endif

#ifdef JiaYangZhen
#define Motor2_reset_direction 		Motor2_Dir_Backward()	// 加样针模块42步进电机-X方向
#define Motor2_Nreset_direction 	Motor2_Dir_Forward()
#define Motor2_reset_OPTstatus		OPT2_ON()
#define Motor2_Nreset_OPTstatus		OPT2_OFF()
#define Motor3_reset_direction 		Motor3_Dir_Forward()	// 加样针模块42步进电机-Z方向
#define Motor3_Nreset_direction 	Motor3_Dir_Backward()
#define Motor3_reset_OPTstatus		OPT3_ON()
#define Motor3_Nreset_OPTstatus		OPT3_OFF()
#endif

#define Motor4_reset_direction 		Motor4_Dir_Forward()	// 磁分离柱塞泵
#define Motor4_Nreset_direction 	Motor4_Dir_Backward()
#define Motor4_reset_OPTstatus		OPT4_OFF()
#define Motor4_Nreset_OPTstatus		OPT4_ON()

void Motor_Data_Init(void);
void ALL_Motors_Disable(void);
uint8_t ALL_Motors_Init(void);
void print_MotorInformation(struct MotorDefine *a);
void MotorMove_steps(struct MotorDefine *temp);
void MotorMove_position(struct MotorDefine *temp  , int32_t targer_position);
void MotorMove_position_Enocder(struct MotorDefine *temp  , int32_t targer_position_encoder);
uint8_t Motor_Reset(struct MotorDefine *temp);
uint8_t Motor4_SuckInMode(uint32_t x_uL);
uint8_t Motor4_PushOutMode(uint32_t x_uL);
void Motor5_SuckOut_ON(void);
void Motor5_SuckOut_OFF(void);
void AccelDecel(uint32_t AccelDecelState,struct MotorDefine *a);
void DC_Motor_Move(void);
void DC_Motor_Stop(void);

void Motor5_AB(void);
void Motor5_aB(void);
void Motor5_ab(void);
void Motor5_Ab(void);
void Motor6_AB(void);
void Motor6_aB(void);
void Motor6_ab(void);
void Motor6_Ab(void);


#endif
