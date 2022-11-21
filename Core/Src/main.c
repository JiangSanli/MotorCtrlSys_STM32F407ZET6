/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "main.h"
#include "cmsis_os.h"
#include "adc.h"
#include "can.h"
#include "dac.h"
#include "dma.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

PUTCHAR_PROTOTYPE
{
	HAL_UART_Transmit(&huart3, (uint8_t*)&ch,1,HAL_MAX_DELAY);
    return ch;
}
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void MX_FREERTOS_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */


  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
  //HAL_Delay(6000);
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_CAN1_Init();
  MX_USART1_UART_Init();
  MX_DAC_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_UART4_Init();
  MX_UART5_Init();
  MX_USART3_UART_Init();
  MX_ADC1_Init();
  MX_ADC2_Init();
  MX_I2C2_Init();
  MX_TIM10_Init();
  MX_TIM11_Init();
  MX_TIM13_Init();
  MX_TIM14_Init();
  MX_TIM9_Init();
  MX_TIM7_Init();
  MX_TIM6_Init();
  MX_TIM12_Init();
#ifdef XXX
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_CAN1_Init();
  MX_USART1_UART_Init();
  MX_DAC_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_UART4_Init();
  MX_UART5_Init();
  MX_USART3_UART_Init();
  MX_ADC1_Init();
  MX_ADC2_Init();
  MX_I2C2_Init();
  MX_TIM10_Init();
  MX_TIM11_Init();
  MX_TIM13_Init();
  MX_TIM14_Init();
  MX_TIM9_Init();
  MX_DMA_Init();
  MX_TIM7_Init();
  MX_TIM6_Init();
  MX_TIM12_Init();
  /* USER CODE BEGIN 2 */
#endif
  ALL_Motors_Disable();

  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();  /* Call init function for freertos objects (in freertos.c) */
  MX_FREERTOS_Init();

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 160;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV4;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

uint32_t uart_reieve_timeoutCount = 0;
uint32_t Pluse_High = 2; // 高电平时10-20us
uint32_t timecount_TIM10 = 0;
uint32_t AccelDecelcount_TIM10 = 0;
uint32_t timecount_TIM11 = 0;
uint32_t AccelDecelcount_TIM11 = 0;
uint32_t timecount_TIM12 = 0;
uint32_t AccelDecelcount_TIM12 = 0;
uint8_t  Motor7_State = 1 ;
uint32_t timecount_TIM13 = 0;
uint32_t AccelDecelcount_TIM13 = 0;
uint32_t timecount_TIM14 = 0;
uint32_t AccelDecelcount_TIM14 = 0;
uint32_t timecount_TIM6 = 0;
uint32_t AccelDecelcount_TIM6 = 0;
uint8_t  Motor5_State = 1 ;
uint32_t timecount_TIM7 = 0;
uint32_t AccelDecelcount_TIM7 = 0;
int  Motor6_State = 0 ;
//直流电机控制
uint32_t timecount_TIM12_DCM6 = 0 ;
uint32_t timecount_TIM12_DCM7 = 0 ;
uint32_t timecount_TIM12_DCM8 = 0 ;


