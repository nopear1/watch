#include "led.h"
#include "tim.h"

/**
 *row:Ҫ������������code Ҫ��ʾ���룬8λ�����λĬ��Ϊ0�� ����ÿλ����led�����һ��7��led��Ϊ1ʱ������
 */
#define LED_SCAN_INTERVAL   1
BlinkFlag_t blinkflag;
LedUsed_t ledUsed;
uint32_t ledTick = 0;
uint8_t codeTable[8] = { 0 };
void LedDisplay(uint8_t row, uint8_t code)
{
	if ((code & 0x01) == 0)
	{
		LED_COL16 = 0;
	}
	else
	{
		LED_COL16 = 1;
	}

	if (((code >> 1) & 0x01) == 0)
	{
		LED_COL15 = 0;
	}
	else
	{
		LED_COL15 = 1;
	}

	if (((code >> 2) & 0x01) == 0)
	{
		LED_COL14 = 0;
	}
	else
	{
		LED_COL14 = 1;
	}

	if (((code >> 3) & 0x01) == 0)
	{
		LED_COL13 = 0;
	}
	else
	{
		LED_COL13 = 1;
	}

	if (((code >> 4) & 0x01) == 0)
	{
		LED_COL12 = 0;
	}
	else
	{
		LED_COL12 = 1;
	}

	if (((code >> 5) & 0x01) == 0)
	{
		LED_COL11 = 0;
	}
	else
	{
		LED_COL11 = 1;
	}

	if (((code >> 6) & 0x01) == 0)
	{
		LED_COL10 = 0;
	}
	else
	{
		LED_COL10 = 1;
	}

	if (((code >> 7) & 0x01) == 0)
	{
		LED_COL9 = 0;
	}
	else
	{
		LED_COL9 = 1;
	}
	switch (row)
	{
	case 1:
		LED_COM1 = 1;
		HAL_Delay(LED_SCAN_INTERVAL);
//		if(GetSysticks()-ledTick>=LED_SCAN_INTERVAL)
//		{
//			ledTick=GetSysticks();
//			LED_COM1 = 0;
//		}
//		if (GetSysticks()%100==0)
//		{
//			LED_COM1 = 1;
//		}
		LED_COM1 = 0;
		break;
	case 2:
		LED_COM2 = 1;
		HAL_Delay(LED_SCAN_INTERVAL);
		LED_COM2 = 0;
		break;
	case 3:
		LED_COM3 = 1;
		HAL_Delay(LED_SCAN_INTERVAL);
		LED_COM3 = 0;
		break;
	case 4:
		LED_COM4 = 1;
		HAL_Delay(LED_SCAN_INTERVAL);
		LED_COM4 = 0;
		break;
	case 5:
		LED_COM5 = 1;
		HAL_Delay(LED_SCAN_INTERVAL);
		LED_COM5 = 0;
		break;
	case 6:
		LED_COM6 = 1;
		HAL_Delay(LED_SCAN_INTERVAL);
		LED_COM6 = 0;
		break;
	case 7:
		LED_COM7 = 1;
		HAL_Delay(LED_SCAN_INTERVAL);
		LED_COM7 = 0;
		break;
	case 8:
		LED_COM8 = 1;
		HAL_Delay(LED_SCAN_INTERVAL);
		LED_COM8 = 0;
		break;
	}

}

void LedLoop(void)
{
	for (uint8_t i = 1; i <= 8; i++)
	{
		LedDisplay(i, codeTable[i]); //���Ե����������ÿ����ѭ������һ��
	}
}
//void LedScan(void)
//{
//	LedDisplay();
//}

/***********************************
 * Brief:�����󳵵���
 * Argument:@state 0����  1����  2:��
 * Return:��
 ************************************/
void SetLeftLine(uint8_t state)
{
	switch (state)
	{
	case 0:
		led.leftLine = 0;
		break;
	case 1:
		led.leftLine = LED_ROADLINE;
		break;
	case 2:

		if (blinkflag.leftLine != 2)
		{
			led.leftLine = LED_ROADLINE;
		}
		break;
	default:
		break;
	}
	blinkflag.leftLine = state;
}

/***********************************
 * Brief:�����ҳ�����
 * Argument:@state 0����  1����  2:��
 * Return:��
 ************************************/
void SetRightLine(uint8_t state)
{
	switch (state)
	{
	case 0:
		led.rightLine = 0;
		break;
	case 1:
		led.rightLine = LED_ROADLINE;
		break;
	case 2:
		if (blinkflag.rightLine != 2)
		{
			led.rightLine = LED_ROADLINE;
		}
		break;
	default:
		break;
	}
	blinkflag.rightLine = state;
}

/***********************************
 * Brief:����С��״̬
 * Argument:@state:0����  1����  2:��
 * Return:��
 ************************************/
