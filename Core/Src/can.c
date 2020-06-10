/**
  ******************************************************************************
  * File Name          : CAN.c
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

/* Includes ------------------------------------------------------------------*/
#include "can.h"

/* USER CODE BEGIN 0 */

uint8_t hardware = 0;
uint8_t canTxCnt = 0;
WatchMsg_t watchTx;
WatchMsg_t watchRx;
AebMsg_t aeb;
BsdMsg_t bsd;

/*BSD控制报文*/
CanRxMsg_t msg11b;
/*BSD应答报文*/
CanRxMsg_t msg11c;
/*AEB应答报文*/
CanRxMsg_t msg11d;
/*AEB控制报文*/
CanRxMsg_t msg11e;

void SetAebState(uint8_t state)
{
	hardware = GetHardwareType();

	memset(&watchTx, 0, sizeof(watchTx));
	watchTx.aebState = state;
	watchTx.hardwareType = hardware;
//	do
//	{
//		CanTxMessage(CAN_ID_STD, 0x11F, 8, (uint8_t*) &watchTx);
//		HAL_Delay(100);
//		canTxCnt++;
//		/*连发5�?????*/
//		if (canTxCnt > 5)
//		{
//			canTxCnt = 0;
//			break;
//		}
//	} while ((msg11d.flg == 0)&&(msg11c.flg == 0));
//	msg11d.flg =0;
//	msg11c.flg =0;

	CanTxMessage(CAN_ID_STD, 0x11F, 8, (uint8_t*) &watchTx);
//	HAL_Delay(100);
}

/* USER CODE END 0 */

CAN_HandleTypeDef hcan;

/* CAN init function */
void MX_CAN_Init(void)
{

  hcan.Instance = CAN1;
  hcan.Init.Prescaler = 4;
  hcan.Init.Mode = CAN_MODE_NORMAL;
  hcan.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan.Init.TimeSeg1 = CAN_BS1_9TQ;
  hcan.Init.TimeSeg2 = CAN_BS2_8TQ;
  hcan.Init.TimeTriggeredMode = DISABLE;
  hcan.Init.AutoBusOff = DISABLE;
  hcan.Init.AutoWakeUp = DISABLE;
  hcan.Init.AutoRetransmission = DISABLE;
  hcan.Init.ReceiveFifoLocked = DISABLE;
  hcan.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan) != HAL_OK)
  {
    Error_Handler();
  }

}

void HAL_CAN_MspInit(CAN_HandleTypeDef* canHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspInit 0 */

  /* USER CODE END CAN1_MspInit 0 */
    /* CAN1 clock enable */
    __HAL_RCC_CAN1_CLK_ENABLE();
  
    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**CAN GPIO Configuration    
    PA11     ------> CAN_RX
    PA12     ------> CAN_TX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* CAN1 interrupt Init */
    HAL_NVIC_SetPriority(USB_LP_CAN1_RX0_IRQn, 3, 0);
    HAL_NVIC_EnableIRQ(USB_LP_CAN1_RX0_IRQn);
  /* USER CODE BEGIN CAN1_MspInit 1 */

  /* USER CODE END CAN1_MspInit 1 */
  }
}

void HAL_CAN_MspDeInit(CAN_HandleTypeDef* canHandle)
{

  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspDeInit 0 */

  /* USER CODE END CAN1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_CAN1_CLK_DISABLE();
  
    /**CAN GPIO Configuration    
    PA11     ------> CAN_RX
    PA12     ------> CAN_TX 
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_11|GPIO_PIN_12);

    /* CAN1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USB_LP_CAN1_RX0_IRQn);
  /* USER CODE BEGIN CAN1_MspDeInit 1 */

  /* USER CODE END CAN1_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */

/* CAN filter config function */
/***********************************
 * Brief:设置CAN滤波设置
 * Argument:�?????
 * Return:�?????
 ************************************/
void CanFilterConfigScale16IdList(void)
{

	uint32_t stdIdBsd = 0x11B;
	uint32_t stdIdBsdAck = 0;
	uint32_t stdIdAebAck = 0;
	uint32_t stdIdAeb = 0x11E;
	CAN_FilterTypeDef sFilterCfg;
	sFilterCfg.FilterScale = CAN_FILTERSCALE_16BIT;
	sFilterCfg.FilterMode = CAN_FILTERMODE_IDLIST;
	sFilterCfg.FilterBank = 0;
	sFilterCfg.FilterIdHigh = stdIdAeb << 5;
	sFilterCfg.FilterIdLow = stdIdBsd << 5;
	sFilterCfg.FilterMaskIdHigh = stdIdBsdAck << 5;
	sFilterCfg.FilterMaskIdLow = stdIdAebAck << 5;
	sFilterCfg.FilterFIFOAssignment = CAN_FILTER_FIFO0;
	sFilterCfg.FilterActivation = CAN_FILTER_ENABLE;
	if (HAL_CAN_ConfigFilter(&hcan, &sFilterCfg) != HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING)
			!= HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_CAN_Start(&hcan) != HAL_OK)
	{
		Error_Handler();
	}
}