/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM1) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

	if (htim->Instance == TIM9) {	// 计时器周期为0.1ms
		uart_reieve_timeoutCount++;
		if( (USART_RX_STA&0x8000) || (USART_RX_STA==0) ){	// 判断串口接收超时
			uart_reieve_timeoutCount = 0;
			HAL_TIM_Base_Stop_IT(&htim9);
		}
		else{
			if(uart_reieve_timeoutCount > 1000){
				printf("[WRONG] Data Input Timeout ! \r\n");
				uart_reieve_timeoutCount = 0;
				USART_RX_STA = 0;
				HAL_TIM_Base_Stop_IT(&htim9);
			}
		}
	}

	if (htim->Instance == TIM10)
	{
			timecount_TIM10++;
			AccelDecelcount_TIM10++;
			if(timecount_TIM10 <= Pluse_High)
			{
				Motorpluse1_High();
			}
			else if(timecount_TIM10 > Pluse_High)
			{
				Motorpluse1_Low();
			}
			if(timecount_TIM10 >= Motor[1].StepperSpeedTMR)
			{
				timecount_TIM10 = 0 ;
				Motor[1].NumberofSteps--;
				if (Motor[1].MotorDirection == 1){
					Motor[1].StepPosition++;
					if (Motor[1].StepPosition >= Motor[1].StepsInOneCircle){
						Motor[1].StepPosition = Motor[1].StepPosition - Motor[1].StepsInOneCircle ;
					}
				}
				else{
					Motor[1].StepPosition--;
					if (Motor[1].StepPosition < 0){
						Motor[1].StepPosition = Motor[1].StepPosition + Motor[1].StepsInOneCircle ;
					}
				}
			}
			if(Motor[1].StepPosition == Motor[1].TargetPosition)
			{
				Motor[1].Status = 0;
				printf("---Motor1 Steps Position:%ld---\r\n",Motor[1].StepPosition);
				HAL_TIM_Base_Stop_IT(&htim10);
			}
			else if (Motor[1].NumberofSteps <= 0){
				Motor[1].Status = 0;
				printf("[WRONG]Motor1 Goto Target Position Failed!---Current_Position:%ld---\r\n",Motor[1].StepPosition);
				HAL_TIM_Base_Stop_IT(&htim10);
			}

			if (Motor[1].NumberofSteps > Motor[1].NumberofSteps_StopAccel)  // if.. begin Acceleration
			{
				if(AccelDecelcount_TIM10 >= Motor[1].AccelerationTimeTMR)
				{
					AccelDecelcount_TIM10=0;
					AccelDecel(ACCEL,&Motor[1]);
				}
			}
			else if (Motor[1].NumberofSteps < Motor[1].NumberofSteps_BeginDecel)  // if.. begin Deceleration
			{
				if(AccelDecelcount_TIM10 >= Motor[1].DecelerationTimeTMR)
				{
					AccelDecelcount_TIM10=0;
					AccelDecel(DECEL,&Motor[1]);
				}
			}


	}

	else if (htim->Instance == TIM11)
	{
			timecount_TIM11++;
			AccelDecelcount_TIM11++;
			if(timecount_TIM11 <= Pluse_High)
			{
				Motorpluse2_High();
			}
			else if(timecount_TIM11 > Pluse_High)
			{
				Motorpluse2_Low();
			}
			if(timecount_TIM11 >= Motor[2].StepperSpeedTMR)
			{
				timecount_TIM11 = 0 ;
				Motor[2].NumberofSteps--;
#ifndef JiaYangZhen_EncoderMode
				if (Motor[2].MotorDirection == 1){
					Motor[2].StepPosition++;
				}
				else{
					Motor[2].StepPosition--;
				}
#endif
			}

			if(Motor[2].StepPosition == Motor[2].TargetPosition){
				Motor[2].Status = 0;
				printf("---Motor2 Steps Position:%ld---\r\n",Motor[2].StepPosition);
				HAL_TIM_Base_Stop_IT(&htim11);
			}
			else if (Motor[2].NumberofSteps <= 0){
				Motor[2].Status = 0;
				printf("[WRONG]Motor2 Goto Target Position Failed!---Current_Position:%ld---\r\n",Motor[2].StepPosition);
				HAL_TIM_Base_Stop_IT(&htim11);
			}

			if (Motor[2].NumberofSteps > Motor[2].NumberofSteps_StopAccel)
			{
				if(AccelDecelcount_TIM11 >= Motor[2].AccelerationTimeTMR)
				{
					AccelDecelcount_TIM11=0;
					AccelDecel(ACCEL,&Motor[2]);
				}
			}
			else if (Motor[2].NumberofSteps < Motor[2].NumberofSteps_BeginDecel)
			{
				if(AccelDecelcount_TIM11 >= Motor[2].DecelerationTimeTMR)
				{
					AccelDecelcount_TIM11=0;
					AccelDecel(DECEL,&Motor[2]);
				}
			}

	}

	else if (htim->Instance == TIM13)
	{
			timecount_TIM13++;
			AccelDecelcount_TIM13++;
			if (Motor[3].StepPosition > 7000){
				printf("[WRONG]OverTrip!!!,Motor[3].StepPosition:%ld\r\n",Motor[3].StepPosition);
				Motor[3].Status = 0;
				HAL_TIM_Base_Stop_IT(&htim13);
			}
#ifdef JiaYangZhen
			if (DetectionTask_STATE == Cap0_Sample_State){
				switch (Follow_state){
				case 1:
					if(timecount_TIM13 <= Pluse_High){
						Motorpluse3_High();
					}
					else if(timecount_TIM13 > Pluse_High){
						Motorpluse3_Low();
					}
					if(timecount_TIM13 >= Motor[3].StepperSpeedTMR){
						timecount_TIM13 = 0 ;
#ifndef JiaYangZhen_EncoderMode
						Motor[3].StepPosition++;
#endif
					}
					break;
				case 2:
					timecount_TIM13 = 0 ;
					//使用IO输出模块进行液面�????????�????????
//					HAL_TIM_Base_Stop_IT(&htim13);
//					Motor[3].Status = 0;
					break;
				case 3:
					if(timecount_TIM13 <= Pluse_High){
						Motorpluse3_High();
					}
					else if(timecount_TIM13 > Pluse_High){
						Motorpluse3_Low();
					}
					if(timecount_TIM13 >= Motor[3].StepperSpeedTMR){
						timecount_TIM13 = 0 ;
#ifndef JiaYangZhen_EncoderMode
							Motor[3].StepPosition--;
#endif
					}
					break;
				}
			}
			else
#endif
			{
				if(timecount_TIM13 <= Pluse_High){
					Motorpluse3_High();
				}
				else if(timecount_TIM13 > Pluse_High){
					Motorpluse3_Low();
				}
				if(timecount_TIM13 >= Motor[3].StepperSpeedTMR){
					timecount_TIM13 = 0 ;
					Motor[3].NumberofSteps--;
#ifndef JiaYangZhen_EncoderMode
					if (Motor[3].MotorDirection == 1){
						Motor[3].StepPosition++;
					}
					else{
						Motor[3].StepPosition--;
					}
#endif
				}

				if(Motor[3].StepPosition == Motor[3].TargetPosition){
					Motor[3].Status = 0;
					printf("---Motor3 Steps Position:%ld---\r\n",Motor[3].StepPosition);
					HAL_TIM_Base_Stop_IT(&htim13);
				}
				else if (Motor[3].NumberofSteps <= 0){
					Motor[3].Status = 0;
					printf("[WRONG]Motor3 Goto Target Position Failed!---Current_Position:%ld---\r\n",Motor[3].StepPosition);
					HAL_TIM_Base_Stop_IT(&htim13);
				}

				if (Motor[3].NumberofSteps > Motor[3].NumberofSteps_StopAccel){
					if(AccelDecelcount_TIM13 >= Motor[3].AccelerationTimeTMR){
						AccelDecelcount_TIM13=0;
						AccelDecel(ACCEL,&Motor[3]);
					}
				}
				else if (Motor[3].NumberofSteps < Motor[3].NumberofSteps_BeginDecel){
					if(AccelDecelcount_TIM13 >= Motor[3].DecelerationTimeTMR){
						AccelDecelcount_TIM13=0;
						AccelDecel(DECEL,&Motor[3]);
					}
				}
			}

	}

	else if (htim->Instance == TIM14)
	{
			timecount_TIM14++;
			AccelDecelcount_TIM14++;
			if(timecount_TIM14 <= Pluse_High)
			{
				Motorpluse4_High();
			}
			else if(timecount_TIM14 > Pluse_High)
			{
				Motorpluse4_Low();
			}
			if(timecount_TIM14 >= Motor[4].StepperSpeedTMR)
			{
				timecount_TIM14 = 0 ;
				Motor[4].NumberofSteps--;
				if (Motor[4].MotorDirection == 1){
					Motor[4].StepPosition++;
				}
				else{
					Motor[4].StepPosition--;
				}
			}
			if(Motor[4].StepPosition == Motor[4].TargetPosition)
			{
				Motor[4].Status = 0;
				//printf("---Motor4 Steps Position:%ld---\r\n",Motor[4].StepPosition);
				HAL_TIM_Base_Stop_IT(&htim14);
			}
			else if (Motor[4].NumberofSteps <= 0){
				Motor[4].Status = 0;
				//printf("[WRONG]Motor4 Goto Target Position Failed!---Current_Position:%ld---\r\n",Motor[4].StepPosition);
				HAL_TIM_Base_Stop_IT(&htim14);
			}

			if (Motor[4].NumberofSteps > Motor[4].NumberofSteps_StopAccel)
			{
				if(AccelDecelcount_TIM14 >= Motor[4].AccelerationTimeTMR)
				{
					AccelDecelcount_TIM14=0;
					AccelDecel(ACCEL,&Motor[4]);
				}
			}
			else if (Motor[4].NumberofSteps < Motor[4].NumberofSteps_BeginDecel)
			{
				if(AccelDecelcount_TIM14 >= Motor[4].DecelerationTimeTMR)
				{
					AccelDecelcount_TIM14=0;
					AccelDecel(DECEL,&Motor[4]);
				}
			}
	}

	else if (htim->Instance == TIM6)
	{
			timecount_TIM6++;
			AccelDecelcount_TIM6++;

			if(timecount_TIM6 >= Motor[5].StepperSpeedTMR)
			{
				timecount_TIM6 = 0 ;
				if (Motor[5].MotorDirection == 1){
					switch ( Motor5_State )
					{
					case 1:
						Motor5_AB();
						Motor5_State = 2 ;
						break;
					case 2:
						Motor5_aB();
						Motor5_State = 3 ;
						break;
					case 3:
						Motor5_ab();
						Motor5_State = 4 ;
						break;
					case 4:
						Motor5_Ab();
						Motor5_State = 1 ;
						break;
					}
				}
				else{
					switch ( Motor5_State )
					{
					case 1:
						Motor5_AB();
						Motor5_State = 2 ;
						break;
					case 2:
						Motor5_Ab();
						Motor5_State = 3 ;
						break;
					case 3:
						Motor5_ab();
						Motor5_State = 4 ;
						break;
					case 4:
						Motor5_aB();
						Motor5_State = 1 ;
						break;
					}
				}

				Motor[5].NumberofSteps--;
				if (Motor[5].MotorDirection == 1){
					Motor[5].StepPosition++;
				}
				else{
					Motor[5].StepPosition--;
				}
			}
			if(Motor[5].StepPosition == Motor[5].TargetPosition){
				Motor[5].Status = 0;
				Motor5_Release();
				printf("---Motor5 Steps Position:%ld---\r\n",Motor[5].StepPosition);
				HAL_TIM_Base_Stop_IT(&htim6);
			}
			else if (Motor[5].NumberofSteps <= 0){
				Motor[5].Status = 0;
				Motor5_Release();
				printf("[WRONG]Motor5 Goto Target Position Failed!---Current_Position:%ld---\r\n",Motor[5].StepPosition);
				HAL_TIM_Base_Stop_IT(&htim6);
			}

			if (Motor[5].NumberofSteps > Motor[5].NumberofSteps_StopAccel){
				if(AccelDecelcount_TIM6 >= Motor[5].AccelerationTimeTMR){
					AccelDecelcount_TIM6=0;
					AccelDecel(ACCEL,&Motor[5]);
				}
			}
			else if (Motor[5].NumberofSteps < Motor[5].NumberofSteps_BeginDecel){
				if(AccelDecelcount_TIM6 >= Motor[5].DecelerationTimeTMR){
					AccelDecelcount_TIM6=0;
					AccelDecel(DECEL,&Motor[5]);
				}
			}
	}

