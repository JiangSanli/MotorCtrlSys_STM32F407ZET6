
#ifndef __MYADC_H__
#define __MYADC_H__

#include "main.h"
#include "MotorCtrl.h"
#include "stdio.h"
#include "string.h"
#include "adc.h"
#include "dac.h"
#include "myADC.h"


extern uint16_t ADC_Values[2];

void Start_DMA_ADC1_CH10CH11(void);
void STOP_DMA_ADC1_CH10CH11(void);
uint16_t get_ADC1_Current_Phase(uint8_t x);


#endif
