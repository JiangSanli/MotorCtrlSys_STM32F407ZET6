
#ifndef __PID_H
#define __PID_H


#include "main.h"

struct _PID
{
	float kp,ki,kd;
	float error,lastError;
	float integral,maxIntegral;
	float output,maxOutput;
};

#define LIMIT(x,min,max) (x)=(((x)<=(min))?(min):(((x)>=(max))?(max):(x)))

extern struct _PID pid1 ;

void PID_Init(struct _PID *pid,float kp,float ki,float kd,float max_ki,float max_out);
void PID_Clear(struct _PID *pid);
void PID_SingleCalc(struct _PID *pid,float SetValue,float feedback);


#endif