#ifndef L298N_StepMotorCtrl
	else if (htim->Instance == TIM7)
	{
			timecount_TIM7++;
			AccelDecelcount_TIM7++;

			if(timecount_TIM7 >= Motor[6].StepperSpeedTMR)
			{
				timecount_TIM7 = 0 ;
				Motor[6].NumberofSteps--;

				if (Motor[6].MotorDirection == 1){
					switch ( Motor6_State )
					{
					case 1:
						Motor6_AB();
						Motor6_State = 2 ;
						break;
					case 2:
						Motor6_aB();
						Motor6_State = 3 ;
						break;
					case 3:
						Motor6_ab();
						Motor6_State = 4 ;
						break;
					case 4:
						Motor6_Ab();
						Motor6_State = 1 ;
						break;
					}
				}
				else{
					switch ( Motor6_State )
					{
					case 1:
						Motor6_AB();
						Motor6_State = 2 ;
						break;
					case 2:
						Motor6_Ab();
						Motor6_State = 3 ;
						break;
					case 3:
						Motor6_ab();
						Motor6_State = 4 ;
						break;
					case 4:
						Motor6_aB();
						Motor6_State = 1 ;
						break;
					}
				}

				if (Motor[6].MotorDirection == 1){
					Motor[6].StepPosition++;
				}
				else{
					Motor[6].StepPosition--;
				}
			}
			if(Motor[6].StepPosition == Motor[6].TargetPosition){
				Motor[6].Status = 0;
				Motor6_Release();
				printf("---Motor[6] Steps Position:%ld---\r\n",Motor[6].StepPosition);
				HAL_TIM_Base_Stop_IT(&htim7);
			}
			else if (Motor[6].NumberofSteps <= 0){
				Motor[6].Status = 0;
				Motor6_Release();
				printf("[WRONG]Motor6 Goto Target Position Failed!---Current_Position:%ld---\r\n",Motor[6].StepPosition);
				HAL_TIM_Base_Stop_IT(&htim7);
			}

			if (Motor[6].NumberofSteps > Motor[6].NumberofSteps_StopAccel){
				if(AccelDecelcount_TIM7 >= Motor[6].AccelerationTimeTMR){
					AccelDecelcount_TIM7=0;
					AccelDecel(ACCEL,&Motor[6]);
				}
			}
			else if (Motor[6].NumberofSteps < Motor[6].NumberofSteps_BeginDecel){
				if(AccelDecelcount_TIM7 >= Motor[6].DecelerationTimeTMR){
					AccelDecelcount_TIM7=0;
					AccelDecel(DECEL,&Motor[6]);
				}
			}
	}
