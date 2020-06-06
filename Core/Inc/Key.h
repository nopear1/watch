/*
 * Copyright(C), 20XX-20XX, Soterea Automotive Technology Co., Ltd.
 * ----------------------------------------------------------------
 *File Name   : Key.h
 *Description :	
 *  Created on: 2020��3��23��
 *      Author   :�
 */
#ifndef KEY_H_
#define KEY_H_

#include "main.h"
#include "Tim.h"
#include "can.h"




#define KEY_AEB    		HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1)
#define  KEY_VOLUME   HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)
#define KEY_RESERVED    HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_2)
#define KEY_ALARM  HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_6)

enum aebState
{
	AEB_ON,
	AEB_OFF,
};


enum volState
{
	VOL_MAX,
	VOL_MID,
	VOL_MIN,
};




typedef struct KeySave
{
//	uint32_t aeb;
//	uint32_t bsd;
//	uint32_t volume;
//	uint32_t load;
//	uint32_t sen;//�����ȵ���Ԥ��
//	uint32_t bright;
//	uint32_t env;
//	uint32_t reserve;//Ԥ��

		uint8_t aeb;
		uint8_t bsd;
		uint8_t volume;
		uint8_t load;
		uint8_t sen;//�����ȵ���Ԥ��
		uint8_t bright;
		uint8_t road;//·��
		uint8_t reserve;//Ԥ��
}KeySave_t;

void KeyInit(void);
void ScanKey(void);
void KeyEvent(void);

#endif /* KEY_H_ */