/***********************************
 * Brief:CAN发�??
 * Argument:@ide：标准帧还是扩展�?????? @id  canid  @len长度 @data数据
 * Return:0：发送成�?????   1：发送失�?????
 ************************************/
uint8_t CanTxMessage(uint8_t ide, uint32_t id, uint8_t len, uint8_t *data)
{
	uint32_t TxMailbox;
	CAN_TxHeaderTypeDef CAN_TxHeader;
	uint16_t i = 0;
	CAN_TxHeader.IDE = ide;
	CAN_TxHeader.StdId = id;
	CAN_TxHeader.ExtId = id;
	CAN_TxHeader.DLC = len;
	CAN_TxHeader.RTR = CAN_RTR_DATA;
	CAN_TxHeader.TransmitGlobalTime = DISABLE;
	while (HAL_CAN_GetTxMailboxesFreeLevel(&hcan) == 0)
	{
		i++;
		if (i > 0xff)
			return 1;
	}
//	HAL_Delay(500);
	if (HAL_CAN_AddTxMessage(&hcan, &CAN_TxHeader, data, &TxMailbox) != HAL_OK)
	{
		return 1;
	}
	return 0;
}

/***********************************
 * Brief:CAN中断回调
 * Argument:@hcan can句柄
 * Return:�?????
 ************************************/
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	CAN_RxHeaderTypeDef CAN_RxHeader;
	HAL_StatusTypeDef HAL_Retval;
	uint8_t RxBuf[8] = { 0 };
	HAL_Retval = HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &CAN_RxHeader, RxBuf);
	if (HAL_Retval == HAL_OK)
	{
//		if (CAN_RxHeader.StdId == 0x11d)
//		{
//			msg11d.flg = 1;
//			memcpy(msg11d.data, RxBuf, 8);
//			memset(RxBuf, 0, 8);
//		}
		if (CAN_RxHeader.StdId == 0x11b)
		{
			msg11b.flg = 1;
			memcpy(msg11b.data, RxBuf, 8);
			memset(RxBuf, 0, 8);
		}
//		if (CAN_RxHeader.StdId == 0x11c)
//		{
//			msg11c.flg = 1;
//			memcpy(msg11c.data, RxBuf, 8);
//			memset(RxBuf, 0, 8);
//		}
		if (CAN_RxHeader.StdId == 0x11e)
		{
			msg11e.flg = 1;
			memcpy(msg11e.data, RxBuf, 8);
			memset(RxBuf, 0, 8);
		}
	}
}

/***********************************
 * Brief:CAN数据解析
 * Argument:�?????
 * Return:�?????
 ************************************/