#else
	else if (htim->Instance == TIM7)
	{
			timecount_TIM7++;
			AccelDecelcount_TIM7++;

			if ( get_ADC1_Current_Phase(0) < (abs(Motor6_MicroSteps[Motor6_State][1])*VM6_Full_Current) ){
				if ( Motor6_MicroSteps[Motor6_State][1] > 0 ){
					Motor6_A();
					LED0_ON();
				}else{
					Motor6_a();
					LED0_OFF();
				}
			}else{
				Motor6_A_release();
//				if ( Motor6_MicroSteps[Motor6_State][1] > 0 ){
//					Motor6_a();
//					LED0_OFF();
//				}else{
//					Motor6_A();
//					LED0_ON();
//				}
			}

			if ( get_ADC1_Current_Phase(1) < (abs(Motor6_MicroSteps[Motor6_State][2])*VM6_Full_Current) ){
				if ( Motor6_MicroSteps[Motor6_State][2] > 0 ){
					Motor6_B();
					LED1_ON();
				}else{
					Motor6_b();
					LED1_OFF();
				}
			}else{
				Motor6_B_release();
//				if ( Motor6_MicroSteps[Motor6_State][2] > 0 ){
//					Motor6_b();
//					LED1_OFF();
//				}else{
//					Motor6_B();
//					LED1_ON();
//				}
			}

			if(timecount_TIM7 >= Motor[6].StepperSpeedTMR)
			{
				timecount_TIM7 = 0 ;
				Motor[6].NumberofSteps--;

				if (Motor[6].MotorDirection == 1){
					Motor6_State += Motor6_MicroSteps_Increment ;
					if ( Motor6_State > 31 ){
						Motor6_State = 0;
					}
				}
				else{
					Motor6_State -= Motor6_MicroSteps_Increment;
					if ( Motor6_State < 0 ){
						Motor6_State = 32 - Motor6_MicroSteps_Increment;
					}
				}

				if (Motor[6].MotorDirection == 1){
					Motor[6].StepPosition++;
				}
				else{
					Motor[6].StepPosition--;
				}

				if(Motor[6].StepPosition == Motor[6].TargetPosition){
					Motor[6].Status = 0;
					Motor6_Release();
					printf("---Motor[6] Steps Position:%ld---\r\n",Motor[6].StepPosition);
					HAL_TIM_Base_Stop_IT(&htim7);
				}
				else if (Motor[6].NumberofSteps <= 0){
					Motor[6].Status = 0;
					Motor6_Release();
					printf("[WRONG]Motor6 Goto Target Position Failed!---Current_Position:%ld---\r\n",Motor[6].StepPosition);
					HAL_TIM_Base_Stop_IT(&htim7);
				}
			}

			if (Motor[6].NumberofSteps > Motor[6].NumberofSteps_StopAccel){
				if(AccelDecelcount_TIM7 >= Motor[6].AccelerationTimeTMR){
					AccelDecelcount_TIM7=0;
					AccelDecel(ACCEL,&Motor[6]);
				}
			}
			else if (Motor[6].NumberofSteps < Motor[6].NumberofSteps_BeginDecel){
				if(AccelDecelcount_TIM7 >= Motor[6].DecelerationTimeTMR){
					AccelDecelcount_TIM7=0;
					AccelDecel(DECEL,&Motor[6]);
				}
			}
	}
