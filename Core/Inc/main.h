/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "MotorCtrl.h"
#include "stdio.h"
#include "string.h"
#include "tim.h"
#include "FDC2112.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define VM4_Step_Pin GPIO_PIN_2
#define VM4_Step_GPIO_Port GPIOE
#define VM4_En_Pin GPIO_PIN_3
#define VM4_En_GPIO_Port GPIOE
#define VM4_Dir_Pin GPIO_PIN_4
#define VM4_Dir_GPIO_Port GPIOE
#define VM6_IN1_Pin GPIO_PIN_5
#define VM6_IN1_GPIO_Port GPIOE
#define VM6_IN2_Pin GPIO_PIN_6
#define VM6_IN2_GPIO_Port GPIOE
#define FDCINTB_Pin GPIO_PIN_2
#define FDCINTB_GPIO_Port GPIOF
#define FDCshutdown_Pin GPIO_PIN_3
#define FDCshutdown_GPIO_Port GPIOF
#define OUT6_Pin GPIO_PIN_5
#define OUT6_GPIO_Port GPIOF
#define OUT5_Pin GPIO_PIN_6
#define OUT5_GPIO_Port GPIOF
#define OUT4_Pin GPIO_PIN_7
#define OUT4_GPIO_Port GPIOF
#define OUT3_Pin GPIO_PIN_8
#define OUT3_GPIO_Port GPIOF
#define OUT2_Pin GPIO_PIN_9
#define OUT2_GPIO_Port GPIOF
#define OUT1_Pin GPIO_PIN_10
#define OUT1_GPIO_Port GPIOF
#define VM6_SensA_ADC_Pin GPIO_PIN_0
#define VM6_SensA_ADC_GPIO_Port GPIOC
#define VM6_SensB_ADC_Pin GPIO_PIN_1
#define VM6_SensB_ADC_GPIO_Port GPIOC
#define VM8_SensA_ADC_Pin GPIO_PIN_2
#define VM8_SensA_ADC_GPIO_Port GPIOC
#define VM8_SensB_ADC_Pin GPIO_PIN_3
#define VM8_SensB_ADC_GPIO_Port GPIOC
#define PA0_Pin GPIO_PIN_0
#define PA0_GPIO_Port GPIOA
#define Encoder4_B_Pin GPIO_PIN_1
#define Encoder4_B_GPIO_Port GPIOA
#define VM8_IN3_Pin GPIO_PIN_2
#define VM8_IN3_GPIO_Port GPIOA
#define VM8_IN4_Pin GPIO_PIN_3
#define VM8_IN4_GPIO_Port GPIOA
#define Encoder4_A_Pin GPIO_PIN_5
#define Encoder4_A_GPIO_Port GPIOA
#define Encoder3_A_Pin GPIO_PIN_6
#define Encoder3_A_GPIO_Port GPIOA
#define Encoder3_B_Pin GPIO_PIN_7
#define Encoder3_B_GPIO_Port GPIOA
#define Encoder3_Z_Pin GPIO_PIN_4
#define Encoder3_Z_GPIO_Port GPIOC
#define Encoder4_Z_Pin GPIO_PIN_5
#define Encoder4_Z_GPIO_Port GPIOC
#define VM7_IN3_Pin GPIO_PIN_0
#define VM7_IN3_GPIO_Port GPIOB
#define VM7_IN4_Pin GPIO_PIN_1
#define VM7_IN4_GPIO_Port GPIOB
#define VM8_EnB_Pin GPIO_PIN_13
#define VM8_EnB_GPIO_Port GPIOF
#define VM8_EnA_Pin GPIO_PIN_14
#define VM8_EnA_GPIO_Port GPIOF
#define VM7_EnB_Pin GPIO_PIN_15
#define VM7_EnB_GPIO_Port GPIOF
#define VM7_EnA_Pin GPIO_PIN_0
#define VM7_EnA_GPIO_Port GPIOG
#define VM6_EnB_Pin GPIO_PIN_1
#define VM6_EnB_GPIO_Port GPIOG
#define VM6_EnA_Pin GPIO_PIN_7
#define VM6_EnA_GPIO_Port GPIOE
#define VM5_EnB_Pin GPIO_PIN_8
#define VM5_EnB_GPIO_Port GPIOE
#define VM5_EnA_Pin GPIO_PIN_9
#define VM5_EnA_GPIO_Port GPIOE
#define BEEP_Pin GPIO_PIN_15
#define BEEP_GPIO_Port GPIOE
#define VM7_IN1_Pin GPIO_PIN_10
#define VM7_IN1_GPIO_Port GPIOB
#define VM7_IN2_Pin GPIO_PIN_11
#define VM7_IN2_GPIO_Port GPIOB
#define VM5_IN1_Pin GPIO_PIN_12
#define VM5_IN1_GPIO_Port GPIOB
#define VM5_IN2_Pin GPIO_PIN_13
#define VM5_IN2_GPIO_Port GPIOB
#define VM5_IN3_Pin GPIO_PIN_14
#define VM5_IN3_GPIO_Port GPIOB
#define VM5_IN4_Pin GPIO_PIN_15
#define VM5_IN4_GPIO_Port GPIOB
#define Encoder2_Z_Pin GPIO_PIN_11
#define Encoder2_Z_GPIO_Port GPIOD
#define Encoder2_A_Pin GPIO_PIN_12
#define Encoder2_A_GPIO_Port GPIOD
#define Encoder2_B_Pin GPIO_PIN_13
#define Encoder2_B_GPIO_Port GPIOD
#define VM8_IN1_Pin GPIO_PIN_14
#define VM8_IN1_GPIO_Port GPIOD
#define VM8_IN2_Pin GPIO_PIN_15
#define VM8_IN2_GPIO_Port GPIOD
#define LED2_Pin GPIO_PIN_2
#define LED2_GPIO_Port GPIOG
#define LED1_Pin GPIO_PIN_3
#define LED1_GPIO_Port GPIOG
#define LED0_Pin GPIO_PIN_4
#define LED0_GPIO_Port GPIOG
#define LED_Heart_Pin GPIO_PIN_5
#define LED_Heart_GPIO_Port GPIOG
#define KEY0_Pin GPIO_PIN_6
#define KEY0_GPIO_Port GPIOG
#define KEY1_Pin GPIO_PIN_7
#define KEY1_GPIO_Port GPIOG
#define KEY2_Pin GPIO_PIN_8
#define KEY2_GPIO_Port GPIOG
#define Encoder1_A_Pin GPIO_PIN_6
#define Encoder1_A_GPIO_Port GPIOC
#define Encoder1_B_Pin GPIO_PIN_7
#define Encoder1_B_GPIO_Port GPIOC
#define VM6_IN3_Pin GPIO_PIN_8
#define VM6_IN3_GPIO_Port GPIOC
#define VM6_IN4_Pin GPIO_PIN_9
#define VM6_IN4_GPIO_Port GPIOC
#define Encoder1_Z_Pin GPIO_PIN_8
#define Encoder1_Z_GPIO_Port GPIOA
#define OPT_IN1_Pin GPIO_PIN_3
#define OPT_IN1_GPIO_Port GPIOD
#define OPT_IN1_EXTI_IRQn EXTI3_IRQn
#define OPT_IN2_Pin GPIO_PIN_4
#define OPT_IN2_GPIO_Port GPIOD
#define OPT_IN2_EXTI_IRQn EXTI4_IRQn
#define OPT_IN3_Pin GPIO_PIN_5
#define OPT_IN3_GPIO_Port GPIOD
#define OPT_IN3_EXTI_IRQn EXTI9_5_IRQn
#define OPT_IN4_Pin GPIO_PIN_6
#define OPT_IN4_GPIO_Port GPIOD
#define OPT_IN4_EXTI_IRQn EXTI9_5_IRQn
#define OPT_IN5_Pin GPIO_PIN_7
#define OPT_IN5_GPIO_Port GPIOD
#define OPT_IN5_EXTI_IRQn EXTI9_5_IRQn
#define OPT_IN6_Pin GPIO_PIN_9
#define OPT_IN6_GPIO_Port GPIOG
#define OPT_IN6_EXTI_IRQn EXTI9_5_IRQn
#define OPT_IN7_Pin GPIO_PIN_10
#define OPT_IN7_GPIO_Port GPIOG
#define OPT_IN8_Pin GPIO_PIN_11
#define OPT_IN8_GPIO_Port GPIOG
#define OPT_IN9_Pin GPIO_PIN_12
#define OPT_IN9_GPIO_Port GPIOG
#define OPT_IN10_Pin GPIO_PIN_13
#define OPT_IN10_GPIO_Port GPIOG
#define OPT_IN11_Pin GPIO_PIN_14
#define OPT_IN11_GPIO_Port GPIOG
#define OPT_IN12_Pin GPIO_PIN_15
#define OPT_IN12_GPIO_Port GPIOG
#define VM1_Step_Pin GPIO_PIN_3
#define VM1_Step_GPIO_Port GPIOB
#define VM1_En_Pin GPIO_PIN_4
#define VM1_En_GPIO_Port GPIOB
#define VM1_Dir_Pin GPIO_PIN_5
#define VM1_Dir_GPIO_Port GPIOB
#define VM2_Step_Pin GPIO_PIN_6
#define VM2_Step_GPIO_Port GPIOB
#define VM2_En_Pin GPIO_PIN_7
#define VM2_En_GPIO_Port GPIOB
#define VM2_Dir_Pin GPIO_PIN_8
#define VM2_Dir_GPIO_Port GPIOB
#define VM3_Step_Pin GPIO_PIN_9
#define VM3_Step_GPIO_Port GPIOB
#define VM3_En_Pin GPIO_PIN_0
#define VM3_En_GPIO_Port GPIOE
#define VM3_Dir_Pin GPIO_PIN_1
#define VM3_Dir_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

