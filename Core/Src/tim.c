/**
 ******************************************************************************
 * File Name          : TIM.c
 * Description        : This file provides code for the configuration
 *                      of the TIM instances.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "tim.h"

/* USER CODE BEGIN 0 */

#include "led.h"

/* USER CODE END 0 */

TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;

/* TIM2 init function */
void MX_TIM2_Init(void)
{
	TIM_ClockConfigTypeDef sClockSourceConfig = { 0 };
	TIM_MasterConfigTypeDef sMasterConfig = { 0 };

	htim2.Instance = TIM2;
	htim2.Init.Prescaler = 0;
	htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim2.Init.Period = 7199;
	htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
	if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
	{
		Error_Handler();
	}
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
	{
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
	{
		Error_Handler();
	}

}
/* TIM3 init function */
void MX_TIM3_Init(void)
{
	TIM_ClockConfigTypeDef sClockSourceConfig = { 0 };
	TIM_MasterConfigTypeDef sMasterConfig = { 0 };

	htim3.Instance = TIM3;
	htim3.Init.Prescaler = 7199;
	htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim3.Init.Period = 4999;
	htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
	if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
	{
		Error_Handler();
	}
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
	{
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
	{
		Error_Handler();
	}

}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *tim_baseHandle)
{

	if (tim_baseHandle->Instance == TIM2)
	{
		/* USER CODE BEGIN TIM2_MspInit 0 */

		/* USER CODE END TIM2_MspInit 0 */
		/* TIM2 clock enable */
		__HAL_RCC_TIM2_CLK_ENABLE();

		/* TIM2 interrupt Init */
		HAL_NVIC_SetPriority(TIM2_IRQn, 1, 0);
		HAL_NVIC_EnableIRQ(TIM2_IRQn);
		/* USER CODE BEGIN TIM2_MspInit 1 */

		/* USER CODE END TIM2_MspInit 1 */
	}
	else if (tim_baseHandle->Instance == TIM3)
	{
		/* USER CODE BEGIN TIM3_MspInit 0 */

		/* USER CODE END TIM3_MspInit 0 */
		/* TIM3 clock enable */
		__HAL_RCC_TIM3_CLK_ENABLE();

		/* TIM3 interrupt Init */
		HAL_NVIC_SetPriority(TIM3_IRQn, 2, 0);
		HAL_NVIC_EnableIRQ(TIM3_IRQn);
		/* USER CODE BEGIN TIM3_MspInit 1 */

		/* USER CODE END TIM3_MspInit 1 */
	}
}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef *tim_baseHandle)
{

	if (tim_baseHandle->Instance == TIM2)
	{
		/* USER CODE BEGIN TIM2_MspDeInit 0 */

		/* USER CODE END TIM2_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_TIM2_CLK_DISABLE();

		/* TIM2 interrupt Deinit */
		HAL_NVIC_DisableIRQ(TIM2_IRQn);
		/* USER CODE BEGIN TIM2_MspDeInit 1 */

		/* USER CODE END TIM2_MspDeInit 1 */
	}
	else if (tim_baseHandle->Instance == TIM3)
	{
		/* USER CODE BEGIN TIM3_MspDeInit 0 */

		/* USER CODE END TIM3_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_TIM3_CLK_DISABLE();

		/* TIM3 interrupt Deinit */
		HAL_NVIC_DisableIRQ(TIM3_IRQn);
		/* USER CODE BEGIN TIM3_MspDeInit 1 */

		/* USER CODE END TIM3_MspDeInit 1 */
	}
}

/* USER CODE BEGIN 1 */

/***********************************
 * Brief:定时器中断回�???
 * Argument:@htim tim句柄
 * Return:�???
 ************************************/
uint32_t usCnt100 = 0;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim == (&htim2))
	{
		usCnt100++;
	}
	if (htim == (&htim3))
	{
		if (blinkflag.ledRed == 2)
		{
			HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
		}
		if (blinkflag.ledGreen == 2)
		{
			HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
		}

		if (blinkflag.leftLine == 2)
		{
			if (led.leftLine == 0)
			{
				led.leftLine = LED_ROADLINE;
			}
			else
			{
				led.leftLine = 0;
			}
		}

		if (blinkflag.rightLine == 2)
		{
			if (led.rightLine == 0)
			{
				led.rightLine = LED_ROADLINE;
			}
			else
			{
				led.rightLine = 0;
			}
		}

		if (blinkflag.car == 2)
		{
			if (led.carGreen == 0)
			{
				led.carGreen = LED_CAR;
			}
			else
			{
				led.carGreen = 0;
			}
		}
		else if (blinkflag.car == 4)
		{
			if (led.carYellow == 0)
			{
				led.carYellow = LED_CAR;
			}
			else
			{
				led.carYellow = 0;
			}
		}
		else if (blinkflag.car == 6)
		{
			if (led.carRed == 0)
			{
				led.carRed = LED_CAR;
			}
			else
			{
				led.carRed = 0;
			}
		}

		if (blinkflag.people == 2)
		{
			if (led.peopleGreen == 0)
			{
				led.peopleGreen = LED_PEOPLE;
			}
			else
			{
				led.peopleGreen = 0;
			}
		}
		else if (blinkflag.people == 4)
		{
			if (led.peopleYellow == 0)
			{
				led.peopleYellow = LED_PEOPLE;
			}
			else
			{
				led.peopleYellow = 0;
			}
		}
		else if (blinkflag.people == 6)
		{
			if (led.peopleRed == 0)
			{
				led.peopleRed = LED_PEOPLE;
			}
			else
			{
				led.peopleRed = 0;
			}
		}

		if (blinkflag.fault == 2)
		{
			if (led.fault == 0)
			{
				led.fault = LED_FAULT;
			}
			else
			{
				led.fault = 0;
			}
		}

		if (blinkflag.aebState == 2)
		{
			if (led.aebStateGreen == 0)
			{
				led.aebStateGreen = LED_AEB_GREEN;
			}
			else
			{
				led.aebStateGreen = 0;
			}
		}
		else if (blinkflag.aebState == 4)
		{
			if (led.aebStateRed == 0)
			{
				led.aebStateRed = LED_AEB_RED;
			}
			else
			{
				led.aebStateRed = 0;
			}
		}

		if (blinkflag.point == 2)
				{
					if (led.point == 0)
					{
						led.point = LED_POINT;
					}
					else
					{
						led.point = 0;
					}
				}

	}
}

/***********************************
 * Brief:延时100us
 * Argument:@value 延时多少�???100us
 * Return:�???
 ************************************/
void Delay100Us(uint32_t value)
{
	uint32_t newCnt = usCnt100;
	while (usCnt100 < newCnt + value)
	{
	}
}

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
