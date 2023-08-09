

#include "pid.h"


struct _PID pid1 ;

void PID_Init(struct _PID *pid,float kp,float ki,float kd,float max_ki,float max_out)
{
	pid->kp=kp;
	pid->ki=ki;
	pid->kd=kd;
	pid->maxIntegral=max_ki;
	pid->maxOutput=max_out;
}

void PID_Clear(struct _PID *pid)
{
	pid->error=0;
	pid->lastError=0;
	pid->integral=0;
	pid->output=0;
}

void PID_SingleCalc(struct _PID *pid,float SetValue,float feedback)
{
	//更新数据
	pid->lastError=pid->error;
	//pid->error=SetValue-feedback;
	pid->error=feedback-SetValue;
	//计算微分
	pid->output=(pid->error-pid->lastError)*pid->kd;
	//计算比例
	pid->output+=pid->error*pid->kp;
	//计算积分
	pid->integral+=pid->error*pid->ki;
	LIMIT(pid->integral,-pid->maxIntegral,pid->maxIntegral);//积分限幅
	pid->output+=pid->integral;
	//输出限幅
	LIMIT(pid->output,-pid->maxOutput,pid->maxOutput);
}




