/**
  ******************************************************************************
  * File Name          : CAN.h
  * Description        : This file provides code for the configuration
  *                      of the CAN instances.
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __can_H
#define __can_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#include "gpio.h"
#include "speaker.h"
#include "led.h"
/* USER CODE END Includes */

extern CAN_HandleTypeDef hcan;

/* USER CODE BEGIN Private defines */
typedef struct AebMsg
{
	uint8_t leftLine:2;
	uint8_t rightLine:2;
	uint8_t car:3;
	uint8_t r1:1;
	uint8_t people:3;
	uint8_t aebState:3;
	uint8_t fault:2;
	uint8_t digitalState:2;
	uint8_t point:2;
	uint8_t ledGreen:2;
	uint8_t ledRed:2;
	uint8_t numRight:4;
	uint8_t numLeft:4;
	uint8_t voice;
	uint8_t r2[3];

}AebMsg_t;

typedef struct BsdMsg
{
	uint8_t leftLine:2;
		uint8_t rightLine:2;
		uint8_t car:3;
		uint8_t r1:1;
		uint8_t people:3;
		uint8_t aebState:3;
		uint8_t fault:2;
		uint8_t digitalState:2;
		uint8_t point:2;
		uint8_t ledGreen:2;
		uint8_t ledRed:2;
		uint8_t numRight:4;
		uint8_t numLeft:4;
		uint8_t voice;
		uint8_t r2[3];

}BsdMsg_t;

typedef struct WatchMsg
{
	uint8_t aebState:2;
	uint8_t bsdState:2;
	uint8_t roadState:4;
	uint8_t loadState:4;
	uint8_t senState:4;
	uint8_t hardwareType;
	uint8_t r[5];

}WatchMsg_t;

typedef struct CanRxMsg
{
	uint8_t data[8];
	uint8_t flg;
} CanRxMsg_t;

extern CanRxMsg_t msg11b; //BSD
extern CanRxMsg_t msg11c; //BSD回复
extern CanRxMsg_t msg11d; //AEB回复
extern CanRxMsg_t msg11e; //AEB

extern WatchMsg_t watchTx;
extern WatchMsg_t watchRx;

extern AebMsg_t aeb;
/* USER CODE END Private defines */

void MX_CAN_Init(void);

/* USER CODE BEGIN Prototypes */
void SetAebState(uint8_t state);
void CanFilterConfigScale16IdList(void);
uint8_t CanTxMessage(uint8_t ide,uint32_t id,uint8_t len,uint8_t *data);
void CanDataAnalisys(void);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ can_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