#define PA0_H()		HAL_GPIO_WritePin(PA0_GPIO_Port, PA0_Pin, GPIO_PIN_SET)
#define PA0_L()		HAL_GPIO_WritePin(PA0_GPIO_Port, PA0_Pin, GPIO_PIN_RESET)
#define PA0_Toggle()		HAL_GPIO_TogglePin(PA0_GPIO_Port, PA0_Pin)

#define LED0_ON()		HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_RESET)
#define LED0_OFF()		HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_SET)
#define LED0_Toggle()		HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin)
#define LED1_ON()		HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET)
#define LED1_OFF()		HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET)
#define LED1_Toggle()		HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin)
#define LED2_ON()		HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET)
#define LED2_OFF()		HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET)
#define LED2_Toggle()		HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin)
#define LED_Heart_ON()		HAL_GPIO_WritePin(LED_Heart_GPIO_Port, LED_Heart_Pin, GPIO_PIN_RESET)
#define LED_Heart_OFF()		HAL_GPIO_WritePin(LED_Heart_GPIO_Port, LED_Heart_Pin, GPIO_PIN_SET)
#define LED_Heart_Toggle()		HAL_GPIO_TogglePin(LED_Heart_GPIO_Port, LED_Heart_Pin)
#define BEEP_ON()		HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, GPIO_PIN_SET)
#define BEEP_OFF()		HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, GPIO_PIN_RESET)
#define BEEP_Toggle()		HAL_GPIO_TogglePin(BEEP_GPIO_Port, BEEP_Pin)

