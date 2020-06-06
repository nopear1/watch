/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "string.h"
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
#define KEY_VOL_Pin GPIO_PIN_0
#define KEY_VOL_GPIO_Port GPIOA
#define KEY_AEB_Pin GPIO_PIN_1
#define KEY_AEB_GPIO_Port GPIOA
#define KEY_RES_Pin GPIO_PIN_2
#define KEY_RES_GPIO_Port GPIOA
#define SP_BUSY_Pin GPIO_PIN_3
#define SP_BUSY_GPIO_Port GPIOA
#define SP_DATA_Pin GPIO_PIN_4
#define SP_DATA_GPIO_Port GPIOA
#define HARDWARE_Pin GPIO_PIN_5
#define HARDWARE_GPIO_Port GPIOA
#define LED_RED_Pin GPIO_PIN_7
#define LED_RED_GPIO_Port GPIOA
#define LED_COM1_Pin GPIO_PIN_0
#define LED_COM1_GPIO_Port GPIOB
#define LED_COM2_Pin GPIO_PIN_1
#define LED_COM2_GPIO_Port GPIOB
#define LED_COL10_Pin GPIO_PIN_10
#define LED_COL10_GPIO_Port GPIOB
#define LED_COL11_Pin GPIO_PIN_11
#define LED_COL11_GPIO_Port GPIOB
#define LED_COL12_Pin GPIO_PIN_12
#define LED_COL12_GPIO_Port GPIOB
#define LED_COL13_Pin GPIO_PIN_13
#define LED_COL13_GPIO_Port GPIOB
#define LED_COL14_Pin GPIO_PIN_14
#define LED_COL14_GPIO_Port GPIOB
#define LED_COL15_Pin GPIO_PIN_15
#define LED_COL15_GPIO_Port GPIOB
#define LED_GREEN_Pin GPIO_PIN_8
#define LED_GREEN_GPIO_Port GPIOA
#define LED_COL16_Pin GPIO_PIN_15
#define LED_COL16_GPIO_Port GPIOA
#define LED_COM3_Pin GPIO_PIN_3
#define LED_COM3_GPIO_Port GPIOB
#define LED_COM4_Pin GPIO_PIN_4
#define LED_COM4_GPIO_Port GPIOB
#define LED_COM5_Pin GPIO_PIN_5
#define LED_COM5_GPIO_Port GPIOB
#define LED_COM6_Pin GPIO_PIN_6
#define LED_COM6_GPIO_Port GPIOB
#define LED_COM7_Pin GPIO_PIN_7
#define LED_COM7_GPIO_Port GPIOB
#define LED_COM8_Pin GPIO_PIN_8
#define LED_COM8_GPIO_Port GPIOB
#define LED_COL9_Pin GPIO_PIN_9
#define LED_COL9_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
