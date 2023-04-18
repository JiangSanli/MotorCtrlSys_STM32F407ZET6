

#include "main.h"
#include "cmsis_os.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "stdio.h"
#include "MotorCtrl.h"
#include "stdlib.h"
#include "adc.h"
#include "myADC.h"


uint16_t ADC_Values[2]={0};


//DMA循环扫描ADC，调用一次即可持续采集，特别注意：main函数中DMA初始化放在ADC初始化前面
void Start_DMA_ADC1_CH10CH11(void)
{
  HAL_ADC_Start_DMA(&hadc1,(uint32_t *)ADC_Values,2);
}

void STOP_DMA_ADC1_CH10CH11(void)
{
	HAL_ADC_Stop_DMA(&hadc1);
}

uint16_t Get_ADC1_Value(uint32_t channel_x)
{
	ADC_ChannelConfTypeDef ADC1_ChanConf;

	ADC1_ChanConf.Channel = channel_x;                            	//通道
	ADC1_ChanConf.Rank = 1;                                       	//第1个序列，序列1
	ADC1_ChanConf.SamplingTime = ADC_SAMPLETIME_15CYCLES;      		//采样时间
	if (HAL_ADC_ConfigChannel(&hadc1, &ADC1_ChanConf) != HAL_OK) 	//通道配置
	{
		Error_Handler();
	}
	HAL_ADC_Start(&hadc1);                               	//开启ADC
	HAL_ADC_PollForConversion(&hadc1, 10);                	//轮询转换

	return (uint16_t) HAL_ADC_GetValue(&hadc1);	 			//返回最近一次ADC1规则组的转换结果
}

// get Motor[6] AorB phase current, units:mA
// Phase A: x=0 , Phase B: x=1
uint16_t get_ADC1_Current_Phase(uint8_t x)
{
	return 0.5*Get_ADC1_Value(x+10);
}