#define KEY0_Pressed()		HAL_GPIO_ReadPin(KEY0_GPIO_Port, KEY0_Pin) == GPIO_PIN_RESET
#define KEY0_UnPressed()		HAL_GPIO_ReadPin(KEY0_GPIO_Port, KEY0_Pin) == GPIO_PIN_SET
#define KEY1_Pressed()		HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin) == GPIO_PIN_RESET
#define KEY1_UnPressed()		HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin) == GPIO_PIN_SET
#define KEY2_Pressed()		HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin) == GPIO_PIN_RESET
#define KEY2_UnPressed()		HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin) == GPIO_PIN_SET

//DRV8825 控制四个24V步进电机GPIO配置
#define Motor1_Enable() 		HAL_GPIO_WritePin(VM1_En_GPIO_Port, VM1_En_Pin, GPIO_PIN_RESET)
#define Motor1_Disable() 		HAL_GPIO_WritePin(VM1_En_GPIO_Port, VM1_En_Pin, GPIO_PIN_SET)
#define Motor1_Dir_Forward() 		HAL_GPIO_WritePin(VM1_Dir_GPIO_Port, VM1_Dir_Pin, GPIO_PIN_SET)
#define Motor1_Dir_Backward() 		HAL_GPIO_WritePin(VM1_Dir_GPIO_Port, VM1_Dir_Pin, GPIO_PIN_RESET)
#define Motorpluse1_High()		HAL_GPIO_WritePin(VM1_Step_GPIO_Port, VM1_Step_Pin, GPIO_PIN_SET)
#define Motorpluse1_Low()		HAL_GPIO_WritePin(VM1_Step_GPIO_Port, VM1_Step_Pin, GPIO_PIN_RESET)
#define Motorpluse1_Toggle()		HAL_GPIO_TogglePin(VM1_Step_GPIO_Port, VM1_Step_Pin)

