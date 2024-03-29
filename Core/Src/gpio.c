/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */
#include "main.h"
/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, VM4_Step_Pin|VM4_Dir_Pin|VM6_IN1_Pin|VM6_IN2_Pin
                          |VM6_EnA_Pin|VM5_EnB_Pin|VM5_EnA_Pin|BEEP_Pin
                          |VM3_Dir_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, VM4_En_Pin|VM3_En_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOF, FDCshutdown_Pin|OUT6_Pin|OUT5_Pin|OUT4_Pin
                          |OUT3_Pin|OUT2_Pin|OUT1_Pin|VM8_EnB_Pin
                          |VM8_EnA_Pin|VM7_EnB_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, VM8_IN3_Pin|VM8_IN4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, VM7_IN3_Pin|VM7_IN4_Pin|VM7_IN1_Pin|VM7_IN2_Pin
                          |VM5_IN1_Pin|VM5_IN2_Pin|VM5_IN3_Pin|VM5_IN4_Pin
                          |VM1_Step_Pin|VM1_Dir_Pin|VM2_Step_Pin|VM2_Dir_Pin
                          |VM3_Step_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOG, VM7_EnA_Pin|VM6_EnB_Pin|LED_Heart_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, VM8_IN1_Pin|VM8_IN2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOG, LED2_Pin|LED1_Pin|LED0_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, VM6_IN3_Pin|VM6_IN4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, VM1_En_Pin|VM2_En_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = VM4_Step_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(VM4_Step_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PEPin PEPin PEPin PEPin
                           PEPin */
  GPIO_InitStruct.Pin = VM4_En_Pin|VM4_Dir_Pin|BEEP_Pin|VM3_En_Pin
                          |VM3_Dir_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : PEPin PEPin */
  GPIO_InitStruct.Pin = VM6_IN1_Pin|VM6_IN2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = FDCINTB_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(FDCINTB_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = FDCshutdown_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(FDCshutdown_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PFPin PFPin PFPin PFPin
                           PFPin PFPin PFPin PFPin
                           PFPin */
  GPIO_InitStruct.Pin = OUT6_Pin|OUT5_Pin|OUT4_Pin|OUT3_Pin
                          |OUT2_Pin|OUT1_Pin|VM8_EnB_Pin|VM8_EnA_Pin
                          |VM7_EnB_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = Liquid_Detect_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(Liquid_Detect_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PAPin PAPin */
  GPIO_InitStruct.Pin = VM8_IN3_Pin|VM8_IN4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PCPin PCPin */
  GPIO_InitStruct.Pin = Encoder3_Z_Pin|Encoder4_Z_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PBPin PBPin PBPin PBPin
                           PBPin PBPin PBPin PBPin */
  GPIO_InitStruct.Pin = VM7_IN3_Pin|VM7_IN4_Pin|VM7_IN1_Pin|VM7_IN2_Pin
                          |VM5_IN1_Pin|VM5_IN2_Pin|VM5_IN3_Pin|VM5_IN4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PGPin PGPin */
  GPIO_InitStruct.Pin = VM7_EnA_Pin|VM6_EnB_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pins : PEPin PEPin PEPin */
  GPIO_InitStruct.Pin = VM6_EnA_Pin|VM5_EnB_Pin|VM5_EnA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = Encoder2_Z_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(Encoder2_Z_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PDPin PDPin */
  GPIO_InitStruct.Pin = VM8_IN1_Pin|VM8_IN2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : PGPin PGPin PGPin PGPin */
  GPIO_InitStruct.Pin = LED2_Pin|LED1_Pin|LED0_Pin|LED_Heart_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pins : PGPin PGPin PGPin */
  GPIO_InitStruct.Pin = KEY0_Pin|KEY1_Pin|KEY2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pins : PCPin PCPin */
  GPIO_InitStruct.Pin = VM6_IN3_Pin|VM6_IN4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = Encoder1_Z_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(Encoder1_Z_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PDPin PDPin PDPin PDPin
                           PDPin */
  GPIO_InitStruct.Pin = OPT_IN1_Pin|OPT_IN2_Pin|OPT_IN3_Pin|OPT_IN4_Pin
                          |OPT_IN5_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : PGPin PGPin PGPin PGPin
                           PGPin PGPin PGPin */
  GPIO_InitStruct.Pin = OPT_IN6_Pin|OPT_IN7_Pin|OPT_IN8_Pin|OPT_IN9_Pin
                          |OPT_IN10_Pin|OPT_IN11_Pin|OPT_IN12_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pins : PBPin PBPin PBPin */
  GPIO_InitStruct.Pin = VM1_Step_Pin|VM2_Step_Pin|VM3_Step_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PBPin PBPin PBPin PBPin */
  GPIO_InitStruct.Pin = VM1_En_Pin|VM1_Dir_Pin|VM2_En_Pin|VM2_Dir_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  HAL_NVIC_SetPriority(EXTI3_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(EXTI3_IRQn);

  HAL_NVIC_SetPriority(EXTI4_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(EXTI4_IRQn);

  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* USER CODE BEGIN 2 */

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    switch(GPIO_Pin)
    {
    	case Liquid_Detect_Pin:
        	if (Liquid_Detect_GPIO_Port->IDR & Liquid_Detect_Pin){ 	// if Rising edge trigger
        		;
        	}
        	else {
        		//Follow_state = 2;		// 使用入液�???测模块时，IO下降沿中断检�???
        	}
            break;

#ifdef L298N_StepMotorCtrl
        case OPT_IN1_Pin:
        	if (OPT_IN1_GPIO_Port->IDR & OPT_IN1_Pin){ 	// if Rising edge trigger
        		if(Motor[1].MotorDirection == 0){
        			Motor[1].StepPosition =0 ;
        		}
        	}
            break;

        case OPT_IN2_Pin:
        	if (OPT_IN2_GPIO_Port->IDR & OPT_IN2_Pin){ 	// if Rising edge trigger
        		if(Motor[2].MotorDirection == 0){
        			Motor[2].StepPosition =0 ;
        		}
        	}
        	break;

        case OPT_IN3_Pin:
        	if (OPT_IN3_GPIO_Port->IDR & OPT_IN3_Pin){ 	// if Rising edge trigger
        		if(Motor[3].MotorDirection == 0){
        			Motor[3].StepPosition =0 ;
        		}
        	}
        	break;
#endif

#ifdef ALL_4port_5V
        case OPT_IN5_Pin:
        	if (OPT_IN5_GPIO_Port->IDR & OPT_IN5_Pin){ 	// if Rising edge trigger
        		if(Motor[5].MotorDirection == 0){
        			Motor[5].StepPosition =0 ;
        		}
        	}
            break;

        case OPT_IN6_Pin:
        	if (OPT_IN6_GPIO_Port->IDR & OPT_IN6_Pin){ 	// if Rising edge trigger
        		if(Motor[6].MotorDirection == 0){
        			Motor[6].StepPosition =0 ;
        		}
        	}
        	break;

        case OPT_IN7_Pin:
        	if (OPT_IN7_GPIO_Port->IDR & OPT_IN7_Pin){ 	// if Rising edge trigger
        		if(Motor[7].MotorDirection == 0){
        			Motor[7].StepPosition =0 ;
        		}
        	}
        	break;
#endif


#ifdef CiFenLi
        case OPT_IN1_Pin:
        	if (OPT_IN1_GPIO_Port->IDR & OPT_IN1_Pin){ 	// if Rising edge trigger
        		;
        	}
        	else {
        		if(Motor[1].MotorDirection == 0){
        			Motor[1].StepPosition =0 ;
        		}
        	}
            break;

        case OPT_IN2_Pin:
        	if (OPT_IN2_GPIO_Port->IDR & OPT_IN2_Pin){ 	// if Rising edge trigger
        		Motor[2].StepPosition =0 ;
        	}
        	else {
        		;
        	}
        	break;
#endif

#ifdef JiaYangZhen
        case OPT_IN2_Pin:
        	if (OPT_IN2_GPIO_Port->IDR & OPT_IN2_Pin) { 	// if Rising edge trigger
        		//Motor[2].StepPosition =0 ;
        	}
        	else {
        		if(Motor[2].MotorDirection == 0){
#ifdef JiaYangZhen_EncoderMode
        			__HAL_TIM_SET_COUNTER(&htim4,Encoder2_0position_number);
#else
        		Motor[2].StepPosition =0 ;
#endif
        		}
        	}
            break;

        case OPT_IN3_Pin:
        	if (OPT_IN3_GPIO_Port->IDR & OPT_IN3_Pin) { 	// if Rising edge trigger
        		Motor[3].StepPosition =0 ;
        	}
        	else {
        		if(Motor[3].MotorDirection == 0){
#ifdef JiaYangZhen_EncoderMode
        			__HAL_TIM_SET_COUNTER(&htim3,Encoder3_0position_number);
#else
        		//Motor[3].StepPosition =0 ;
#endif
        		}
        	}
            break;
#endif

#ifdef DuoTongDao
        case OPT_IN2_Pin:
        	if (OPT_IN2_GPIO_Port->IDR & OPT_IN2_Pin){ 	// if Rising edge trigger
        		;
        	}
        	else {
        		Motor[2].StepPosition =0 ;
        	}
        	break;

        case OPT_IN3_Pin:
        	if (OPT_IN3_GPIO_Port->IDR & OPT_IN3_Pin) { 	// if Rising edge trigger
        		;
        	}
        	else {
        		Motor[3].StepPosition =0 ;
        	}
        	break;
#endif



        case OPT_IN4_Pin:
        	if (OPT_IN4_GPIO_Port->IDR & OPT_IN4_Pin) { 	// if Rising edge trigger
        		Motor[4].StepPosition =0 ;
        	}
        	else {
        		 ;
        	}
            break;

#ifdef DuoTongDao		// DuoTongDao 5V stepmotor
        case OPT_IN5_Pin:
        	if (OPT_IN5_GPIO_Port->IDR & OPT_IN5_Pin) { 	// if Rising edge trigger
        		;
        	}
        	else {
        		Motor[5].StepPosition =0 ;
        	}
            break;

        case OPT_IN6_Pin:
        	if (OPT_IN6_GPIO_Port->IDR & OPT_IN6_Pin) { 	// if Rising edge trigger
        		 ;
        	}
        	else {
        		Motor[6].StepPosition =0 ;
        	}
            break;
#endif


#ifdef WeiLiuKong		// WeiLiuKong 5V stepmotor
        case OPT_IN9_Pin:
        	if (OPT_IN9_GPIO_Port->IDR & OPT_IN9_Pin) { 	// if Rising edge trigger
        		Motor[5].StepPosition =0 ;
        	}
        	else {
        		;
        	}
            break;

        case OPT_IN10_Pin:
        	if (OPT_IN10_GPIO_Port->IDR & OPT_IN10_Pin) { 	// if Rising edge trigger
        		 ;
        	}
        	else {
        		Motor[6].StepPosition =0 ;
        	}
            break;

        case OPT_IN7_Pin:
        	if (OPT_IN7_GPIO_Port->IDR & OPT_IN7_Pin) { 	// if Rising edge trigger
        		Motor[7].StepPosition =0 ;
        	}
        	else {
        		 ;
        	}
            break;
#endif

    }
}
/* USER CODE END 2 */