#endif

#ifdef WeiLiuKong
	else if (htim->Instance == TIM12)
	{
			timecount_TIM12++;
			AccelDecelcount_TIM12++;

			if(timecount_TIM12 >= Motor[7].StepperSpeedTMR)
			{
				timecount_TIM12 = 0 ;
				Motor[7].NumberofSteps--;

				if (Motor[7].MotorDirection == 1){
					switch ( Motor7_State )
					{
					case 1:
						Motor7_AB();
						Motor7_State = 2 ;
						break;
					case 2:
						Motor7_Ab();
						Motor7_State = 3 ;
						break;
					case 3:
						Motor7_ab();
						Motor7_State = 4 ;
						break;
					case 4:
						Motor7_aB();
						Motor7_State = 1 ;
						break;
					}
				}
				else{
					switch ( Motor7_State )
					{
					case 1:
						Motor7_AB();
						Motor7_State = 2 ;
						break;
					case 2:
						Motor7_aB();
						Motor7_State = 3 ;
						break;
					case 3:
						Motor7_ab();
						Motor7_State = 4 ;
						break;
					case 4:
						Motor7_Ab();
						Motor7_State = 1 ;
						break;
					}
				}

				if (Motor[7].MotorDirection == 1){
					Motor[7].StepPosition++;
				}
				else{
					Motor[7].StepPosition--;
				}
			}
			if(Motor[7].StepPosition == Motor[7].TargetPosition){
				Motor[7].Status = 0;
				Motor7_Release();
				printf("---Motor[7] Steps Position:%ld---\r\n",Motor[7].StepPosition);
				HAL_TIM_Base_Stop_IT(&htim12);
			}
			else if (Motor[7].NumberofSteps <= 0){
				Motor[7].Status = 0;
				Motor7_Release();
				printf("[WRONG]Motor[7] Goto Target Position Failed!---Current_Position:%ld---\r\n",Motor[7].StepPosition);
				HAL_TIM_Base_Stop_IT(&htim12);
			}

			if (Motor[7].NumberofSteps > Motor[7].NumberofSteps_StopAccel){
				if(AccelDecelcount_TIM12 >= Motor[7].AccelerationTimeTMR){
					AccelDecelcount_TIM12=0;
					AccelDecel(ACCEL,&Motor[7]);
				}
			}
			else if (Motor[7].NumberofSteps < Motor[7].NumberofSteps_BeginDecel){
				if(AccelDecelcount_TIM12 >= Motor[7].DecelerationTimeTMR){
					AccelDecelcount_TIM12=0;
					AccelDecel(DECEL,&Motor[7]);
				}
			}
	}