#define Motor2_Enable() 		HAL_GPIO_WritePin(VM2_En_GPIO_Port, VM2_En_Pin, GPIO_PIN_RESET)
#define Motor2_Disable() 		HAL_GPIO_WritePin(VM2_En_GPIO_Port, VM2_En_Pin, GPIO_PIN_SET)
#define Motor2_Dir_Forward() 		HAL_GPIO_WritePin(VM2_Dir_GPIO_Port, VM2_Dir_Pin, GPIO_PIN_SET)
#define Motor2_Dir_Backward() 		HAL_GPIO_WritePin(VM2_Dir_GPIO_Port, VM2_Dir_Pin, GPIO_PIN_RESET)
#define Motorpluse2_High()		HAL_GPIO_WritePin(VM2_Step_GPIO_Port, VM2_Step_Pin, GPIO_PIN_SET)
#define Motorpluse2_Low()		HAL_GPIO_WritePin(VM2_Step_GPIO_Port, VM2_Step_Pin, GPIO_PIN_RESET)
#define Motorpluse2_Toggle()		HAL_GPIO_TogglePin(VM2_Step_GPIO_Port, VM2_Step_Pin)

#define Motor3_Enable() 		HAL_GPIO_WritePin(VM3_En_GPIO_Port, VM3_En_Pin, GPIO_PIN_RESET)
#define Motor3_Disable() 		HAL_GPIO_WritePin(VM3_En_GPIO_Port, VM3_En_Pin, GPIO_PIN_SET)
#define Motor3_Dir_Forward() 		HAL_GPIO_WritePin(VM3_Dir_GPIO_Port, VM3_Dir_Pin, GPIO_PIN_SET)
#define Motor3_Dir_Backward() 		HAL_GPIO_WritePin(VM3_Dir_GPIO_Port, VM3_Dir_Pin, GPIO_PIN_RESET)
#define Motorpluse3_High()		HAL_GPIO_WritePin(VM3_Step_GPIO_Port, VM3_Step_Pin, GPIO_PIN_SET)
#define Motorpluse3_Low()		HAL_GPIO_WritePin(VM3_Step_GPIO_Port, VM3_Step_Pin, GPIO_PIN_RESET)
#define Motorpluse3_Toggle()		HAL_GPIO_TogglePin(VM3_Step_GPIO_Port, VM3_Step_Pin)

