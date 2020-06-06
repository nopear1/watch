/*
 * Copyright(C), 20XX-20XX, Soterea Automotive Technology Co., Ltd.
 * ----------------------------------------------------------------
 *File Name   : speaker.h
 *Description :	
 *  Created on: 2020��4��23��
 *      Author   :�
 */
#ifndef SPEAKER_H_
#define SPEAKER_H_

#include "main.h"
#include "key.h"
#define SP_DATA_LOW   HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET)
#define SP_DATA_HIGH    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET)

#define SP_BUSY  HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_3)

enum voice
{
	SP_WELCOME,
	SP_FAULTCODE,
	SP_SYS_OFF,
	SP_KEEP_DISTANCE,
	SP_AEB_ON,
	SP_AEB_OFF,
	SP_BSD_ON,
	SP_BSD_OFF,
	SP_FULL,
	SP_EMPTY,
	SP_SNOW_ON,
	SP_SNOW_OFF,
	SP_BLOCK_ON,
	SP_BLOCK_OFF,
	SP_LDW_LEFT,
	SP_LDW_RIGHT,
	SP_CALIBRATE,
	SP_LIMIT,
	SP_KEEP_D1,
	SP_MIND_PEOPLE,
	SP_WILL_UPDATE,
	SP_UPDATING,
	SP_UPDATE_OK,
	SP_UPDATE_FAILD,
	SP_BSD_LEFT,
	SP_BSD_RIGHT,
	SP_DOWNHILL,
	SP_SPEED_LIMIT,
	SP_SHARP_CURVE,
	SP_HOTLINE,
	SP_MODE_SWITCH,
	SP_FATIGUE,
	SP_BEEP,


	SP_VOL_NONE=0xe1,
	SP_VOL_MIN=0xe3,
	SP_VOL_MID=0xe7,
	SP_VOL_MAX=0xeD,

	SP_CONTINUOUS=0XF3,
};



void SpeakerInit(void);
void OneLineSendData(uint8_t data);
void PlayVoice(uint8_t value);
void SetVolume(uint8_t value);
void PlayVoiceOnce(uint8_t value);
void PlayVoiceContinuous(uint8_t value);
void PlayVoice5TimesPer10min(uint8_t value);
#endif /* SPEAKER_H_ */