void SetCar(uint8_t state)
{
	switch (state)
	{
	case 0:
		led.carGreen = 0;
		led.carRed = 0;
		led.carYellow = 0;
		break;
	case 1:
		led.carGreen = LED_CAR;
		led.carRed = 0;
		led.carYellow = 0;
		break;
	case 2:
		if (blinkflag.car != 2)
		{
			led.carGreen = LED_CAR;
			led.carRed = 0;
			led.carYellow = 0;
		}
		break;
	case 3:
		led.carYellow = LED_CAR;
		led.carGreen = 0;
		led.carRed = 0;

		break;
	case 4:
		if (blinkflag.car != 4)
		{
			led.carYellow = LED_CAR;
			led.carGreen = 0;
			led.carRed = 0;
		}
		break;
	case 5:
		led.carRed = LED_CAR;
		led.carGreen = 0;
		led.carYellow = 0;
		break;
	case 6:
		if (blinkflag.car != 6)
		{
			led.carRed = LED_CAR;
			led.carGreen = 0;
			led.carYellow = 0;
		}
	default:
		break;
	}
	blinkflag.car = state;
}

/***********************************
 * Brief:������״̬
 * Argument:@state:0����  1����  2:��
 * Return:��
 ************************************/
void SetPeople(uint8_t state)
{
	switch (state)
	{
	case 0:
		led.peopleGreen = 0;
		led.peopleRed = 0;
		led.peopleYellow = 0;
		break;
	case 1:
		led.peopleGreen = LED_PEOPLE;
		led.peopleRed = 0;
		led.peopleYellow = 0;
		break;
	case 2:
		if (blinkflag.people != 2)
		{
			led.peopleGreen = LED_PEOPLE;
			led.peopleRed = 0;
			led.peopleYellow = 0;
		}
		break;
	case 3:
		led.peopleYellow = LED_PEOPLE;
		led.peopleGreen = 0;
		led.peopleRed = 0;
		break;
	case 4:
		if (blinkflag.people != 4)
		{
			led.peopleYellow = LED_PEOPLE;
			led.peopleGreen = 0;
			led.peopleRed = 0;
		}
		break;
	case 5:
		led.peopleRed = LED_PEOPLE;
		led.peopleGreen = 0;
		led.peopleYellow = 0;
		break;
	case 6:
		if (blinkflag.people != 6)
		{
			led.peopleRed = LED_PEOPLE;
			led.peopleGreen = 0;
			led.peopleYellow = 0;
		}
		break;
	default:
		break;
	}
	blinkflag.people = state;
}

/***********************************
 * Brief:����С����״̬
 * Argument:@state:0����  1����  2:��
 * Return:��
 ************************************/
void SetPoint(uint8_t state)
{
	switch (state)
	{
	case 0:
		led.point = 0;
		break;
	case 1:
		led.point = LED_POINT;
		break;
	case 2:
		if (blinkflag.point != 2)
		{
			led.point = LED_POINT;
		}
		break;
	default:
		break;
	}
	blinkflag.point = state;
}

/***********************************
 * Brief:����AEB״̬
 * Argument:@state:0����  1����  2:��
 * Return:��
 ************************************/
void SetAeb(uint8_t state)
{
	switch (state)
	{
	case 0:
		led.aebStateGreen = 0;
		led.aebStateRed = 0;
		break;
	case 1:
		led.aebStateGreen = LED_AEB_GREEN;
		led.aebStateRed = 0;
		break;
	case 2:
		if (blinkflag.aebState != 2)
		{
			led.aebStateGreen = LED_AEB_GREEN;
			led.aebStateRed = 0;
		}
		break;
	case 3:
		led.aebStateRed = LED_AEB_RED;
		led.aebStateGreen = 0;

		break;
	case 4:
		if (blinkflag.aebState != 4)
		{
			led.aebStateRed = LED_AEB_RED;
			led.aebStateGreen = 0;
		}
		break;
	default:
		break;
	}
	blinkflag.aebState = state;
}
/***********************************
 * Brief:���ù��ϵ�״̬
 * Argument:@state:0����  1����  2:��
 * Return:��
 ************************************/
void SetFault(uint8_t state)
{
	switch (state)
	{
	case 0:
		led.fault = 0;
		break;
	case 1:
		led.fault = LED_FAULT;
		break;
	case 2:
		if (blinkflag.fault != 2)
		{
			led.fault = LED_FAULT;
		}
		break;
	default:
		break;
	}
	blinkflag.fault = state;
}

/***********************************
 * Brief:������������״̬
 * Argument:@state:0~F
 * Return:��
 ************************************/
void SetDigitalNumLeft(uint8_t state)
{
	led.numLeft = numTab[state];
}

/***********************************
 * Brief:�����Ҳ������״̬
 * Argument:@state:0~F
 * Return:��
 ************************************/
void SetDigitalNumRight(uint8_t state)
{
	led.numRight = numTab[state];
}

