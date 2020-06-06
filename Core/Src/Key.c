/*
 * Copyright(C), 20XX-20XX, Soterea Automotive Technology Co., Ltd.
 * ----------------------------------------------------------------
 *File Name   : Key.c
 *Description :	
 *  Created on: 2020��3��23��
 *      Author   :�
 */

#include "Key.h"
#include "string.h"
#include"speaker.h"
#include "can.h"



extern uint8_t testData;


enum KeyState
{
	NONE = 0, PRESS, LONG_PRESS, RELEASE
};

#define UP  1
#define DOWN 0
#define BUTTON_MAX   8
typedef struct HmiKey
{
	uint32_t jitterTick;
	uint32_t pressTick;
//	uint32_t releaseTick;
	enum KeyState keyState;
	uint8_t (*readBtn)(void);
	void (*callBack)(enum KeyState ksta);
} HmiKey_t;



HmiKey_t aebKey={0};
HmiKey_t volumeKey =
{ 0 };

HmiKey_t reserveKey =
{ 0 };

static KeySave_t keySave;
//#define KEY_SCAN_INTERVAL    20
#define SHORT_PRESS_TICK  100
#define LONG_PRESS_TICK  2000
#define JITTER  20


TickType_t settingRetrunTick=0;


uint8_t ReadAebBtn(void)
{
	return KEY_AEB;
}

uint8_t ReadVolumeBtn(void)
{
	return KEY_VOLUME;
}


uint8_t ReadRevBtn(void)
{
	return KEY_RESERVED;
}

/***********************************
 * Function name: AebCb
 * Brief:AEB�����ص�
 * Argument:kSta ����״̬
 * Return:��
 ************************************/
void AebCb(enum KeyState kSta)
{
	static aebCnt=0;
	if (kSta == LONG_PRESS)
	{
		SetAebState(AEB_OFF);
	}
	else if(kSta==PRESS)
	{
		SetAebState(AEB_ON);

//		uint8_t hardware=GetHardwareType();
//		if(hardware==HW_ALARM)
//		{
//			if(aeb.aebState==AEB_OFF)
//			{
//				SetAebState(AEB_ON);
//			}
//			else
//			{
//				aebCnt++;
//				SetVolume(aebCnt%3);
//				PlayVoice(SP_AEB_ON);
//			}
//		}
//		else if(hardware==HW_WATCH)
//		{
//			SetAebState(AEB_ON);
//		}
	}
}


void VolCb(enum KeyState kSta)
{
	static uint8_t volCnt = 0;
	if (kSta == PRESS)
	{
		volCnt++;
		uint8_t volValue = volCnt % 3;
		switch (volValue)
		{
		case VOL_MAX:
			SetVolume(VOL_MAX);
			break;
		case VOL_MID:
			SetVolume(VOL_MID);
			break;
		case VOL_MIN:
			SetVolume(VOL_MIN);
			break;
		default:
			SetVolume(VOL_MAX);
			break;
		}
	}
}


void KeyInit(void)
{
//	memset(&keySave, 0, sizeof(keySave));



	/*��������*/
//	SetVolume(keySave.volume);

	/*��ʼ��ÿ������ʵ��*/
	aebKey.jitterTick = 0;
	aebKey.keyState = NONE;
	aebKey.pressTick = 0;
	aebKey.readBtn = ReadAebBtn;
	aebKey.callBack = AebCb;

	volumeKey.jitterTick = 0;
	volumeKey.keyState = NONE;
	volumeKey.pressTick = 0;
	volumeKey.readBtn = ReadVolumeBtn;
	volumeKey.callBack = VolCb;

	reserveKey.jitterTick = 0;
	reserveKey.keyState = NONE;
	reserveKey.pressTick = 0;
	reserveKey.readBtn = ReadRevBtn;
	reserveKey.callBack = NULL;

}

/**
 *
 * ���¾�ִ�ж���
 *
 */

void ScanOneKey1(HmiKey_t *pKey)
{
	if (pKey->readBtn() == DOWN)
	{
		if (pKey->jitterTick == 0)
		{
			pKey->jitterTick = GetSysticks();
		}
		else if (GetSysticks() - pKey->jitterTick > 20)
		{
			if (pKey->readBtn() == DOWN)
			{
				if (pKey->pressTick == 0)
				{
					pKey->pressTick = GetSysticks();
				}
				if (GetSysticks() - pKey->pressTick > 2000)
				{
					pKey->pressTick = GetSysticks();
					pKey->keyState = LONG_PRESS;
					if (pKey->callBack != NULL)
					{
						pKey->callBack(pKey->keyState);
					}
					pKey->jitterTick = 0;
					pKey->pressTick = 0;
//						pKey->keyState=NONE;
//						pKey->pressTick=GetSysticks();
				}
			}
		}
	}
	else
	{
		if ((pKey->pressTick != 0) && (pKey->keyState == NONE))
		{
			if ((GetSysticks() - pKey->pressTick < 2000)
					&& (GetSysticks() - pKey->pressTick > 50)) //�ﵽ�˶̰���׼
			{
				pKey->pressTick = GetSysticks();
				pKey->keyState = PRESS;
				if (pKey->callBack != NULL)
				{
					pKey->callBack(pKey->keyState);
				}
			}
			pKey->jitterTick = 0;
			pKey->pressTick = 0;
//					pKey->keyState=NONE;
//					pKey->pressTick=GetSysticks();
		}
		pKey->keyState = NONE;
	}
}
/****
 *
 * �����ɿ���ִ�ж���
 *
 */
void ScanOneKey(HmiKey_t *pKey)
{
	/******************************************/
	if (pKey->readBtn() == DOWN) //�����������
	{
		if (pKey->jitterTick == 0)
		{
			pKey->jitterTick = GetSysticks();
		}
		else if (GetSysticks() - pKey->jitterTick > 20) //����
		{
			if (pKey->readBtn() == DOWN) //�����������
			{
				if (pKey->pressTick == 0)
				{
					pKey->pressTick = GetSysticks();
				}
			}
		}
	}
	else //����ʱ̧��״̬
	{
		if (pKey->pressTick != 0) //������¹�
		{
			if (GetSysticks() - pKey->pressTick > 2000) //�жϰ���ʱ���ﵽ�˳�����׼
			{
				pKey->pressTick = GetSysticks();
				pKey->keyState = LONG_PRESS;
			}
			else// if (GetSysticks() - pKey->pressTick > 50) //�ﵽ�˶̰���׼
			{
				pKey->keyState = PRESS;
			}
			if (pKey->callBack != NULL)
			{
				pKey->callBack(pKey->keyState);
			}
			pKey->jitterTick = 0;
			pKey->pressTick = 0;
			pKey->keyState = NONE;
		}
	}
}

/***********************************
 * Function name: ScanKey
 * Brief:ɨ�����а���
 * Argument:kSta ����״̬
 * Return:��
 ************************************/
void ScanKey(void)
{
		ScanOneKey(&aebKey);
		ScanOneKey(&volumeKey);
}