#define Motor4_Enable() 		HAL_GPIO_WritePin(VM4_En_GPIO_Port, VM4_En_Pin, GPIO_PIN_RESET)
#define Motor4_Disable() 		HAL_GPIO_WritePin(VM4_En_GPIO_Port, VM4_En_Pin, GPIO_PIN_SET)
#define Motor4_Dir_Forward() 		HAL_GPIO_WritePin(VM4_Dir_GPIO_Port, VM4_Dir_Pin, GPIO_PIN_SET)
#define Motor4_Dir_Backward() 		HAL_GPIO_WritePin(VM4_Dir_GPIO_Port, VM4_Dir_Pin, GPIO_PIN_RESET)
#define Motorpluse4_High()		HAL_GPIO_WritePin(VM4_Step_GPIO_Port, VM4_Step_Pin, GPIO_PIN_SET)
#define Motorpluse4_Low()		HAL_GPIO_WritePin(VM4_Step_GPIO_Port, VM4_Step_Pin, GPIO_PIN_RESET)
#define Motorpluse4_Toggle()		HAL_GPIO_TogglePin(VM4_Step_GPIO_Port, VM4_Step_Pin)

//控制四路=L298N驱动芯片UM5 UM6-5V ,UM7 UM8-24V
#define VM5_IN1_H()		HAL_GPIO_WritePin(VM5_IN1_GPIO_Port, VM5_IN1_Pin, GPIO_PIN_SET)
#define VM5_IN2_H()		HAL_GPIO_WritePin(VM5_IN2_GPIO_Port, VM5_IN2_Pin, GPIO_PIN_SET)
#define VM5_IN3_H()		HAL_GPIO_WritePin(VM5_IN3_GPIO_Port, VM5_IN3_Pin, GPIO_PIN_SET)
#define VM5_IN4_H()		HAL_GPIO_WritePin(VM5_IN4_GPIO_Port, VM5_IN4_Pin, GPIO_PIN_SET)
#define VM5_IN1_L()		HAL_GPIO_WritePin(VM5_IN1_GPIO_Port, VM5_IN1_Pin, GPIO_PIN_RESET)
#define VM5_IN2_L()		HAL_GPIO_WritePin(VM5_IN2_GPIO_Port, VM5_IN2_Pin, GPIO_PIN_RESET)
#define VM5_IN3_L()		HAL_GPIO_WritePin(VM5_IN3_GPIO_Port, VM5_IN3_Pin, GPIO_PIN_RESET)
#define VM5_IN4_L()		HAL_GPIO_WritePin(VM5_IN4_GPIO_Port, VM5_IN4_Pin, GPIO_PIN_RESET)
#define VM5_Enable_A() 			HAL_GPIO_WritePin(VM5_EnA_GPIO_Port, VM5_EnA_Pin, GPIO_PIN_SET)
#define VM5_Disable_A() 		HAL_GPIO_WritePin(VM5_EnA_GPIO_Port, VM5_EnA_Pin, GPIO_PIN_RESET)
#define VM5_Enable_B() 			HAL_GPIO_WritePin(VM5_EnB_GPIO_Port, VM5_EnB_Pin, GPIO_PIN_SET)
#define VM5_Disable_B() 		HAL_GPIO_WritePin(VM5_EnB_GPIO_Port, VM5_EnB_Pin, GPIO_PIN_RESET)