#endif

#ifdef CiFenLi
	else if (htim->Instance == TIM12)
	{
			timecount_TIM12_DCM7++;
			timecount_TIM12_DCM6++;
			if (Motor[7].Status){
				if(timecount_TIM12_DCM7 <= Motor[7].AccelerationTimeTMR)
				{
					switch( Motor[7].Status ){
					case 0b00000010:
						VM7_IN1_H();
						break;
					case 0b00000001:
						VM7_IN4_H();
						break;
					case 0b00000011:
						VM7_IN1_H();
						VM7_IN4_H();
						break;
					}
				}
				else if(timecount_TIM12_DCM7 > Motor[7].AccelerationTimeTMR)
				{
					switch( Motor[7].Status ){
					case 0b00000010:
						VM7_IN1_L();
						break;
					case 0b00000001:
						VM7_IN4_L();
						break;
					case 0b00000011:
						VM7_IN1_L();
						VM7_IN4_L();
						break;
					}
				}
				if(timecount_TIM12_DCM7 >= Motor[7].StepperSpeedTMR)
				{
					timecount_TIM12_DCM7 = 0 ;
				}
			}

			if (Motor[6].Status){
				if(timecount_TIM12_DCM6 <= Motor[6].AccelerationTimeTMR)
				{
					switch( Motor[6].Status ){
					case 0b00000010:
						VM6_IN1_H();
						break;
					case 0b00000001:
						VM6_IN4_H();
						break;
					case 0b00000011:
						VM6_IN1_H();
						VM6_IN4_H();
						break;
					}
				}
				else if(timecount_TIM12_DCM6 > Motor[6].AccelerationTimeTMR)
				{
					switch( Motor[6].Status ){
					case 0b00000010:
						VM6_IN1_L();
						break;
					case 0b00000001:
						VM6_IN4_L();
						break;
					case 0b00000011:
						VM6_IN1_L();
						VM6_IN4_L();
						break;
					}
				}
				if(timecount_TIM12_DCM6 >= Motor[6].StepperSpeedTMR)
				{
					timecount_TIM12_DCM6 = 0 ;
				}
			}
	}
