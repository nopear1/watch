/*
 * Copyright(C), 20XX-20XX, Soterea Automotive Technology Co., Ltd.
 * ----------------------------------------------------------------
 *File Name   : speaker.c
 *Description :	
 *  Created on: 2020��4��23��
 *      Author   :�
 */

#include "tim.h"
#include "speaker.h"


/***********************************
 * Function name: SpeakerInit
 * Brief:������ʼ��
 * Argument:��
 * Return:��
 ************************************/
void SpeakerInit(void)
{
	DelayMs(200);
}

/***********************************
 * Function name: OneLineSendData
 * Brief:һ�ߴ��ڷ�������
 * Argument:��
 * Return:��
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
 * Brief:һ����һ���Ĳ�������
 * Argument:value �ڼ�������
 * Return:��
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
 * Brief:��������
 * Argument:value �ڼ�������
 * Return:��
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
 * Brief:��������
 * Argument:value ���õ�����
 * Return:��
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
 * Brief:����һ��
 * Argument:value ����
 * Return:��
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
 * Brief:ÿ��5�벥��һ������
 * Argument:value ����
 * Return:��
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

