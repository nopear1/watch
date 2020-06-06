#include "led.h"
#include "tim.h"

/**
 *row:Ҫ������������code Ҫ��ʾ���룬8λ�����λĬ��Ϊ0�� ����ÿλ����led�����һ��7��led��Ϊ1ʱ������
 */

BlinkFlag_t blinkflag;

uint8_t codeTable[8]={0};
void LedDisplay(uint8_t row, uint8_t code)
{
	if ((code & 0x01) == 1)
		{
			LED_COL9 = 0;
		} else
		{
			LED_COL9 = 1;
		}

		if (((code >> 1) & 0x01) == 1)
		{
			LED_COL10 = 0;
		} else
		{
			LED_COL10 = 1;
		}

		if (((code >> 2) & 0x01) == 1)
		{
			LED_COL11 = 0;
		} else
		{
			LED_COL11 = 1;
		}

		if (((code >> 3) & 0x01) == 1)
		{
			LED_COL12 = 0;
		} else
		{
			LED_COL12 = 1;
		}

		if (((code >> 4) & 0x01) == 1)
		{
			LED_COL13 = 0;
		} else
		{
			LED_COL13 = 1;
		}

		if (((code >> 5) & 0x01) == 1)
		{
			LED_COL14 = 0;
		} else
		{
			LED_COL14 = 1;
		}

		if (((code >> 6) & 0x01) == 1)
		{
			LED_COL15 = 0;
		} else
		{
			LED_COL15 = 1;
		}

		if (((code >> 7) & 0x01) == 1)
		{
			LED_COL16 = 0;
		} else
		{
			LED_COL16 = 1;
		}
	switch (row)
	{
	case 1:
		LED_COM1 = 0;
		HAL_Delay(100);
//		if (GetSysticks()%100==0)
//		{
//			LED_COM1 = 1;
//		}
		LED_COM1 = 1;
		break;
	case 2:
		LED_COM2 = 0;
		HAL_Delay(100);
		LED_COM2 = 1;
		break;
	case 3:
		LED_COM3 = 0;
		HAL_Delay(100);
		LED_COM3=1;
		break;
	case 4:
		LED_COM4 = 0;
		HAL_Delay(100);
		LED_COM4=1;
		break;
	case 5:
		LED_COM5 = 0;
		HAL_Delay(100);
		LED_COM5=1;
		break;
	case 6:
		LED_COM6 = 0;
		HAL_Delay(100);
		LED_COM6=1;
		break;
	case 7:
		LED_COM7 = 0;
		HAL_Delay(100);
		LED_COM7=1;
		break;
	case 8:
		LED_COM8 = 0;
		HAL_Delay(100);
		LED_COM8=1;
		break;
	}


}


void LedLoop(void)
{
	for(uint8_t i=0;i<8;i++)
	{
		LedDisplay(i,codeTable[i]);//���Ե����������ÿ����ѭ������һ��
	}
}
//void LedScan(void)
//{
//	LedDisplay();
//}

/***********************************
 * Brief:�󳵵�����
 * Argument:��
 * Return:��
 ************************************/
 void LeftLineOn(void)
{
//	LedDisplay();
}

/***********************************
 * Brief:�󳵵�����
 * Argument:��
 * Return:��
 ************************************/
void LeftLineOff(void)
{
//	LedDisplay();
}

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

		break;
	case 1:

		break;
	case 2:

		if (GetSysticks() % 500 == 0)
		{

		}
		break;
	default:
		break;
	}
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

		break;
	case 1:

		break;
	case 2:

		if (GetSysticks() % 500 == 0)
		{

		}
		break;
	default:
		break;
	}
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

		break;
	case 1:

		break;
	case 2:

		if (GetSysticks() % 500 == 0)
		{

		}
		break;
	default:
		break;
	}
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

		break;
	case 1:

		break;
	case 2:

		if (GetSysticks() % 500 == 0)
		{

		}
		break;
	default:
		break;
	}
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

		break;
	case 1:

		break;
	case 2:

		if (GetSysticks() % 500 == 0)
		{

		}
		break;
	default:
		break;
	}
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

		break;
	case 1:

		break;
	case 2:

		if (GetSysticks() % 500 == 0)
		{

		}
		break;
	default:
		break;
	}
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

		break;
	case 1:

		break;
	case 2:

		if (GetSysticks() % 500 == 0)
		{

		}
		break;
	default:
		break;
	}
}

/***********************************
 * Brief:������������״̬
 * Argument:@state:0~F
 * Return:��
 ************************************/
void SetDigitalNumLeft(uint8_t state)
{
	switch (state)
	{
	case 0:

		break;
	case 1:

		break;
	case 2:

		break;
	case 3:

		break;
	case 4:

		break;
	case 5:

		break;
	case 6:

		break;
	case 7:

		break;
	case 8:

		break;
	case 9:

		break;
	case 0xA:

		break;
	case 0xB:

		break;
	case 0xC:

		break;
	case 0xD:

		break;
	case 0xE:

		break;
	case 0xF:

		break;
	default:
		break;
	}
}

/***********************************
 * Brief:�����Ҳ������״̬
 * Argument:@state:0~F
 * Return:��
 ************************************/
void SetDigitalNumRight(uint8_t state)
{
	switch (state)
		{
		case 0:

			break;
		case 1:

			break;
		case 2:

			break;
		case 3:

			break;
		case 4:

			break;
		case 5:

			break;
		case 6:

			break;
		case 7:

			break;
		case 8:

			break;
		case 9:

			break;
		case 0xA:

			break;
		case 0xB:

			break;
		case 0xC:

			break;
		case 0xD:

			break;
		case 0xE:

			break;
		case 0xF:

			break;
		default:
			break;
		}
}