#define VM6_IN1_H()		HAL_GPIO_WritePin(VM6_IN1_GPIO_Port, VM6_IN1_Pin, GPIO_PIN_SET)
#define VM6_IN2_H()		HAL_GPIO_WritePin(VM6_IN2_GPIO_Port, VM6_IN2_Pin, GPIO_PIN_SET)
#define VM6_IN3_H()		HAL_GPIO_WritePin(VM6_IN3_GPIO_Port, VM6_IN3_Pin, GPIO_PIN_SET)
#define VM6_IN4_H()		HAL_GPIO_WritePin(VM6_IN4_GPIO_Port, VM6_IN4_Pin, GPIO_PIN_SET)
#define VM6_IN1_L()		HAL_GPIO_WritePin(VM6_IN1_GPIO_Port, VM6_IN1_Pin, GPIO_PIN_RESET)
#define VM6_IN2_L()		HAL_GPIO_WritePin(VM6_IN2_GPIO_Port, VM6_IN2_Pin, GPIO_PIN_RESET)
#define VM6_IN3_L()		HAL_GPIO_WritePin(VM6_IN3_GPIO_Port, VM6_IN3_Pin, GPIO_PIN_RESET)
#define VM6_IN4_L()		HAL_GPIO_WritePin(VM6_IN4_GPIO_Port, VM6_IN4_Pin, GPIO_PIN_RESET)
#define VM6_Enable_A() 			HAL_GPIO_WritePin(VM6_EnA_GPIO_Port, VM6_EnA_Pin, GPIO_PIN_SET)
#define VM6_Disable_A() 		HAL_GPIO_WritePin(VM6_EnA_GPIO_Port, VM6_EnA_Pin, GPIO_PIN_RESET)
#define VM6_Enable_B() 			HAL_GPIO_WritePin(VM6_EnB_GPIO_Port, VM6_EnB_Pin, GPIO_PIN_SET)
#define VM6_Disable_B() 		HAL_GPIO_WritePin(VM6_EnB_GPIO_Port, VM6_EnB_Pin, GPIO_PIN_RESET)

#define VM7_IN1_H()		HAL_GPIO_WritePin(VM7_IN1_GPIO_Port, VM7_IN1_Pin, GPIO_PIN_SET)
#define VM7_IN2_H()		HAL_GPIO_WritePin(VM7_IN2_GPIO_Port, VM7_IN2_Pin, GPIO_PIN_SET)
#define VM7_IN3_H()		HAL_GPIO_WritePin(VM7_IN3_GPIO_Port, VM7_IN3_Pin, GPIO_PIN_SET)
#define VM7_IN4_H()		HAL_GPIO_WritePin(VM7_IN4_GPIO_Port, VM7_IN4_Pin, GPIO_PIN_SET)
#define VM7_IN1_L()		HAL_GPIO_WritePin(VM7_IN1_GPIO_Port, VM7_IN1_Pin, GPIO_PIN_RESET)
#define VM7_IN2_L()		HAL_GPIO_WritePin(VM7_IN2_GPIO_Port, VM7_IN2_Pin, GPIO_PIN_RESET)
#define VM7_IN3_L()		HAL_GPIO_WritePin(VM7_IN3_GPIO_Port, VM7_IN3_Pin, GPIO_PIN_RESET)
#define VM7_IN4_L()		HAL_GPIO_WritePin(VM7_IN4_GPIO_Port, VM7_IN4_Pin, GPIO_PIN_RESET)
#define VM7_Enable_A() 			HAL_GPIO_WritePin(VM7_EnA_GPIO_Port, VM7_EnA_Pin, GPIO_PIN_SET)
#define VM7_Disable_A() 		HAL_GPIO_WritePin(VM7_EnA_GPIO_Port, VM7_EnA_Pin, GPIO_PIN_RESET)
#define VM7_Enable_B() 			HAL_GPIO_WritePin(VM7_EnB_GPIO_Port, VM7_EnB_Pin, GPIO_PIN_SET)
#define VM7_Disable_B() 		HAL_GPIO_WritePin(VM7_EnB_GPIO_Port, VM7_EnB_Pin, GPIO_PIN_RESET)

