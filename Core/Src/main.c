/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "can.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "sys.h"
#include "speaker.h"
#include "led.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint32_t tick = 0;
uint8_t aebConnected = 0;
uint8_t bsdConnected = 0;
/*用来记录初始按键电平*/
volatile uint32_t latchSta = 0;
uint32_t keyCnt = 0;
uint32_t volCnt = 0;
uint8_t numTab[] = { 0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f,
		0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71 };

uint8_t num = 0;
LED_t led = { 0 };
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void AlarmKeyScan(void)
{
	/*按键切换状�??*/
	if (PAin(6) == latchSta)
	{
		latchSta = !PAin(6);
		PAout(8) = ~PAout(8);
		SetAebState(keyCnt % 2);

		keyCnt++;
		/*按六次音量调�??*/
		if ((keyCnt % 6 == 0) && (keyCnt != 0))
		{
			volCnt++;
			SetVolume(volCnt % 3);
		}
	}
}

void LedTest(void)
{
	while (num != 15)
	{
		LedDisplay(1, numTab[num]);
		LedDisplay(2, numTab[num]);
		LedDisplay(3, 0x3f);
		LedDisplay(4, 0x3f);
		/*人*/
		LedDisplay(5 + num % 3, 0x0f);
		/*车*/
		LedDisplay(5 + num % 3, 0xf0);
		/*AEB绿*/
		LedDisplay(3, 0x40);
		/*AEB红*/
		LedDisplay(8, 0x01);
		/*故障*/
		LedDisplay(8, 0x02);
		/*小数点*/
		LedDisplay(1, 0x80);
		if (GetSysticks() % 1000 == 0)
		{
			num = (num + 1) % 16;
		}
	}
}
/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
	/* USER CODE BEGIN 1 */
//uint8_t buf[8]={0};
	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_CAN_Init();
	MX_USART1_UART_Init();
	MX_TIM2_Init();
	MX_TIM3_Init();
	/* USER CODE BEGIN 2 */
	CanFilterConfigScale16IdList();
	HAL_TIM_Base_Start_IT(&htim2);
	HAL_TIM_Base_Start_IT(&htim3);
	KeyInit();

	/*第一次播�???? �????活，但不出声*/

//	PlayVoice(SP_WELCOME);
	HAL_Delay(200);
	PlayVoice(SP_WELCOME);

	if (GetHardwareType() == HW_WATCH)
	{
		LED_COM1 = 1;
		LED_COL9 = 1;
//						LedTest();
		led.aebStateGreen = 0;
		led.numLeft = 0;
		led.numRight = 0;
		led.aebStateRed = 0;
		led.carGreen = 0;
		led.carRed = 0;
		led.carYellow = 0;
		led.peopleRed = 0;
		led.peopleGreen = 0;
		led.peopleYellow = 0;
		led.rightLine = 0;
		led.leftLine = 0;
		led.fault = 0;
		led.numLeft = 0;
		led.numRight = 0;
		led.point = 0;
//		led.aebStateRed = LED_AEB_RED;
//		led.carGreen = LED_CAR;
//		led.carRed = LED_CAR;
//		led.carYellow = LED_CAR;
//		led.peopleRed = LED_PEOPLE;
//		led.peopleGreen = LED_PEOPLE;
//		led.peopleYellow = LED_PEOPLE;
//		led.rightLine = LED_ROADLINE;
//		led.leftLine = LED_ROADLINE;
//		led.fault = LED_FAULT;
//		led.numLeft = numTab[8];
//		led.numRight = numTab[8];
//		led.point = LED_POINT;
	}
	SetAebState(AEB_ON);

	HAL_Delay(1000);
//	if (msg11e.flg == 1)  	  	  	  	  	  	  	  	  	  //AEB已连
//	{
//		aebConnected = 1;
//	}
//	if (msg11b.flg == 1)  	  	  	  	  	  	  	  	  	  //BSD已连
//	{
//		bsdConnected = 1;
//	}

	if (GetHardwareType() == HW_ALARM)
	{
		PAout(8) = 1;
		PAout(7) = 0;
		/*read key state*/
		latchSta = PAin(6);
		latchSta = !latchSta;
	}
	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1)
	{
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */

		if (GetHardwareType() == HW_ALARM)
		{
			AlarmKeyScan();
		}
		else if (GetHardwareType() == HW_WATCH)
		{
			ScanKey();
			/*左数码管和小数点*/
			LedDisplay(1, led.numLeft | led.point);
			/*右数码管*/
			LedDisplay(2, led.numRight);
			/*左车道线和绿AEB*/
			LedDisplay(3, led.leftLine | led.aebStateGreen);
			/*右车道线*/
			LedDisplay(4, led.rightLine);
			/*人和车 黄  绿 红*/
			LedDisplay(5, led.peopleYellow | led.carYellow);
			LedDisplay(6, led.peopleGreen | led.carGreen);
			LedDisplay(7, led.peopleRed | led.carRed);
			/*AEB红和故障*/
			LedDisplay(8, led.aebStateRed | led.fault);
		}
		/*every 200ms send heartbeat*/
		if (GetSysticks() - tick >= 200)
		{
			tick = GetSysticks();
			SetAebState(keyCnt % 2);
		}
		/*解析收到的CAN数据*/
		CanDataAnalisys();

	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Initializes the CPU, AHB and APB busses clocks
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}
	/** Initializes the CPU, AHB and APB busses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
	{
		Error_Handler();
	}
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */

	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