#endif

#ifdef JiaYangZhen
	else if (htim->Instance == TIM12)
	{
			timecount_TIM12_DCM7++;
			timecount_TIM12_DCM8++;
			if (Motor[7].Status){
				if(timecount_TIM12_DCM7 <= Motor[7].AccelerationTimeTMR)
				{
					switch( Motor[7].Status ){
					case 0b00000010:
						VM7_IN1_H();
						break;
					case 0b00000001:
						VM7_IN4_H();
						break;
					case 0b00000011:
						VM7_IN1_H();
						VM7_IN4_H();
						break;
					}
				}
				else if(timecount_TIM12_DCM7 > Motor[7].AccelerationTimeTMR)
				{
					switch( Motor[7].Status ){
					case 0b00000010:
						VM7_IN1_L();
						break;
					case 0b00000001:
						VM7_IN4_L();
						break;
					case 0b00000011:
						VM7_IN1_L();
						VM7_IN4_L();
						break;
					}
				}
				if(timecount_TIM12_DCM7 >= Motor[7].StepperSpeedTMR)
				{
					timecount_TIM12_DCM7 = 0 ;
				}
			}

			if (Motor[8].Status){
				if(timecount_TIM12_DCM8 <= Motor[8].AccelerationTimeTMR)
				{
					switch( Motor[8].Status ){
					case 0b00000010:
						VM8_IN1_H();
						break;
					case 0b00000001:
						VM8_IN4_H();
						break;
					case 0b00000011:
						VM8_IN1_H();
						VM8_IN4_H();
						break;
					}
				}
				else if(timecount_TIM12_DCM8 > Motor[8].AccelerationTimeTMR)
				{
					switch( Motor[8].Status ){
					case 0b00000010:
						VM8_IN1_L();
						break;
					case 0b00000001:
						VM8_IN4_L();
						break;
					case 0b00000011:
						VM8_IN1_L();
						VM8_IN4_L();
						break;
					}
				}
				if(timecount_TIM12_DCM8 >= Motor[8].StepperSpeedTMR)
				{
					timecount_TIM12_DCM8 = 0 ;
				}
			}
	}
#endif

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