#define VM8_IN1_H()		HAL_GPIO_WritePin(VM8_IN1_GPIO_Port, VM8_IN1_Pin, GPIO_PIN_SET)
#define VM8_IN2_H()		HAL_GPIO_WritePin(VM8_IN2_GPIO_Port, VM8_IN2_Pin, GPIO_PIN_SET)
#define VM8_IN3_H()		HAL_GPIO_WritePin(VM8_IN3_GPIO_Port, VM8_IN3_Pin, GPIO_PIN_SET)
#define VM8_IN4_H()		HAL_GPIO_WritePin(VM8_IN4_GPIO_Port, VM8_IN4_Pin, GPIO_PIN_SET)
#define VM8_IN1_L()		HAL_GPIO_WritePin(VM8_IN1_GPIO_Port, VM8_IN1_Pin, GPIO_PIN_RESET)
#define VM8_IN2_L()		HAL_GPIO_WritePin(VM8_IN2_GPIO_Port, VM8_IN2_Pin, GPIO_PIN_RESET)
#define VM8_IN3_L()		HAL_GPIO_WritePin(VM8_IN3_GPIO_Port, VM8_IN3_Pin, GPIO_PIN_RESET)
#define VM8_IN4_L()		HAL_GPIO_WritePin(VM8_IN4_GPIO_Port, VM8_IN4_Pin, GPIO_PIN_RESET)
#define VM8_Enable_A() 			HAL_GPIO_WritePin(VM8_EnA_GPIO_Port, VM8_EnA_Pin, GPIO_PIN_SET)
#define VM8_Disable_A() 		HAL_GPIO_WritePin(VM8_EnA_GPIO_Port, VM8_EnA_Pin, GPIO_PIN_RESET)
#define VM8_Enable_B() 			HAL_GPIO_WritePin(VM8_EnB_GPIO_Port, VM8_EnB_Pin, GPIO_PIN_SET)
#define VM8_Disable_B() 		HAL_GPIO_WritePin(VM8_EnB_GPIO_Port, VM8_EnB_Pin, GPIO_PIN_RESET)

//OPT input IN1-IN12 : NPN常开，低电平为接收到外界触发信号
#define OPT1_ON()		HAL_GPIO_ReadPin(OPT_IN1_GPIO_Port, OPT_IN1_Pin) == GPIO_PIN_RESET
#define OPT1_OFF()		HAL_GPIO_ReadPin(OPT_IN1_GPIO_Port, OPT_IN1_Pin) == GPIO_PIN_SET
#define OPT2_ON()		HAL_GPIO_ReadPin(OPT_IN2_GPIO_Port, OPT_IN2_Pin) == GPIO_PIN_RESET
#define OPT2_OFF()		HAL_GPIO_ReadPin(OPT_IN2_GPIO_Port, OPT_IN2_Pin) == GPIO_PIN_SET
#define OPT3_ON()		HAL_GPIO_ReadPin(OPT_IN3_GPIO_Port, OPT_IN3_Pin) == GPIO_PIN_RESET
#define OPT3_OFF()		HAL_GPIO_ReadPin(OPT_IN3_GPIO_Port, OPT_IN3_Pin) == GPIO_PIN_SET
#define OPT4_ON()		HAL_GPIO_ReadPin(OPT_IN4_GPIO_Port, OPT_IN4_Pin) == GPIO_PIN_RESET
#define OPT4_OFF()		HAL_GPIO_ReadPin(OPT_IN4_GPIO_Port, OPT_IN4_Pin) == GPIO_PIN_SET
#define OPT5_ON()		HAL_GPIO_ReadPin(OPT_IN5_GPIO_Port, OPT_IN5_Pin) == GPIO_PIN_RESET
#define OPT5_OFF()		HAL_GPIO_ReadPin(OPT_IN5_GPIO_Port, OPT_IN5_Pin) == GPIO_PIN_SET
#define OPT6_ON()		HAL_GPIO_ReadPin(OPT_IN6_GPIO_Port, OPT_IN6_Pin) == GPIO_PIN_RESET
#define OPT6_OFF()		HAL_GPIO_ReadPin(OPT_IN6_GPIO_Port, OPT_IN6_Pin) == GPIO_PIN_SET
#define OPT7_ON()		HAL_GPIO_ReadPin(OPT_IN7_GPIO_Port, OPT_IN7_Pin) == GPIO_PIN_RESET
#define OPT7_OFF()		HAL_GPIO_ReadPin(OPT_IN7_GPIO_Port, OPT_IN7_Pin) == GPIO_PIN_SET
#define OPT8_ON()		HAL_GPIO_ReadPin(OPT_IN8_GPIO_Port, OPT_IN8_Pin) == GPIO_PIN_RESET
#define OPT8_OFF()		HAL_GPIO_ReadPin(OPT_IN8_GPIO_Port, OPT_IN8_Pin) == GPIO_PIN_SET
#define OPT9_ON()		HAL_GPIO_ReadPin(OPT_IN9_GPIO_Port, OPT_IN9_Pin) == GPIO_PIN_RESET
#define OPT9_OFF()		HAL_GPIO_ReadPin(OPT_IN9_GPIO_Port, OPT_IN9_Pin) == GPIO_PIN_SET
#define OPT10_ON()		HAL_GPIO_ReadPin(OPT_IN10_GPIO_Port, OPT_IN10_Pin) == GPIO_PIN_RESET
#define OPT10_OFF()		HAL_GPIO_ReadPin(OPT_IN10_GPIO_Port, OPT_IN10_Pin) == GPIO_PIN_SET
#define OPT11_ON()		HAL_GPIO_ReadPin(OPT_IN11_GPIO_Port, OPT_IN11_Pin) == GPIO_PIN_RESET
#define OPT11_OFF()		HAL_GPIO_ReadPin(OPT_IN11_GPIO_Port, OPT_IN11_Pin) == GPIO_PIN_SET
#define OPT12_ON()		HAL_GPIO_ReadPin(OPT_IN12_GPIO_Port, OPT_IN12_Pin) == GPIO_PIN_RESET
#define OPT12_OFF()		HAL_GPIO_ReadPin(OPT_IN12_GPIO_Port, OPT_IN12_Pin) == GPIO_PIN_SET

