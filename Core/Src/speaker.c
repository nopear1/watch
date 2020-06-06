/*
 * Copyright(C), 20XX-20XX, Soterea Automotive Technology Co., Ltd.
 * ----------------------------------------------------------------
 *File Name   : speaker.c
 *Description :	
 *  Created on: 2020年4月23日
 *      Author   :杨超
 */

#include "tim.h"
#include "speaker.h"


/***********************************
 * Function name: SpeakerInit
 * Brief:语音初始化
 * Argument:无
 * Return:无
 ************************************/
void SpeakerInit(void)
{
	DelayMs(200);
}

/***********************************
 * Function name: OneLineSendData
 * Brief:一线串口发送数据
 * Argument:无
 * Return:无
 ************************************/
void OneLineSendData(uint8_t data)
{
	uint8_t temp;
	uint8_t i;
	SP_DATA_LOW;
	DelayMs(5);
	temp = data & 0x01;
	for (i = 0; i < 8; i++)
	{
		if (temp == 1)
		{
			SP_DATA_HIGH;
			Delay100Us(6);
			SP_DATA_LOW;
			Delay100Us(2);
		}
		else
		{
			SP_DATA_HIGH;
			Delay100Us(2);
			SP_DATA_LOW;
			Delay100Us(6);
		}
		data = data >> 1;
		temp = data & 0x01;
	}
	SP_DATA_HIGH;
}

/***********************************
 * Function name: PlayVoice1
 * Brief:一条接一条的播放语音
 * Argument:value 第几条语音
 * Return:无
 ************************************/
void PlayVoice1(uint8_t value)
{
	while (SP_BUSY == 0)
	{
	};
	OneLineSendData(SP_CONTINUOUS);
	DelayMs(2);
	OneLineSendData(value);
	DelayMs(2);
}

/***********************************
 * Function name: PlayVoice
 * Brief:播放语音
 * Argument:value 第几条语音
 * Return:无
 ************************************/
static uint8_t voice=0;
void PlayVoice(uint8_t value)
{
	voice=value;
	while (SP_BUSY == 0)
	{
	};
	DelayMs(5);
	OneLineSendData(value);
}

/***********************************
 * Function name: SetVolume
 * Brief:设置音量
 * Argument:value 设置的音量
 * Return:无
 ************************************/
void SetVolume(uint8_t value)
{
	while (SP_BUSY == 0)
	{
	};
	DelayMs(5);
	switch (value)
	{
	case VOL_MAX:
		OneLineSendData(SP_VOL_MAX);
		break;
	case VOL_MID:

		OneLineSendData(SP_VOL_MID);
		break;
	case VOL_MIN:
		OneLineSendData(SP_VOL_MIN);
		break;
	default:
		break;
	}

}

/***********************************
 * Function name: PlayVoiceOnce
 * Brief:播放一次
 * Argument:value 语音
 * Return:无
 ************************************/
void PlayVoiceOnce(uint8_t value)
{
	if(value!=voice)
	{
		PlayVoice(value);
	}
}


/***********************************
 * Function name: PlayVoiceContinuous
 * Brief:每隔5秒播放一次语音
 * Argument:value 语音
 * Return:无
 ************************************/
TickType_t aebAlarmTick=0;
void PlayVoiceContinuous(uint8_t value)
{
	if(GetSysticks()-aebAlarmTick>5000)
	{
		aebAlarmTick=GetSysticks();
		PlayVoice(value);
	}
}

TickType_t faultTick=0;
uint8_t  faultCnt=0;
void PlayVoice5TimesPer10min(uint8_t value)
{
	if(GetSysticks()-faultTick>1000*60*10)
	{
		faultCnt++;
				if(faultCnt>5)
				{
					return;
				}
		faultTick=GetSysticks();
		PlayVoice(value);

	}
}

