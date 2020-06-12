/**
  ******************************************************************************
  * File Name          : gpio.c
  * Description        : This file provides code for the configuration
  *                      of all used GPIO pins.
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
#include "gpio.h"
/* USER CODE BEGIN 0 */
#include "led.h"
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
        * Free pins are configured automatically as Analog (this feature is enabled through 
        * the Code Generation settings)
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, SP_DATA_Pin|LED_RED_Pin|LED_GREEN_Pin|LED_COL16_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LED_COM1_Pin|LED_COM2_Pin|LED_COL10_Pin|LED_COL11_Pin 
                          |LED_COL12_Pin|LED_COL13_Pin|LED_COL14_Pin|LED_COL15_Pin 
                          |LED_COM3_Pin|LED_COM4_Pin|LED_COM5_Pin|LED_COM6_Pin 
                          |LED_COM7_Pin|LED_COM8_Pin|LED_COL9_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : PC13 PC14 PC15 */
  GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PAPin PAPin PAPin PAPin 
                           PAPin PA6 */
  GPIO_InitStruct.Pin = KEY_VOL_Pin|KEY_AEB_Pin|KEY_RES_Pin|SP_BUSY_Pin 
                          |HARDWARE_Pin|GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PAPin PAPin PAPin PAPin */
  GPIO_InitStruct.Pin = SP_DATA_Pin|LED_RED_Pin|LED_GREEN_Pin|LED_COL16_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PBPin PBPin PBPin PBPin 
                           PBPin PBPin PBPin PBPin 
                           PBPin PBPin PBPin PBPin 
                           PBPin PBPin PBPin */
  GPIO_InitStruct.Pin = LED_COM1_Pin|LED_COM2_Pin|LED_COL10_Pin|LED_COL11_Pin 
                          |LED_COL12_Pin|LED_COL13_Pin|LED_COL14_Pin|LED_COL15_Pin 
                          |LED_COM3_Pin|LED_COM4_Pin|LED_COM5_Pin|LED_COM6_Pin 
                          |LED_COM7_Pin|LED_COM8_Pin|LED_COL9_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PB2 */
  GPIO_InitStruct.Pin = GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 2 */

/***********************************
 * Brief:获取硬件类型
 * Argument:�???
 * Return:HW_ALARM�???  报警�???  HW_WATCH：watch
 ************************************/
uint8_t GetHardwareType(void)
{

	if(HAL_GPIO_ReadPin(HARDWARE_GPIO_Port, HARDWARE_Pin)==GPIO_PIN_RESET)
	{
		return HW_ALARM;
	}
	else
	{
		return HW_WATCH;
	}

}

//TickType_t ledRedTick=0;

/***********************************
 * Brief:设置红色LED（报警器版）
 * Argument:state�???0：led�???  1：led�???  2：led�???
 * Return:�???
 ************************************/
void SetLedRed(uint8_t state)
{

	switch (state) {
		case 0:
			HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin,GPIO_PIN_RESET );
			break;
		case 1:
					HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin,GPIO_PIN_SET );
					break;
		case 2:
			if(blinkflag.ledRed!=2)
			{
			HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin,GPIO_PIN_SET );
			}

			break;
		default:
			break;
	}
	blinkflag.ledRed=state;
}

/***********************************
 * Brief:设置绿色LED（报警器版）
 * Argument:state�???0：led�???  1：led�???  2：led�???
 * Return:�???
 ************************************/
void SetLedGreen(uint8_t state)
{

	switch (state) {
		case 0:
			HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin,GPIO_PIN_SET );
			break;
		case 1:

					HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin,GPIO_PIN_RESET );
					break;
		case 2:
			if(blinkflag.ledGreen!=2)
			{
//				HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin,GPIO_PIN_SET );
				HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin,GPIO_PIN_RESET );
			}

			break;
		default:
			break;
	}
	blinkflag.ledGreen=state;
}
/* USER CODE END 2 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