//24V output: OUT1-OUT12
#define OUT1_ON()		HAL_GPIO_WritePin(OUT1_GPIO_Port, OUT1_Pin, GPIO_PIN_SET)
#define OUT1_OFF()		HAL_GPIO_WritePin(OUT1_GPIO_Port, OUT1_Pin, GPIO_PIN_RESET)
#define OUT2_ON()		HAL_GPIO_WritePin(OUT2_GPIO_Port, OUT2_Pin, GPIO_PIN_SET)
#define OUT2_OFF()		HAL_GPIO_WritePin(OUT2_GPIO_Port, OUT2_Pin, GPIO_PIN_RESET)
#define OUT3_ON()		HAL_GPIO_WritePin(OUT3_GPIO_Port, OUT3_Pin, GPIO_PIN_SET)
#define OUT3_OFF()		HAL_GPIO_WritePin(OUT3_GPIO_Port, OUT3_Pin, GPIO_PIN_RESET)
#define OUT4_ON()		HAL_GPIO_WritePin(OUT4_GPIO_Port, OUT4_Pin, GPIO_PIN_SET)
#define OUT4_OFF()		HAL_GPIO_WritePin(OUT4_GPIO_Port, OUT4_Pin, GPIO_PIN_RESET)
#define OUT5_ON()		HAL_GPIO_WritePin(OUT5_GPIO_Port, OUT5_Pin, GPIO_PIN_SET)
#define OUT5_OFF()		HAL_GPIO_WritePin(OUT5_GPIO_Port, OUT5_Pin, GPIO_PIN_RESET)
#define OUT6_ON()		HAL_GPIO_WritePin(OUT6_GPIO_Port, OUT6_Pin, GPIO_PIN_SET)
#define OUT6_OFF()		HAL_GPIO_WritePin(OUT6_GPIO_Port, OUT6_Pin, GPIO_PIN_RESET)


/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