void CanDataAnalisys(void)
{
	/*如果收到AEB应答指令*/
//	if (msg11d.flg == 1)
//	{
//		watchRx = *(WatchMsg_t*) (msg11d.data);
//		/*发�?�和接收到的�?????�?????*/
//		if (watchRx.aebState == watchTx.aebState)
//		{
//			if (watchRx.aebState == AEB_ON)
//			{
//				PlayVoiceOnce(SP_AEB_ON);
//			}
//			else
//			{
//				PlayVoiceOnce(SP_AEB_OFF);
//			}
//			msg11d.flg = 0;
//		}
//	}
	/*如果收到BSD应答指令*/
//	 if (msg11c.flg == 1)
//	{
//		watchRx = *(WatchMsg_t*) (msg11c.data);
//		/*发�?�和接收到的�?????�?????*/
//		if (watchRx.bsdState == watchTx.bsdState)
//		{
////	  PlayVoice (SP_BSD_ON);
//		msg11c.flg = 0;
//		}
//	}
	/*如果收到AEB控制指令*/
	if (msg11e.flg == 1)
	{
		aeb = *(AebMsg_t*) (msg11e.data);
		/*先解析语�?????*/
		if (aeb.voice != 0)
		{
			PlayVoice(aeb.voice);
		}
		/*如果是报警器*/
		if (hardware == HW_ALARM)
		{
			/*点亮操作不受限制*/
			if (aeb.ledRed != 0)
			{
				SetLedRed(aeb.ledRed);
			}
			else
			{
				/*熄灭操作，需要确认bsd没有点亮的情况下去操�?????*/
				if (bsd.ledRed == 0)
				{
					SetLedRed(aeb.ledRed);
				}
			}
			/*点亮操作不受限制*/
			if (aeb.ledGreen != 0)
			{
				SetLedGreen(aeb.ledGreen);
			}
			else
			{
				/*熄灭操作，需要确认bsd没有点亮的情况下去操�?????*/
				if (bsd.ledGreen == 0)
				{
					SetLedGreen(aeb.ledGreen);
				}
			}

		}
		else if (hardware == HW_WATCH)
		{
			/*解析左车道线*/
			SetLeftLine(aeb.leftLine);
			/*解析右车道线*/
			SetRightLine(aeb.rightLine);
			/*解析aeb灯*/
			SetAeb(aeb.aebState);
			/*点亮操作不受限制*/
			if (aeb.car != 0)
			{
				SetCar(aeb.car);
			}
			else
			{
				/*熄灭操作，需要确认bsd没有点亮的情况下去操�?????*/
				if (bsd.car == 0)
				{
					SetCar(aeb.car);
				}
			}
			/*点亮操作不受限制*/
						if (aeb.fault != 0)
						{
							SetFault(aeb.fault);
						}
						else
						{
							/*熄灭操作，需要确认bsd没有点亮的情况下去操�?????*/
							if (bsd.fault == 0)
							{
								SetFault(aeb.fault);
							}
						}
			/*点亮操作不受限制*/
			if (aeb.people != 0)
			{
				SetPeople(aeb.people);
			}
			else
			{
				/*熄灭操作，需要确认bsd没有点亮的情况下去操�?????*/
				if (bsd.people == 0)
				{
					SetPeople(aeb.people);
				}
			}
			/*点亮操作不受限制*/
			if (aeb.point != 0)
			{
				SetPoint(aeb.point);
			}
			else
			{
				/*熄灭操作，需要确认bsd没有点亮的情况下去操�?????*/
				if (bsd.point == 0)
				{
					SetPoint(aeb.point);
				}
			}

			if (aeb.digitalState == 1)
			{
				SetDigitalNumLeft(aeb.numLeft);
				SetDigitalNumRight(aeb.numRight);
			}
			else
			{
				led.numLeft=0;
				led.numRight=0;
			}
		}
		msg11e.flg =0;
	}
	/*如果收到BSD控制指令*/
	 if (msg11b.flg == 1)
	{
		bsd = *(BsdMsg_t*) (msg11b.data);

		/*先解析语�?????*/
		if (aeb.voice == 0)
		{
			if (bsd.voice != 0)
			{
				PlayVoice(bsd.voice);
			}
		}
		/*如果是报警器*/
		if (hardware == HW_ALARM)
		{
			/*如果没被aeb占用*/
			if (aeb.ledRed == 0)
			{
				SetLedRed(bsd.ledRed);
			}
			if (aeb.ledGreen == 0)
			{
				SetLedGreen(bsd.ledGreen);
			}
		}
		else if (hardware == HW_WATCH)
		{
			/*只有AEB没有操作，bsd才能操作该led*/
			if (aeb.car == 0)
			{
				SetCar(bsd.car);
			}

			if (aeb.fault == 0)
						{
				SetFault(bsd.fault);
						}

			if (aeb.people == 0)
			{
				SetPeople(bsd.people);
			}

			if (aeb.point == 0)
			{
				SetPoint(bsd.point);
			}

			if ((aeb.digitalState == 0) && (bsd.digitalState == 1))
			{
				SetDigitalNumLeft(bsd.numLeft);
				SetDigitalNumRight(bsd.numRight);
			}
			else
				{
					led.numLeft=0;
					led.numRight=0;
				}
		}
		msg11b.flg =0;
	}

}
/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
